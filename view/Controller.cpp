#include "Controller.h"

Controller::Controller(const std::string& key) {
    bot = new TgBot::Bot(key);
    dataBase.init();
    stockMarket.init(&dataBase);
}

bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void Controller::onStartCommand(TgBot::Message::Ptr message) {
    User user;
    user.id = message->chat->id;
    user.firstName = message->chat->firstName;
    user.lastName = message->chat->lastName;
    user.money = 1000;
    dataBase.insertUser(user);
    bot->getApi().sendMessage(message->chat->id, res.get("HELLO_TEXT", loc), false, 0, KeyboardFactory::mainKeyboard(res, loc));

    std::cout << "New user : " << user.id << std::endl;
}

void Controller::onMessage(TgBot::Message::Ptr message) {

    printf("User wrote:'%s'\n", message->text.c_str());
    // Check whether the user is in the database or not
    auto user = dataBase.getUserById(message->chat->id);
    if (user == nullptr) {
        bot->getApi().sendMessage(message->chat->id, res.get("RESTART_LABEL", loc));
        return;
    }
    auto text = message->text;
    if (res.equal("PRICE_BUTTON", text)) {
        std::string msg = res.get("PRICE_LABEL", loc) + "\n";
        int i = 1;
        for (auto &share : StockMarket::shares) {
            msg += std::to_string(i) + ". " +stockMarket.getCurrentPrice(share).toString() + "\n";
            i++;
        }
        bot->getApi().sendMessage(message->chat->id, msg);
    }
    if (res.equal("GRAPH_BUTTON", text)) {
        bot->getApi().sendMessage(message->chat->id, res.get("TIME_LABEL", loc),
                false, 0, KeyboardFactory::timeKeyboard(res, loc));
    } else
    if (res.equal("TIME1_BUTTON", text)) {
        time_t since = 3600;
        bot->getApi().sendPhoto(message->chat->id,
                               TgBot::InputFile::fromFile(stockMarket.getGraph(StockMarket::shares, since), "image/jpeg"), "", 0, KeyboardFactory::mainKeyboard(res, loc));
    } else
    if (res.equal("TIME2_BUTTON", text)) {
        time_t since = 24 * 3600;
        bot->getApi().sendPhoto(message->chat->id,
                               TgBot::InputFile::fromFile(stockMarket.getGraph(StockMarket::shares, since), "image/jpeg"), "", 0, KeyboardFactory::mainKeyboard(res, loc));
    } else
    if (res.equal("TIME3_BUTTON", text)) {
        time_t since = 7 * 24 * 3600;
        bot->getApi().sendPhoto(message->chat->id,
                               TgBot::InputFile::fromFile(stockMarket.getGraph(StockMarket::shares, since), "image/jpeg"), "", 0, KeyboardFactory::mainKeyboard(res, loc));
    } else
    if (res.equal("TIME4_BUTTON", text)) {
        time_t since = 30 * 24 * 3600;
        bot->getApi().sendPhoto(message->chat->id,
                               TgBot::InputFile::fromFile(stockMarket.getGraph(StockMarket::shares, since), "image/jpeg"), "", 0, KeyboardFactory::mainKeyboard(res, loc));
    } else
    if (res.equal("INFO_BUTTON", text)) {
        bot->getApi().sendMessage(message->chat->id, "Information");
    } else
    if (res.equal("ORDERS_BUTTON", text)) {
        bot->getApi().sendMessage(message->chat->id, returnOrders(user));
    } else
    if (res.equal("CLOSE_BUTTON", text)) {
        auto user = dataBase.getUserById(message->chat->id);
        bot->getApi().sendMessage(message->chat->id, returnOrdersToClose(user),
                false, 0, KeyboardFactory::cancelKeyboard(res, loc));
    } else
    if (res.equal("NEW_BUTTON", text)) {
        bot->getApi().sendMessage(message->chat->id, "Choose the share", false, 0, KeyboardFactory::shareKeyboard(res, loc));
    } else
    if (res.equal("K_BUTTON", text) || res.equal("P_BUTTON", text)) {
        idsWithUnopenedOrder.insert(std::pair<int64_t, std::string>(message->chat->id, message->text));
        bot->getApi().sendMessage(message->chat->id, "Please, enter the amount of share below (only integer):");
    } else
    if (res.equal("CANCEL_BUTTON", text)) {
        idsWithUnopenedOrder.erase(message->chat->id);
        idsWithUnclosedOrder.erase(message->chat->id);
        bot->getApi().sendMessage(message->chat->id, res.get("CANCEL_BUTTON", loc), false, 0, KeyboardFactory::mainKeyboard(res, loc));
    } else
    if (idsWithUnopenedOrder.count(message->chat->id) == 1) {
        if (is_number(message->text)) {
            std::string share = idsWithUnopenedOrder[message->chat->id];
            int amount = std::stoi(message->text);
            double bid =  stockMarket.getCurrentPrice(share).bid;
            if (user->money < bid * amount) {
                bot->getApi().sendMessage(message->chat->id, res.get("NO_MONEY", loc), false, 0, KeyboardFactory::mainKeyboard(res, loc));
            } else {
                user->money -= bid * amount;
                Order o { 0, user->id, share, amount, bid, 0, true };
                dataBase.addNewOrder(o);
                stockMarket.updatePrice(share, amount);
                bot->getApi().sendMessage(message->chat->id, res.get("SUCCESS", loc), false, 0, KeyboardFactory::mainKeyboard(res, loc));
            }
        } else {
            bot->getApi().sendMessage(message->chat->id, "", false, 0, KeyboardFactory::mainKeyboard(res, loc));
        }
        idsWithUnopenedOrder.erase(message->chat->id);
    } else
    if (idsWithUnclosedOrder.count(message->chat->id) == 1) {
        if (is_number(message->text)) {
            int index = std::stoi(message->text) - 1;
            auto orders = dataBase.getUserOrders(user->id);
            if (index >= orders.size() || index < 0) {
                bot->getApi().sendMessage(message->chat->id, "No such order", false, 0, KeyboardFactory::mainKeyboard(res, loc));
                return;
            }
            Order order = orders[index];
            double ask = stockMarket.getCurrentPrice(order.share).ask;
            user->money += order.amount * ask;
            order.isOpen = false;
            order.closePrice = ask;
            stockMarket.updatePrice(order.share, order.amount);
            dataBase.updateOrder(order);
            dataBase.insertUser(*user);
            bot->getApi().sendMessage(message->chat->id, res.get("SUCCESS", loc), false, 0, KeyboardFactory::mainKeyboard(res, loc));
        } else {
            bot->getApi().sendMessage(message->chat->id, res.get("WRONG_INPUT", loc), false, 0, KeyboardFactory::mainKeyboard(res, loc));
        }
        idsWithUnclosedOrder.erase(message->chat->id);
    }
}

