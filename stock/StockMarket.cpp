#include <cstdlib>
#include <thread>
#include <ctime>
#include <fstream>
#include <cmath>
#include "StockMarket.h"


double StockMarket::getCurrentPrice(std::string share) {
    return lastPrices[share].back().ask;
}

void StockMarket::init(MyDatabase *_database) {
    database = _database;
    auto now = std::time(nullptr);
    for (auto &share : shares) {
        lastPrices.insert(std::pair(share, database->getPricesSince(share, now - 3600 * 24)));
    }
//    int m = 100;
//    for (int i=0; i<m; i++) {
//        auto time = std::time(nullptr) - m * 24 * 7 + 24 * 7 * i;
//        for (auto &share : shares) {
//            Price p;
//            p.share = share;
//            p.time = time;
//            p.ask = p.bid = sin(i / 1000.0 * (int) share[0]) * (int) share[0] / 5.0 + 50.0;
//            lastPrices[share].push_back(p);
//            database->addNewPrice(p);
//        }
//    }
}

void StockMarket::updatePrice(std::string share, double amount) {
    double price = lastPrices[share].back().ask;
    auto time = std::time(nullptr);
    Price newPrice {0, share, time, price, price };
    database->addNewPrice(newPrice);
}

std::string StockMarket::getGraph(std::vector<std::string> keys, time_t since) {
    std::ofstream file;
    file.open("graphics/data.txt");
    auto time = std::time(nullptr) - since;
    for (auto &key : keys) {
        file << key << std::endl;
        for (auto &p : database->getPricesSince(key, time)) {
            if (p.time > time) {
                file << p.time << " ";
            }
        }
        file << std::endl;
        for (auto &p : database->getPricesSince(key, time)) {
            if (p.time > time) {
                file << p.ask << " ";
            }
        }
        file << std::endl;
    }
    file.close();
    std::string command = "python ../plot.py";
    system(command.c_str());
    return "graphics/image.png";
}
