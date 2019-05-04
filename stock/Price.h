#ifndef TELEGRAMBOT_PRICE_H
#define TELEGRAMBOT_PRICE_H

#include <ctime>
#include <string>

struct Price {
    long long dId;
    std::string share;
    time_t time;
    double ask;
    double bid;
};

#endif //TELEGRAMBOT_PRICE_H
