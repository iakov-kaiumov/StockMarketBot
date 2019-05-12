#ifndef TELEGRAMBOT_DATA_H
#define TELEGRAMBOT_DATA_H

#include <string>

struct Stock {
    int dId = 0;
    std::string share;
    double NASP = 0;
    double NSP = 0;
    double P = 100;
    int TOTAL_SHARES = 10;
    int BOUGHT_SHARES = 0;
    time_t lastTransaction;
};

#endif //TELEGRAMBOT_DATA_H
