//
// Created by kostiantyn on 11/7/23.
//

#include "JSON_API.h"
#define MINUTES_IN_DAY 1440
#define MINUTES_IN_HOURS 60
#define MINUTES_IN_YEAR 525600
#define MINUTES_IN_MONTH 43200
#define _CRT_SECURE_NO_WARNINGS

JSON_API::JSON_API(const std::string& filename) : filename(filename) {
    if (fileExists()) {
        if (!loadJsonFromFile()) {
            std::cerr << "Error loading JSON from file: " << filename << std::endl;
        }
    }
    else {
        jsonData.SetObject();
        saveJsonToFile();
    }
}

bool JSON_API::isInteger(const std::string& s) {
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
    }
    else {
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

    std::cout << "Before restTime: " << std::endl;
    saveJsonToFile();

    jsonData["restTime"].SetString(buffer, static_cast<rapidjson::SizeType>(strlen(buffer)));

    std::cout << "After restTime: " << jsonData["restTime"].GetString() << std::endl;
    saveJsonToFile();
}

int JSON_API::getFoodState() {
    int foodTimeDifference = foodTimeDiff();
    std::cout << foodTimeDiff() << std::endl;
    if (foodTimeDifference > 10 && foodTimeDifference < 19) {
        return 1;
    }
    else if (foodTimeDifference > 20 && foodTimeDifference < 29) {
        return 2;
    }
    else if (foodTimeDifference > 30 && foodTimeDifference < 39) {
        return 3;
    }
    else if (foodTimeDifference > 40 && foodTimeDifference < 49) {
        return 4;
    }
    else if (foodTimeDifference > 50) {
        return 5;
    }
    else {
        return 0;
    }
}

std::string JSON_API::convertJsonDate(const std::string& jsonDate) const {
    std::string foodTimeStr = jsonDate;
    return foodTimeStr;
}

int JSON_API::parseDateTime(const std::string& dateTimeStr) const {
    std::string delimiter = ":";
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::vector<int> res;
    std::string token;

    while ((pos_end = dateTimeStr.find(delimiter, pos_start)) != std::string::npos) {
        token = dateTimeStr.substr(pos_start, pos_end - pos_start);
        res.push_back(stoi(token));
        pos_start = pos_end + delim_len;
    }
    token = dateTimeStr.substr(pos_start);
    res.push_back(stoi(token));

    if (res.size() != 5) {
        return -1;
    }

    int minSum = (res[0] - 2022) * MINUTES_IN_YEAR + res[1] * MINUTES_IN_MONTH + res[2] * MINUTES_IN_DAY + res[3] * MINUTES_IN_HOURS + res[4];
    return minSum;
}

std::string JSON_API::getActualDate() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&currentTime);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y:%m:%d:%H:%M", timeInfo);

    jsonData["actualTime"].SetString(buffer, static_cast<rapidjson::SizeType>(strlen(buffer)));

    saveJsonToFile();

    return jsonData["actualTime"].GetString();
}

int JSON_API::getRestState() {
    int restTimeDifference = restTimeDiff();
    std::cout << restTimeDiff() << std::endl;
    if (restTimeDifference > 10 && restTimeDifference < 19) {
        return 1;
    }
    else if (restTimeDifference > 20 && restTimeDifference < 29) {
        return 2;
    }
    else if (restTimeDifference > 30 && restTimeDifference < 39) {
        return 3;
    }
    else if (restTimeDifference > 40 && restTimeDifference < 49) {
        return 4;
    }
    else if (restTimeDifference > 50) {
        return 5;
    }
    else {
        return 0;
    }
}

