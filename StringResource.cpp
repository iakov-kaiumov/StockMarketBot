#include "StringResource.h"
#include <rapidxml.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <cstring>
#include <algorithm>


using namespace std;
using namespace rapidxml;

StringResource::StringResource() {
    load();
}

std::string StringResource::get(const std::string& key, const std::string& locale) {
    string loc = locale;
    if (m.count(locale) == 0)
        loc = "en";
    if (m[loc].count(key) == 0)
        throw runtime_error("StringResources: invalid key");
    return m[loc][key];
}

void read_directory(const std::string& path, vector<string>& v) {
    DIR* dir = opendir(path.c_str());
    struct dirent * dp;
    while ((dp = readdir(dir)) != nullptr) {
        if (strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, ".") != 0) {
            v.emplace_back(path + dp->d_name);
        }
    }
    closedir(dir);
}

void StringResource::load() {
    vector<string> files;
    read_directory("strings/", files);

    int i = 0;
    for (auto &path : files) {
        string locale = path.substr(path.size() - 6, 2);
        xml_document<> doc;
        xml_node<> *root_node;
        // Read the xml file into a vector
        ifstream file(path);
        vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        buffer.push_back('\0');
        // Parse the buffer using the xml file parsing library into doc
        doc.parse<0>(&buffer[0]);
        // Find our root node
        root_node = doc.first_node("resources");
        map<string, string> locMap;
        for (xml_node<> *node = root_node->first_node("string"); node; node = node->next_sibling()) {
            auto key = node->first_attribute("name")->value();
            auto value = node->value();
            locMap.insert(pair(key, value));

            if (i == 0) {
                equalMap.insert(pair(key, vector<string>()));
            }
            equalMap[key].emplace_back(value);
        }
        m.insert(pair(locale, locMap));
        i++;
    }
}

bool StringResource::equal(const std::string &key, const std::string &value) {
    auto v = equalMap[key];
    return std::find(v.begin(), v.end(), value) != v.end();
}
