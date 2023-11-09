//
// Created by kostiantyn on 11/7/23.
//

#include "../headers/JSON_API.h"
#include <fstream>
#include <iostream>
#include <iomanip>

JSON_API::JSON_API(const std::string& filename) {
    if (fileExists(filename)) {
        if (!loadJsonFromFile(filename)) {
            std::cerr << "Error loading JSON from file: " << filename << std::endl;
        }
    } else {
        jsonData.SetObject();
        saveJsonToFile(filename);
    }
}

bool JSON_API::fileExists(const std::string& filename) const {
    std::ifstream file(filename);
    return file.good();
}

bool JSON_API::loadJsonFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string jsonStr((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        jsonData.Parse(jsonStr.c_str());
        file.close();
        return !jsonData.HasParseError() && jsonData.IsObject();
    }
    return false;
}

void JSON_API::saveJsonToFile(const std::string& filename) const {
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

    ss >> std::get_time(&timeInfo, "%Y:%m:%d:%H:%M");

    if (ss.fail()) {
        std::cerr << "Error parsing date and time: " << dateTimeStr << std::endl;
        return 0;
    }
    return std::mktime(&timeInfo);
}

std::time_t JSON_API::foodTimeDiff() const {
    std::string foodTimeStr = jsonData["foodTime"].GetString();
    std::time_t foodTime = parseDateTime(foodTimeStr);
    std::time_t currentTime = std::time(nullptr);

    return currentTime - foodTime;
}

std::time_t JSON_API::restTimeDiff() const {
    std::string restTimeStr = jsonData["restTime"].GetString();
    std::time_t restTime = parseDateTime(restTimeStr);
    std::time_t currentTime = std::time(nullptr);

    return currentTime - restTime;
}