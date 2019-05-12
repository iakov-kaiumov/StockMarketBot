#include <cstdlib>
#include <thread>
#include <ctime>
#include <fstream>
#include <cmath>
#include "StockMarket.h"

int sign(int x) {
    return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

int indicator(time_t dt1, time_t dt2) {
    return (dt1 < dt2) ? 0 : 1;
}

void StockMarket::init(MyDatabase *_database) {
    database = _database;
    for (auto &share : shares) {
        try {
            lastPrices.insert(std::pair(share, database->getLastPrice(share)));
        } catch (std::out_of_range& e) {
            database->initPrices(share);
            lastPrices.insert(std::pair(share, database->getLastPrice(share)));
        }
        try {
            stocks.insert(std::pair(share, database->getStock(share)));
        } catch (std::out_of_range& e) {
            // IPO
            Stock s;
            s.share = share;
            database->insertStock(s);
            stocks.insert(std::pair(share, s));
        }
    }
    timer.add(30 * 1000, [this]() { timePriceChange(); });
}

Price StockMarket::getCurrentPrice(std::string& share) {
    return lastPrices[share];
}

void StockMarket::updatePrice(std::string& share, int amount) {
    auto time = std::time(nullptr);
    Price lastPrice = lastPrices[share];
    Price newPrice {0, share, time, 0, 0 };

    stocks[share].lastTransaction = time;
    // Increase counter
    stocks[share].BOUGHT_SHARES += amount;
    // CEO
    if (stocks[share].BOUGHT_SHARES > stocks[share].TOTAL_SHARES) {
        stocks[share].TOTAL_SHARES += 10;
    }
    // Calculate new prices
    int s = sign(amount);
    stocks[share].NASP += amount * s;
    stocks[share].NSP += amount * lastPrice.bid * s;
    if (s == 1) {
        newPrice.ask = std::min(beta * stocks[share].NSP / stocks[share].NASP, lastPrice.ask);
    } else {
        newPrice.ask = stocks[share].NSP / stocks[share].NASP;
    }
    newPrice.bid = 1.0 * pow(stocks[share].NASP, alpha) + stocks[share].P / stocks[share].TOTAL_SHARES;
    // Saving new prices
    lastPrices[share] = newPrice;
    database->insertStock(stocks[share]);
    database->insertPrice(newPrice);

    // Printing
    std::cout << "+---------------" << std::endl;
    std::cout << "| TRANSACTION" << std::endl;
    std::cout << "| Amount " << amount << std::endl;
    std::cout << "| LAST PRICE: " << lastPrice.toString() << std::endl;
    std::cout << "| NEW PRICE: " << newPrice.toString() << std::endl << std::endl;
    std::cout << "+---------------" << std::endl;
}

std::string StockMarket::getGraph(std::vector<std::string> keys, time_t since, std::string& style) {
    auto now = std::time(nullptr);
    std::string command = "python3 ../plot.py " + style + " " + std::to_string(now - since);
    for (auto &key : keys) {
        command += " " + key;
    }
    system(command.c_str());
    return "graphics/image.png";
}

void StockMarket::timePriceChange() {
    auto now = std::time(nullptr);
    for (auto &share : shares) {
        int ind = indicator(now - stocks[share].lastTransaction, allowedTimeGap);
        if (ind == 1)
            stocks[share].lastTransaction = now;
        double M = database->getUserCount() * 100;
        double SI = stocks[share].NSP / M;
        double y = ind * (std::max(SI - SI_HIGH, 0.0) + std::min(SI - SI_LOW, 0.0));
        double c = 1.01 * beta * SI_LOW / (beta - 1);
        double k = 1 + y / c;

        Price lastPrice = lastPrices[share];
        Price newPrice {0, share, now, 0, 0 };
        newPrice.ask *= k;
        newPrice.bid *= k;
        std::cout << "+---------------" << std::endl;
        std::cout << "| Price change due to time" << std::endl;
        std::cout << "| PREVIOUS PRICE: " << lastPrice.toString() << std::endl;
        std::cout << "| NEW PRICE: " << newPrice.toString() << std::endl << std::endl;
        std::cout << "+---------------" << std::endl;
        database->insertPrice(newPrice);
    }
}
