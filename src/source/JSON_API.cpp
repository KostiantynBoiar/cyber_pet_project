//
// Created by kostiantyn on 11/7/23.
//

#include "../headers/JSON_API.h"
#include <iomanip>

#include <sstream>
#include <fstream>
#include <iostream>

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


std::time_t JSON_API::parseDateTime(const std::string& dateTimeStr) const {
    std::tm timeInfo = {};
    std::istringstream ss(dateTimeStr);

    if (!(ss >> std::get_time(&timeInfo, "%Y-%m-%d %H:%M"))) {
        ss.clear();
        ss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Error parsing date and time: " << dateTimeStr << std::endl;
        return 0;
    }

    return std::mktime(&timeInfo);
}

int JSON_API::foodTimeDiff() const {
    std::string foodTimeStr = jsonData["foodTime"].GetString();
    std::cout << foodTimeStr;
    return 0;
}

std::time_t JSON_API::restTimeDiff() const {
    std::string restTimeStr = jsonData["restTime"].GetString();
    std::time_t restTime = parseDateTime(restTimeStr);
    std::time_t currentTime = std::time(nullptr);
    return currentTime - restTime;
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

    std::cout << "After updateFoodTime: " << std::endl;
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
    std::cout << foodTimeDifference;
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
