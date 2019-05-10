#include <cstdlib>
#include <thread>
#include <ctime>
#include <fstream>
#include <cmath>
#include "StockMarket.h"

int sign(int x) {
    return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
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
            sp.insert(std::pair(share, database->getSP(share)));
        } catch (std::out_of_range& e) {
            SP _sp {0, share, 0, 0, 1, 10};
            database->insertSP(_sp);
            sp.insert(std::pair(share, _sp));
        }
    }
}

Price StockMarket::getCurrentPrice(std::string& share) {
    return lastPrices[share];
}

void StockMarket::updatePrice(std::string& share, int amount) {
    auto time = std::time(nullptr);
    Price lastPrice = lastPrices[share];
    Price newPrice {0, share, time, 0, 0 };

    sp[share].NASP += amount * sign(amount);
    sp[share].NSP += amount * lastPrice.bid * sign(amount);
    newPrice.ask = sp[share].NSP / sp[share].NASP;
    newPrice.bid = lastPrice.bid + pow(sp[share].a * sp[share].NASP / sp[share].Q, 1);
    std::cout << "LAST PRICE: " << lastPrice.toString() << std::endl;
    std::cout << "NEW PRICE: " << newPrice.toString() << std::endl;
    lastPrices[share] = newPrice;
    database->insertSP(sp[share]);
    database->insertPrice(newPrice);
}

std::string StockMarket::getGraph(std::vector<std::string> keys, time_t since) {
    std::ofstream file;
    file.open("graphics/data.txt");
    auto time = std::time(nullptr) - since;
    for (auto &key : keys) {
        std::cout << database->dumpPricesSince(key, time) << std::endl;
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
