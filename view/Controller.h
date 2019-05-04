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
#include "../Phrases.h"


class Controller {
public:
    Controller();
    void run();

private:
    void onMessage(TgBot::Message::Ptr message);
    void onStartCommand(TgBot::Message::Ptr message);

    TgBot::Bot *bot;
    MyDatabase dataBase;
    StockMarket stockMarket;
    std::map<int64_t, std::string> idsWithUnopenedOrder;
    std::set<int64_t> idsWithUnclosedOrder;
    const std::string key = "694941103:AAEPJCvKYIbj6pmjF16gIiShsaWU-z-t2jc";
};

#endif //TELEGRAMBOT_CONTROLLER_H
