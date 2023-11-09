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

    bool fileExists(const std::string& filename) const;
    bool loadJsonFromFile(const std::string& filename);
    void saveJsonToFile(const std::string& filename) const;
    std::time_t parseDateTime(const std::string& dateTimeStr) const;

public:
    JSON_API(const std::string& filename);

    std::time_t foodTimeDiff() const;
    std::time_t restTimeDiff() const;
};

#endif // JSON_API_H