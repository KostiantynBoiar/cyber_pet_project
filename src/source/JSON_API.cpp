//
// Created by kostiantyn on 11/7/23.
//

#include "../headers/JSON_API.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

#define MINUTES_IN_DAY 1440
#define MINUTES_IN_HOURS 60
#define MINUTES_IN_YEAR 525600
#define MINUTES_IN_MONTH 43200

JSON_API::JSON_API(const std::string& filename) : filename(filename) {
    if (fileExists()) {
        if (!loadJsonFromFile()) {
            std::cerr << "Error loading JSON from file: " << filename << std::endl;
        }
    } else {
        jsonData.SetObject();
        saveJsonToFile();
    }
}

bool JSON_API::isInteger(const std::string &s) {
    for (char c : s) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool JSON_API::fileExists() const {
    std::ifstream file(filename);
    return file.good();
}

bool JSON_API::loadJsonFromFile() {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string jsonStr((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        jsonData.Parse(jsonStr.c_str());
        file.close();
        return !jsonData.HasParseError() && jsonData.IsObject();
    }
    return false;
}

void JSON_API::saveJsonToFile() const {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    jsonData.Accept(writer);

    std::ofstream file(filename);
    if (file.is_open()) {
        file << buffer.GetString();
        file.close();
    } else {
        std::cerr << "Error saving JSON to file: " << filename << std::endl;
    }
}

int JSON_API::foodTimeDiff() {
    int result = parseDateTime(convertJsonDate(getActualDate())) - parseDateTime(jsonData["foodTime"].GetString());
    return result;
}

int JSON_API::restTimeDiff() {
    int result = parseDateTime(convertJsonDate(getActualDate())) - parseDateTime(jsonData["restTime"].GetString());
    return result;
}

void JSON_API::updateFoodTime() {
    if (!jsonData.HasMember("foodTime")) {
        jsonData.AddMember("foodTime", "", jsonData.GetAllocator());
    }

    std::time_t currentTime = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&currentTime);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y:%m:%d:%H:%M", timeInfo);

    std::cout << "Before updateFoodTime: " << std::endl;
    saveJsonToFile();

    jsonData["foodTime"].SetString(buffer, static_cast<rapidjson::SizeType>(strlen(buffer)));

    std::cout << "After updateFoodTime: " << jsonData["foodTime"].GetString() << std::endl;
    saveJsonToFile();
}

void JSON_API::updateRestTime() {
    if (!jsonData.HasMember("restTime")) {
        jsonData.AddMember("restTime", "", jsonData.GetAllocator());
    }

    std::time_t currentTime = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&currentTime);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y:%m:%d:%H:%M", timeInfo);
    jsonData["restTime"].SetString(buffer, static_cast<rapidjson::SizeType>(strlen(buffer)));
    saveJsonToFile();
}

int JSON_API::getFoodState() {
    int foodTimeDifference = foodTimeDiff();
    std::cout << foodTimeDiff() << std::endl;
    if (foodTimeDifference > 10 && foodTimeDifference < 19) {
        return 1;
    } else if (foodTimeDifference > 20 && foodTimeDifference < 29) {
        return 2;
    } else if (foodTimeDifference > 30 && foodTimeDifference < 39) {
        return 3;
    } else if (foodTimeDifference > 40 && foodTimeDifference < 49) {
        return 4;
    } else if (foodTimeDifference > 50) {
        return 5;
    } else {
        return 0;
    }
}

std::string JSON_API::convertJsonDate(const std::string& jsonDate) const {
    std::string foodTimeStr = jsonDate;
    std::cout << "Your time is: " << foodTimeStr << std::endl;
    return foodTimeStr;
}

int JSON_API::parseDateTime(const std::string &dateTimeStr) const {
    std::string delimiter = ":";
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<int> res;

    while ((pos_end = dateTimeStr.find(delimiter, pos_start)) != std::string::npos) {
        token = dateTimeStr.substr(pos_start, pos_end - pos_start);

        token.erase(std::remove_if(token.begin(), token.end(), [](unsigned char c) { return !std::isdigit(c); }), token.end());

        pos_start = pos_end + delim_len;

        if (!token.empty()) {
            res.push_back(stoi(token));
        }
    }

    token = dateTimeStr.substr(pos_start);
    token.erase(std::remove_if(token.begin(), token.end(), [](unsigned char c) { return !std::isdigit(c); }), token.end());
    std::cout << token << std::endl;

    if (!token.empty()) {
        res.push_back(stoi(token));
    }

    for (int value : res) {
        std::cout << value << std::endl;
    }
    int minSum = (res[0] - 2022) * MINUTES_IN_YEAR + res[1] * MINUTES_IN_MONTH + res[2] * MINUTES_IN_DAY + res[3] * MINUTES_IN_HOURS + res[4];
    return minSum;

}

std::string JSON_API::getActualDate(){
    if (!jsonData.HasMember("actualTime")) {
        jsonData.AddMember("actualTime", "", jsonData.GetAllocator());
    }

    std::time_t currentTime = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&currentTime);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y:%m:%d:%H:%M", timeInfo);

    saveJsonToFile();

    jsonData["actualTime"].SetString(buffer, static_cast<rapidjson::SizeType>(strlen(buffer)));

    saveJsonToFile();
    return jsonData["actualTime"].GetString();
}


