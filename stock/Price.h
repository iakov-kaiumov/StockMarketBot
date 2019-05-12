#ifndef TELEGRAMBOT_PRICE_H
#define TELEGRAMBOT_PRICE_H

#include <ctime>
#include <string>
#include <fmt/core.h>

class Price {
public:
    long long dId;
    std::string share;
    time_t time;
    double ask;
    double bid;
    std::string toString() {
        return share + ": " + fmt::format("{:.2f}", bid) + "$ - " + fmt::format("{:.2f}", ask) + "$ ";
    }
};

#endif //TELEGRAMBOT_PRICE_H
