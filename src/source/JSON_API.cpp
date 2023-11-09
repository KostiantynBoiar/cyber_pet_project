//
// Created by kostiantyn on 11/7/23.
//

#include "../headers/JSON_API.h"
#include <iomanip>

#include <sstream>
#include <fstream>
#include <iostream>
#include <chrono>

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

// That's piece of shit that is not working
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
    std::cout << convertJsonDate(jsonData["foodTime"].GetString()) << std::endl;
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

std::string JSON_API::convertJsonDate(std::string jsonDate) const {
    std::string foodTimeStr = jsonData["foodTime"].GetString();
    std::cout << "Your time is: " << foodTimeStr << std::endl;

    // String to stream
    std::istringstream iss(foodTimeStr);

    // Declare variables for data
    int year, month, day, hour, minute;

    // Reading data from stream
    iss >> year >> month >> day >> hour >> minute;

    // Creating time object
    std::tm timeStruct = {};
    timeStruct.tm_year = year - 1900;
    timeStruct.tm_mon = month - 1;
    timeStruct.tm_mday = day;
    timeStruct.tm_hour = hour;
    timeStruct.tm_min = minute;

    // Convert to a time object using std::chrono
    auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&timeStruct));

    // Convert data to a time
    std::ostringstream oss;
    oss << std::put_time(&timeStruct, "%Y-%m-%d %H:%M:%S");

    std::string formattedTime = oss.str();

    return formattedTime;
}
