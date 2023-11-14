#ifndef JSON_API_H
#define JSON_API_H

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

class JSON_API {
private:
    rapidjson::Document jsonData;
    std::string filename;

    // Вспомогательные методы
    bool fileExists() const;
    bool loadJsonFromFile();
    void saveJsonToFile() const;
    static bool isInteger(const std::string& s) ;

public:
    JSON_API(const std::string& filename);
    int foodTimeDiff();
    int restTimeDiff();
    void updateFoodTime();
    void updateRestTime();
    int parseDateTime(const std::string& dateTimeStr) const;
    int getFoodState();
    std::string convertJsonDate(const std::string& jsonDate) const;
    std::string getActualDate();
    int getRestState();
};

#endif // JSON_API_H