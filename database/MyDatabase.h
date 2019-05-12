#ifndef TELEGRAMBOT_DATABASE_H
#define TELEGRAMBOT_DATABASE_H


#include <vector>
#include "../sqlite_orm-master/include/sqlite_orm/sqlite_orm.h"
#include "User.h"
#include "../stock/Price.h"
#include "../stock/Stock.h"

using namespace sqlite_orm;

class MyDatabase {
public:
    void initPrices(std::string &share);

    void init();

    User getUserById(int64_t id);
    long getUserCount();
    void insertUser(User user);

    void insertOrder(Order &order);
    void updateOrder(Order& order);
    std::vector<Order> getUserOrders(int64_t id, bool isOpen = true);

    void insertPrice(Price& price);
    std::vector<Price> getPricesSince(std::string& share, time_t since);
    Price getLastPrice(std::string& share);

    void insertStock(Stock &stock);
    Stock getStock(std::string &share);
private:
    static inline auto storage = make_storage("db.sqlite",
                                make_table("user",
                                           make_column("dId", &User::dId, primary_key()),
                                           make_column("id", &User::id),
                                           make_column("firstName", &User::firstName),
                                           make_column("lastName", &User::lastName),
                                           make_column("money", &User::money),
                                           make_column("locale", &User::locale),
                                           make_column("graphView", &User::graphView)),
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
                                make_table("stock",
                                         make_column("dId", &Stock::dId, primary_key()),
                                         make_column("share", &Stock::share),
                                         make_column("NASP", &Stock::NASP),
                                         make_column("NSP", &Stock::NSP),
                                         make_column("P", &Stock::P),
                                         make_column("TOTAL_SHARES", &Stock::TOTAL_SHARES),
                                         make_column("BOUGHT_SHARES", &Stock::BOUGHT_SHARES),
                                         make_column("lastTransaction", &Stock::lastTransaction)));
};


#endif //TELEGRAMBOT_DATABASE_H
