#ifndef TELEGRAMBOT_KEYBOARDFACTORY_H
#define TELEGRAMBOT_KEYBOARDFACTORY_H

#include <tgbot/tgbot.h>

class KeyboardFactory {
public:
    static TgBot::ReplyKeyboardMarkup::Ptr mainKeyboard();
    static TgBot::ReplyKeyboardMarkup::Ptr shareKeyboard();
    static TgBot::ReplyKeyboardMarkup::Ptr timeKeyboard();
    static TgBot::ReplyKeyboardMarkup::Ptr cancelKeyboard();
};


#endif //TELEGRAMBOT_KEYBOARDFACTORY_H
