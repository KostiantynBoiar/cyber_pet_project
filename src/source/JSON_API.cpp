//
// Created by kostiantyn on 11/7/23.
//

#include "../headers/JSON_API.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <vector>

#define MINUTES_IN_DAY 1440
#define MINUTES_IN_HOURS 60

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

int JSON_API::foodTimeDiff() const {

    return 0;
}

std::time_t JSON_API::restTimeDiff() const {


    return 0;
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

int JSON_API::getState() const {
    std::time_t foodTimeDifference = foodTimeDiff();
    std::cout << parseDateTime(convertJsonDate(jsonData["foodTime"].GetString())) << std::endl;
    if (foodTimeDifference > 10 * 60) {
        return 1;
    } else if (foodTimeDifference > 20 * 60) {
        return 2;
    } else if (foodTimeDifference > 30 * 60) {
        return 3;
    } else if (foodTimeDifference > 40 * 60) {
        return 4;
    } else if (foodTimeDifference > 50 * 60) {
        return 5;
    } else {
        return 0;
    }
}

std::string JSON_API::convertJsonDate(const std::string& jsonDate) const {
    std::string foodTimeStr = jsonData["foodTime"].GetString();
    std::cout << "Your time is: " << foodTimeStr << std::endl;
    return foodTimeStr;
}

int JSON_API::parseDateTime(const std::string &dateTimeStr) const {
    std::string delimiter = ":";
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = dateTimeStr.find(delimiter, pos_start)) != std::string::npos) {
        token = dateTimeStr.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(dateTimeStr.substr(pos_start));

    int minSum = std::stoi(res[0]) * MINUTES_IN_DAY + std::stoi(res[1]) * MINUTES_IN_HOURS + std::stoi(res[2]);
    std::cout << minSum;
    return minSum;

}


