#ifndef TELEGRAMBOT_PRICE_H
#define TELEGRAMBOT_PRICE_H

#include <ctime>
#include <string>

class Price {
public:
    long long dId;
    std::string share;
    time_t time;
    double ask;
    double bid;
    std::string toString() {
        return share + ": " + std::to_string(bid) + "$ - " + std::to_string(ask) + "$ ";
    }
};

#endif //TELEGRAMBOT_PRICE_H
