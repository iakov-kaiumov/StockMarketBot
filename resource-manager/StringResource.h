#ifndef TELEGRAMBOT_STRINGRESOURCE_H
#define TELEGRAMBOT_STRINGRESOURCE_H


#include <string>
#include <vector>
#include <map>
#include <locale>

class StringResource {
public:
    StringResource();
    std::string get(const std::string& key, const std::string& locale = "en");
    bool equal(const std::string& key, const std::string& value);
private:
    void load();
    std::map<std::string, std::map<std::string, std::string>> m;
    std::map<std::string, std::vector<std::string>> equalMap;
};


#endif //TELEGRAMBOT_STRINGRESOURCE_H
