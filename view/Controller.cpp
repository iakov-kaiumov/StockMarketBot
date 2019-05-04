#include "Controller.h"

Controller::Controller(std::string key) {
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
    user.money = 100;
    dataBase.addNewUser(user);
    bot->getApi().sendMessage(message->chat->id, PHRASES::HELLO_TEXT, false, 0, KeyboardFactory::mainKeyboard());

    std::cout << "New user : " << user.id << std::endl;
}

void Controller::onMessage(TgBot::Message::Ptr message) {
    std::vector<std::string> keys;
    keys.push_back("K");
    keys.push_back("P");

    printf("User wrote %s\n", message->text.c_str());

    if (message->text == PHRASES::PRICE_BUTTON) {
        bot->getApi().sendMessage(message->chat->id,
                                 "Current prices are: \n K: " + std::to_string(stockMarket.getCurrentPrice("K")) + " $\n"
                                                                                                                   " P: " + std::to_string(stockMarket.getCurrentPrice("P")) + " $");
    }
    if (message->text == PHRASES::GRAPH_BUTTON) {
        bot->getApi().sendMessage(message->chat->id, "Choose time interval", false, 0, KeyboardFactory::timeKeyboard());
    } else
    if (message->text == PHRASES::TIME1_BUTTON) {
        time_t since = 3600;
        bot->getApi().sendPhoto(message->chat->id,
                               TgBot::InputFile::fromFile(stockMarket.getGraph(keys, since), "image/jpeg"), "", 0, KeyboardFactory::mainKeyboard());
    } else
    if (message->text == PHRASES::TIME2_BUTTON) {
        time_t since = 24 * 3600;
        bot->getApi().sendPhoto(message->chat->id,
                               TgBot::InputFile::fromFile(stockMarket.getGraph(keys, since), "image/jpeg"), "", 0, KeyboardFactory::mainKeyboard());
    } else
    if (message->text == PHRASES::TIME3_BUTTON) {
        time_t since = 7 * 24 * 3600;
        bot->getApi().sendPhoto(message->chat->id,
                               TgBot::InputFile::fromFile(stockMarket.getGraph(keys, since), "image/jpeg"), "", 0, KeyboardFactory::mainKeyboard());
    } else
    if (message->text == PHRASES::TIME4_BUTTON) {
        time_t since = 30 * 24 * 3600;
        bot->getApi().sendPhoto(message->chat->id,
                               TgBot::InputFile::fromFile(stockMarket.getGraph(keys, since), "image/jpeg"), "", 0, KeyboardFactory::mainKeyboard());
    } else
    if (message->text == PHRASES::INFO_BUTTON) {
        bot->getApi().sendMessage(message->chat->id, "Information");
    } else
    if (message->text == PHRASES::ORDERS_BUTTON) {
        auto user = dataBase.getUserById(message->chat->id);
        if (user == nullptr)
            return;
        std::string text = "Available money: " + std::to_string(user->money) + "$\n";
        auto orders = dataBase.getUserOrders(user->id);
        if (orders.empty()) {
            text += "No open orders";
        } else {
            text += "Orders: \n";
            for (int i=0; i<orders.size(); i++) {
                Order order = orders[i];
                double profit = (stockMarket.getCurrentPrice(order.share) - order.openPrice) * order.amount;
                text += std::to_string(i + 1) + ". " + order.share +
                        " share with current profit " + std::to_string(profit) + "$\n";
            }
        }
        bot->getApi().sendMessage(message->chat->id, text);
    } else
    if (message->text == PHRASES::CLOSE_BUTTON) {
        auto user = dataBase.getUserById(message->chat->id);
        if (user == nullptr)
            return;
        std::string text = "Enter the number of share to close\n";
        auto orders = dataBase.getUserOrders(user->id);
        if (orders.empty()) {
            text = "No open orders";
        } else {
            idsWithUnclosedOrder.insert(message->chat->id);
            for (int i=0; i<orders.size(); i++) {
                Order order = orders[i];
                double profit = (stockMarket.getCurrentPrice(order.share) - order.openPrice) * order.amount;
                text += std::to_string(i + 1) + ". " + order.share +
                        " share with current profit " + std::to_string(profit) + "$\n";
            }
        }
        bot->getApi().sendMessage(message->chat->id, text, false, 0, KeyboardFactory::cancelKeyboard());
    } else
    if (message->text == PHRASES::NEW_BUTTON) {
        bot->getApi().sendMessage(message->chat->id, "Choose the share", false, 0, KeyboardFactory::shareKeyboard());
    } else
    if (message->text == PHRASES::K_BUTTON || message->text == PHRASES::P_BUTTON) {
        idsWithUnopenedOrder.insert(std::pair<int64_t, std::string>(message->chat->id, message->text));
        bot->getApi().sendMessage(message->chat->id, "Please, enter the amount of share below (only integer):");
    } else
    if (message->text == PHRASES::CANCEL_BUTTON) {
        idsWithUnopenedOrder.erase(message->chat->id);
        idsWithUnclosedOrder.erase(message->chat->id);
        bot->getApi().sendMessage(message->chat->id, "Cancel", false, 0, KeyboardFactory::mainKeyboard());
    } else
    if (idsWithUnopenedOrder.count(message->chat->id) == 1) {
        if (is_number(message->text)) {
            std::string share = idsWithUnopenedOrder[message->chat->id];
            double amount = std::stoi(message->text);
            double currentPrice =  stockMarket.getCurrentPrice(share);
            auto user = dataBase.getUserById(message->chat->id);
            if (user == nullptr)
                return;
            if (user->money < currentPrice * amount) {
                bot->getApi().sendMessage(message->chat->id, "Not enough money!", false, 0, KeyboardFactory::mainKeyboard());
            } else {
                user->money -= currentPrice * amount;
                dataBase.addNewOrder({ 0, user->id, share, amount, currentPrice, 0, true });
                stockMarket.updatePrice(share, amount);
                bot->getApi().sendMessage(message->chat->id, "Successfully!", false, 0, KeyboardFactory::mainKeyboard());
            }
        } else {
            bot->getApi().sendMessage(message->chat->id, "", false, 0, KeyboardFactory::mainKeyboard());
        }
        idsWithUnopenedOrder.erase(message->chat->id);
    } else
    if (idsWithUnclosedOrder.count(message->chat->id) == 1) {
        if (is_number(message->text)) {
            int index = std::stoi(message->text) - 1;
            auto user = dataBase.getUserById(message->chat->id);
            if (user == nullptr)
                return;
            auto orders = dataBase.getUserOrders(user->id);
            if (index >= orders.size() || index < 0) {
                bot->getApi().sendMessage(message->chat->id, "No such order", false, 0, KeyboardFactory::mainKeyboard());
                return;
            }
            Order order = orders[index];
            double currentPrice = stockMarket.getCurrentPrice(order.share);
            user->money += order.amount * currentPrice;
            order.isOpen = false;
            order.closePrice = currentPrice;
            stockMarket.updatePrice(order.share, order.amount);
            dataBase.updateOrder(order);
            bot->getApi().sendMessage(message->chat->id, "Successfully!", false, 0, KeyboardFactory::mainKeyboard());
        } else {
            bot->getApi().sendMessage(message->chat->id, "Wrong input", false, 0, KeyboardFactory::mainKeyboard());
        }
        idsWithUnclosedOrder.erase(message->chat->id);
    }
}

void Controller::run() {
    bot->getEvents().onCommand("start", [this](TgBot::Message::Ptr message) {
        onStartCommand(message);
    });

    bot->getEvents().onNonCommandMessage([this](TgBot::Message::Ptr message) {
        onMessage(message);
    });

    try {
        printf("Bot username: %s\n", bot->getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(*bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
}
