#ifndef TELEGRAMBOT_PHRASES_H
#define TELEGRAMBOT_PHRASES_H

#include <string>

namespace PHRASES {
    const std::string HELLO_TEXT = "Greetings, my friend! You've just joined private K&P stock market.\n"
                                                 "Here you can find two big companies K and P. It is a rapidly growing market,"
                                                 "so don't lose a chance and make a fortune using our 100$!";

    inline static const std::string PRICE_BUTTON = "Current price";

    inline static const std::string GRAPH_BUTTON = "Graph";

    inline static const std::string ORDERS_BUTTON = "My orders";

    inline static const std::string NEW_BUTTON = "New order";

    inline static const std::string K_BUTTON = "K";

    inline static const std::string P_BUTTON = "P";

    inline static const std::string CLOSE_BUTTON = "Close order";

    inline static const std::string INFO_BUTTON = "Info";

    inline static const std::string CANCEL_BUTTON = "Cancel";

    inline static const std::string TIME1_BUTTON = "1 hour";

    inline static const std::string TIME2_BUTTON = "24 hours";

    inline static const std::string TIME3_BUTTON = "1 week";

    inline static const std::string TIME4_BUTTON = "1 month";
};

#endif //TELEGRAMBOT_PHRASES_H
