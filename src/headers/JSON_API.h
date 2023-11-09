#ifndef JSON_API_H
#define JSON_API_H

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>
#include <ctime>

class JSON_API {
private:
    rapidjson::Document jsonData;
    std::string filename;

    // Вспомогательные методы
    bool fileExists() const;
    bool loadJsonFromFile();
    void saveJsonToFile() const;

public:
    JSON_API(const std::string& filename);
    int foodTimeDiff() const;
    std::time_t restTimeDiff() const;
    void updateFoodTime();
    void updateRestTime();
    std::time_t parseDateTime(const std::string& dateTimeStr) const;
    int getState() const;
    std::string convertJsonDate(std::string jsonDate) const;
};

#endif // JSON_API_H