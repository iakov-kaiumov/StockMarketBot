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
    std::string locale;
    std::string graphView;
};

//    std::string toString() {
//        return "dId " + std::to_string(dId) + "\n" +
//                "id " + std::to_string(id) + "\n" +
//                "firstName " + firstName + "\n" +
//                "lastName " + lastName + "\n" +
//                "money " + std::to_string(money) + "\n" +
//                "locale " + locale + "\n" +
//                "graphView " + graphView + "\n";
//    }

#endif //TELEGRAMBOT_USER_H
