#ifndef TELEGRAMBOT_DATABASE_H
#define TELEGRAMBOT_DATABASE_H


#include <vector>
#include "../sqlite_orm-master/include/sqlite_orm/sqlite_orm.h"
#include "User.h"
#include "../stock/Price.h"

using namespace sqlite_orm;

class MyDatabase {
public:
    void init();
    User *getUserById(int64_t id);
    std::vector<Order> getUserOrders(int64_t id, bool isOpen = true);
    void addNewUser(User user);
    void addNewOrder(Order order);
    void updateOrder(Order order);
    void addNewPrice(Price price);
    std::vector<Price> getPricesSince(std::string share, time_t since);
private:
    static inline auto storage = make_storage("db.sqlite",
                                make_table("users",
                                           make_column("dId", &User::dId, primary_key()),
                                           make_column("id", &User::id),
                                           make_column("firstName", &User::firstName),
                                           make_column("lastName", &User::lastName),
                                           make_column("money", &User::money)),
                                make_table("orders",
                                           make_column("dId", &Order::dId, primary_key()),
                                           make_column("id", &Order::id),
                                           make_column("name", &Order::share),
                                           make_column("amount", &Order::amount),
                                           make_column("openPrice", &Order::openPrice),
                                           make_column("closePrice", &Order::closePrice),
                                           make_column("isOpen", &Order::isOpen)),
                                make_table("prices",
                                         make_column("dId", &Price::dId, primary_key()),
                                         make_column("name", &Price::share),
                                         make_column("ask", &Price::ask),
                                         make_column("bid", &Price::bid),
                                         make_column("time", &Price::time)));
};


#endif //TELEGRAMBOT_DATABASE_H
