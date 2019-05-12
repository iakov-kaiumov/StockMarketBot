#ifndef TELEGRAMBOT_KEYBOARDFACTORY_H
#define TELEGRAMBOT_KEYBOARDFACTORY_H

#include <tgbot/tgbot.h>
#include "../resource-manager/StringResource.h"

class KeyboardFactory {
public:
    static TgBot::ReplyKeyboardMarkup::Ptr mainKeyboard(StringResource& res, const std::string& locale);
    static TgBot::ReplyKeyboardMarkup::Ptr shareKeyboard(StringResource& res, const std::string& locale);
    static TgBot::ReplyKeyboardMarkup::Ptr timeKeyboard(StringResource& res, const std::string& locale);
    static TgBot::ReplyKeyboardMarkup::Ptr cancelKeyboard(StringResource& res, const std::string& locale);

    static TgBot::ReplyKeyboardMarkup::Ptr settingsKeyboard(StringResource& res, const std::string& locale);
    static TgBot::ReplyKeyboardMarkup::Ptr graphViewKeyboard(StringResource& res, const std::string& locale);
    static TgBot::ReplyKeyboardMarkup::Ptr langKeyboard(StringResource& res, const std::string& locale);
};


#endif //TELEGRAMBOT_KEYBOARDFACTORY_H
