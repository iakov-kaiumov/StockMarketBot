#ifndef TELEGRAMBOT_CONTROLLER_H
#define TELEGRAMBOT_CONTROLLER_H

#include <iostream>
#include <stdio.h>
#include <set>
#include <tgbot/tgbot.h>
#include "../database/MyDatabase.h"
#include "../database/User.h"
#include "../stock/Order.h"
#include "../stock/StockMarket.h"
#include "../view/KeyboardFactory.h"


class Controller {
public:
    Controller(const std::string& key);
    void run();
private:
    void onMessage(TgBot::Message::Ptr message);
    void onStartCommand(TgBot::Message::Ptr message);
    std::string returnOrders(User *user);
    std::string returnOrdersToClose(User *user);
    TgBot::Bot *bot;
    MyDatabase dataBase;
    StockMarket stockMarket;
    StringResource res;
    std::map<int64_t, std::string> idsWithUnopenedOrder;
    std::set<int64_t> idsWithUnclosedOrder;

    std::string loc = "en";
};

#endif //TELEGRAMBOT_CONTROLLER_H
