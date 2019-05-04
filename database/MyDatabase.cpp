#include <iostream>
#include "MyDatabase.h"

void MyDatabase::init() {
    storage.sync_schema();
}

User *MyDatabase::getUserById(int64_t id) {
    std::cout << id << std::endl;
    for (auto &u : storage.get_all<User>(where(c(&User::id) == id))) {
        return &u;
    }
    return nullptr;
}

void MyDatabase::addNewUser(User user) {
    if (storage.get_all<User>(where(c(&User::id) == user.id)).empty())
        storage.insert(user);
    else
        storage.update(user);
}

void MyDatabase::addNewOrder(Order order) {
    storage.insert(order);
}

std::vector<Order> MyDatabase::getUserOrders(int64_t id, bool isOpen) {
    return storage.get_all<Order>(where(c(&Order::id) == id && c(&Order::isOpen) == isOpen));
}

void MyDatabase::updateOrder(Order order) {
    storage.update(order);
}

void MyDatabase::addNewPrice(Price price) {
    storage.insert(price);
}

std::vector<Price> MyDatabase::getPricesSince(std::string share, time_t since) {
    return storage.get_all<Price>(where(c(&Price::share) == share && c(&Price::time) > since));
}