void Controller::run() {
    bot->getEvents().onCommand("start", [this] (TgBot::Message::Ptr message) {
        onStartCommand(message);
    });

    bot->getEvents().onNonCommandMessage([this] (TgBot::Message::Ptr message) {
        onMessage(message);
    });

    try {
        printf("Bot username: %s\n", bot->getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(*bot);
        while (true) {
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("Error: %s\n", e.what());
    }
}

std::string Controller::returnOrdersToClose(User *user) {
    std::string text = res.get("CLOSE_LABEL_1", loc);
    auto orders = dataBase.getUserOrders(user->id);
    if (orders.empty()) {
        text = res.get("EMPTY_ORDERS", loc);
    } else {
        idsWithUnclosedOrder.insert(user->id);
        for (int i=0; i<orders.size(); i++) {
            Order order = orders[i];
            double profit = (stockMarket.getCurrentPrice(order.share).ask - order.openPrice) * order.amount;
            text += std::to_string(i + 1) + ". " + order.share + res.get("SHARE_INFO", loc)
                    + std::to_string(profit) + "$\n";
        }
    }
    return text;
}

std::string Controller::returnOrders(User *user) {
    std::string text = res.get("MONEY_INFO", loc) + std::to_string(user->money) + "$\n";
    auto orders = dataBase.getUserOrders(user->id);
    if (orders.empty()) {
        text += res.get("EMPTY_ORDERS", loc);
    } else {
        text += "Orders: \n";
        for (int i=0; i<orders.size(); i++) {
            Order order = orders[i];
            double profit = (stockMarket.getCurrentPrice(order.share).ask - order.openPrice) * order.amount;
            text += std::to_string(i + 1) + ". " + order.share + res.get("SHARE_INFO", loc)
                    + std::to_string(profit) + "$\n";
        }
    }
    return text;
}
