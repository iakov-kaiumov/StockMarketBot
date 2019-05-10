#ifndef TELEGRAMBOT_STOCKMARKET_H
#define TELEGRAMBOT_STOCKMARKET_H

#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include "Price.h"
#include "../database/MyDatabase.h"

class StockMarket {
public:
    Price getCurrentPrice(std::string& share);
    void init(MyDatabase *_database);
    void updatePrice(std::string& share, int amount);
    std::string getGraph(std::vector<std::string> keys, time_t since);
    inline static std::vector<std::string> shares = {"K", "P"};
private:
    MyDatabase *database;
    std::map<std::string, Price> lastPrices;
    std::map<std::string, SP> sp;
};

#endif //TELEGRAMBOT_STOCKMARKET_H
