#ifndef TELEGRAMBOT_ORDER_H
#define TELEGRAMBOT_ORDER_H

struct Order {
    int dId;
    int64_t id;
    std::string share;
    double amount;
    double openPrice;
    double closePrice;
    bool isOpen;
};

#endif //TELEGRAMBOT_ORDER_H
