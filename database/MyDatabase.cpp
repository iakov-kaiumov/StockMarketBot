#include <iostream>
#include <algorithm>
#include "MyDatabase.h"

void MyDatabase::init() {
    storage.sync_schema();
}

User MyDatabase::getUserById(int64_t id) {
    for (auto &u : storage.get_all<User>(where(c(&User::id) == id))) {
        return u;
    }
    throw std::logic_error("No user with id: " + std::to_string(id));
}

long MyDatabase::getUserCount() {
    return storage.count<User>();
}

void MyDatabase::insertUser(User user) {
    if (storage.get_all<User>(where(c(&User::id) == user.id)).empty())
        storage.insert(user);
    else
        storage.update(user);
}

void MyDatabase::insertOrder(Order &order) {
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

Price MyDatabase::getLastPrice(std::string &share) {
    auto p = storage.get_all<Price>(where(c(&Price::share) == share), order_by(&Price::time));
    if (p.empty()) {
        throw std::out_of_range("DB: getLastPrice() array is empty");
    }
    return p.back();
}

void MyDatabase::insertStock(Stock &stock) {
    if (storage.get_all<Stock>(where(c(&Stock::share) == stock.share)).empty())
        storage.insert(stock);
    else
        storage.update(stock);
}

Stock MyDatabase::getStock(std::string &share) {
    auto p = storage.get_all<Stock>(where(c(&Stock::share) == share));
    if (p.empty()) {
        throw std::out_of_range("DB: getStock() array is empty");
    }
    return p.back();
}

void MyDatabase::initPrices(std::string &share) {
    storage.transaction([&] () mutable {
        auto now = std::time(nullptr);
        for (int i=3600 * 24 * 7; i > 0; i -= 3600) {
            double ask = 10; //98 + 0.5 * (rand() % 10);
            double bid = 10; //ask + 1 + 0.2 * (rand() % 10);
            for (int j=0; j<3600; j+= 600) {
                auto time = now - i + j;
                Price p {0, share, time, ask, bid};
                storage.insert(p);
            }
        }
        return true;
    });
}
