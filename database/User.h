#ifndef TELEGRAMBOT_USER_H
#define TELEGRAMBOT_USER_H


#include <string>
#include "../stock/Order.h"

struct User {
    int dId;
    int64_t id;
    std::string firstName;
    std::string lastName;
    double money;
};

#endif //TELEGRAMBOT_USER_H
