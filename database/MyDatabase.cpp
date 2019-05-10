#include <iostream>
#include <algorithm>
#include "MyDatabase.h"

void MyDatabase::init() {
    storage.sync_schema();
}

User *MyDatabase::getUserById(int64_t id) {
    for (auto &u : storage.get_all<User>(where(c(&User::id) == id))) {
        return &u;
    }
    return nullptr;
}

void MyDatabase::insertUser(User &user) {
    if (storage.get_all<User>(where(c(&User::id) == user.id)).empty())
        storage.insert(user);
    else
        storage.update(user);
}

void MyDatabase::addNewOrder(Order& order) {
    storage.insert(order);
}

std::vector<Order> MyDatabase::getUserOrders(int64_t id, bool isOpen) {
    return storage.get_all<Order>(where(c(&Order::id) == id && c(&Order::isOpen) == isOpen));
}

void MyDatabase::updateOrder(Order& order) {
    storage.update(order);
}

void MyDatabase::insertPrice(Price& price) {
    storage.insert(price);
}

std::vector<Price> MyDatabase::getPricesSince(std::string& share, time_t since) {
    return storage.get_all<Price>(where(c(&Price::share) == share && c(&Price::time) > since), order_by(&Price::time));
}

std::string MyDatabase::dumpPricesSince(std::string& share, time_t since) {
    auto prices = storage.get_all<Price>(where(c(&Price::share) == share && c(&Price::time) > since),
            order_by(&Price::time));
    std::string json = "\"" + share + "\": [";
    for (auto &p : prices) {
        auto s = storage.dump(p);
        std::replace(s.begin(), s.end(), '\'', '\"');
        json += s + ", ";
    }
    json += "]";
    return json;
}

Price MyDatabase::getLastPrice(std::string &share) {
    auto p = storage.get_all<Price>(where(c(&Price::share) == share), order_by(&Price::time));
    if (p.empty()) {
        throw std::out_of_range("DB: getLastPrice() array is empty");
    }
    return p.back();
}

void MyDatabase::insertSP(SP &sp) {
    if (storage.get_all<SP>(where(c(&SP::share) == sp.share)).empty())
        storage.insert(sp);
    else
        storage.update(sp);
}

SP MyDatabase::getSP(std::string &share) {
    auto p = storage.get_all<SP>(where(c(&SP::share) == share));
    if (p.empty()) {
        throw std::out_of_range("DB: getSP() array is empty");
    }
    return p.back();
}

void MyDatabase::initPrices(std::string &share) {
    storage.transaction([&] () mutable {
        auto now = std::time(nullptr);
        for (int i=3600 * 24 * 7; i > 0; i -= 3600) {
            double ask = 98 + 0.5 * (rand() % 10);
            double bid = ask + 1 + 0.2 * (rand() % 10);
            for (int j=0; j<3600; j+= 300) {
                auto time = now - i + j;
                Price p {0, share, time, ask, bid};
                storage.insert(p);
            }
        }
        return true;
    });
}
