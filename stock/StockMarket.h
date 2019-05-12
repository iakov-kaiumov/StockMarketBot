#ifndef TELEGRAMBOT_STOCKMARKET_H
#define TELEGRAMBOT_STOCKMARKET_H

#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include "Price.h"
#include "Stock.h"
#include "../database/MyDatabase.h"
#include "Timer.h"

class StockMarket {
public:
    Price getCurrentPrice(std::string& share);
    void init(MyDatabase *_database);
    void updatePrice(std::string& share, int amount);
    std::string getGraph(std::vector<std::string> keys, time_t since, std::string& style);
    inline static std::vector<std::string> shares = {"K", "P"};
private:
    void timePriceChange();
    MyDatabase *database;
    std::map<std::string, Price> lastPrices;
    std::map<std::string, Stock> stocks;

    Timer timer;

    const double SI_LOW = 0.35;
    const double SI_HIGH = 0.80;
    time_t allowedTimeGap = 60;
    const double alpha = 0.7;
    const double beta = 1.005;
};

#endif //TELEGRAMBOT_STOCKMARKET_H
