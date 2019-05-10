#ifndef TELEGRAMBOT_DATABASE_H
#define TELEGRAMBOT_DATABASE_H


#include <vector>
#include "../sqlite_orm-master/include/sqlite_orm/sqlite_orm.h"
#include "User.h"
#include "../stock/Price.h"
#include "../stock/SP.h"

using namespace sqlite_orm;

class MyDatabase {
public:
    void initPrices(std::string &share);

    void init();
    User *getUserById(int64_t id);
    void insertUser(User &user);

    void addNewOrder(Order& order);
    void updateOrder(Order& order);
    std::vector<Order> getUserOrders(int64_t id, bool isOpen = true);

    void insertPrice(Price& price);
    std::vector<Price> getPricesSince(std::string& share, time_t since);
    std::string dumpPricesSince(std::string& share, time_t since);
    Price getLastPrice(std::string& share);

    void insertSP(SP &sp);
    SP getSP(std::string &share);
private:
    static inline auto storage = make_storage("db.sqlite",
                                make_table("user",
                                           make_column("dId", &User::dId, primary_key()),
                                           make_column("id", &User::id),
                                           make_column("firstName", &User::firstName),
                                           make_column("lastName", &User::lastName),
                                           make_column("money", &User::money)),
                                make_table("order",
                                           make_column("dId", &Order::dId, primary_key()),
                                           make_column("id", &Order::id),
                                           make_column("share", &Order::share),
                                           make_column("amount", &Order::amount),
                                           make_column("openPrice", &Order::openPrice),
                                           make_column("closePrice", &Order::closePrice),
                                           make_column("isOpen", &Order::isOpen)),
                                make_table("price",
                                         make_column("dId", &Price::dId, primary_key()),
                                         make_column("share", &Price::share),
                                         make_column("ask", &Price::ask),
                                         make_column("bid", &Price::bid),
                                         make_column("time", &Price::time)),
                                make_table("SP",
                                         make_column("dId", &SP::dId, primary_key()),
                                         make_column("share", &SP::share),
                                         make_column("NASP", &SP::NASP),
                                         make_column("NSP", &SP::NSP)));
};


#endif //TELEGRAMBOT_DATABASE_H
