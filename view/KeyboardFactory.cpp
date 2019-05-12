#include "KeyboardFactory.h"


TgBot::ReplyKeyboardMarkup::Ptr KeyboardFactory::mainKeyboard(StringResource& res, const std::string& locale) {
    TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup);
    std::vector<TgBot::KeyboardButton::Ptr> row0;
    std::vector<TgBot::KeyboardButton::Ptr> row1;

    TgBot::KeyboardButton::Ptr button0(new TgBot::KeyboardButton);
    button0->text = res.get("PRICE_BUTTON", locale);
    row0.push_back(button0);

    TgBot::KeyboardButton::Ptr button1(new TgBot::KeyboardButton);
    button1->text = res.get("GRAPH_BUTTON", locale);
    row0.push_back(button1);

    TgBot::KeyboardButton::Ptr button2(new TgBot::KeyboardButton);
    button2->text = res.get("ORDERS_BUTTON", locale);
    row0.push_back(button2);

    TgBot::KeyboardButton::Ptr button3(new TgBot::KeyboardButton);
    button3->text = res.get("NEW_BUTTON", locale);
    row1.push_back(button3);

    TgBot::KeyboardButton::Ptr button4(new TgBot::KeyboardButton);
    button4->text = res.get("CLOSE_BUTTON", locale);
    row1.push_back(button4);

    TgBot::KeyboardButton::Ptr button5(new TgBot::KeyboardButton);
    button5->text = res.get("SETTINGS_OPEN", locale);
    row1.push_back(button5);

    keyboard->keyboard.push_back(row0);
    keyboard->keyboard.push_back(row1);
    return keyboard;
}

TgBot::ReplyKeyboardMarkup::Ptr KeyboardFactory::shareKeyboard(StringResource& res, const std::string& locale) {
    TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup);
    std::vector<TgBot::KeyboardButton::Ptr> row0;
    std::vector<TgBot::KeyboardButton::Ptr> row1;
    TgBot::KeyboardButton::Ptr button0(new TgBot::KeyboardButton);
    button0->text = res.get("K_BUTTON", locale);
    row0.push_back(button0);

    TgBot::KeyboardButton::Ptr button1(new TgBot::KeyboardButton);
    button1->text = res.get("P_BUTTON", locale);
    row0.push_back(button1);

    TgBot::KeyboardButton::Ptr button2(new TgBot::KeyboardButton);
    button2->text = res.get("CANCEL_BUTTON", locale);
    row1.push_back(button2);

    keyboard->keyboard.push_back(row0);
    keyboard->keyboard.push_back(row1);
    return keyboard;
}

TgBot::ReplyKeyboardMarkup::Ptr KeyboardFactory::timeKeyboard(StringResource& res, const std::string& locale) {
    TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup);
    std::vector<TgBot::KeyboardButton::Ptr> row0;
    std::vector<TgBot::KeyboardButton::Ptr> row1;
    std::vector<TgBot::KeyboardButton::Ptr> row2;
    TgBot::KeyboardButton::Ptr button0(new TgBot::KeyboardButton);
    button0->text = res.get("TIME1_BUTTON", locale);
    row0.push_back(button0);

    TgBot::KeyboardButton::Ptr button1(new TgBot::KeyboardButton);
    button1->text = res.get("TIME2_BUTTON", locale);
    row0.push_back(button1);

    TgBot::KeyboardButton::Ptr button2(new TgBot::KeyboardButton);
    button2->text = res.get("TIME3_BUTTON", locale);
    row1.push_back(button2);

    TgBot::KeyboardButton::Ptr button3(new TgBot::KeyboardButton);
    button3->text = res.get("TIME4_BUTTON", locale);
    row1.push_back(button3);

    TgBot::KeyboardButton::Ptr button4(new TgBot::KeyboardButton);
    button4->text = res.get("CANCEL_BUTTON", locale);
    row2.push_back(button4);

    keyboard->keyboard.push_back(row0);
    keyboard->keyboard.push_back(row1);
    keyboard->keyboard.push_back(row2);
    return keyboard;
}

TgBot::ReplyKeyboardMarkup::Ptr KeyboardFactory::cancelKeyboard(StringResource& res, const std::string& locale) {
    TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup);
    std::vector<TgBot::KeyboardButton::Ptr> row0;
    TgBot::KeyboardButton::Ptr button0(new TgBot::KeyboardButton);
    button0->text = res.get("CANCEL_BUTTON", locale);
    row0.push_back(button0);
    keyboard->keyboard.push_back(row0);
    return keyboard;
}

TgBot::ReplyKeyboardMarkup::Ptr KeyboardFactory::settingsKeyboard(StringResource &res, const std::string &locale) {
    TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup);
    std::vector<TgBot::KeyboardButton::Ptr> row0;
    std::vector<TgBot::KeyboardButton::Ptr> row1;
    TgBot::KeyboardButton::Ptr button0(new TgBot::KeyboardButton);
    button0->text = res.get("SETTINGS_GRAPH", locale);
    row0.push_back(button0);

    TgBot::KeyboardButton::Ptr button1(new TgBot::KeyboardButton);
    button1->text = res.get("SETTINGS_LANG", locale);
    row0.push_back(button1);

    TgBot::KeyboardButton::Ptr button2(new TgBot::KeyboardButton);
    button2->text = res.get("CANCEL_BUTTON", locale);
    row1.push_back(button2);

    keyboard->keyboard.push_back(row0);
    keyboard->keyboard.push_back(row1);
    return keyboard;
}

TgBot::ReplyKeyboardMarkup::Ptr KeyboardFactory::graphViewKeyboard(StringResource &res, const std::string &locale) {
    TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup);
    std::vector<TgBot::KeyboardButton::Ptr> row0;
    std::vector<TgBot::KeyboardButton::Ptr> row1;
    TgBot::KeyboardButton::Ptr button0(new TgBot::KeyboardButton);
    button0->text = res.get("SETTINGS_LINES", locale);
    row0.push_back(button0);

    TgBot::KeyboardButton::Ptr button1(new TgBot::KeyboardButton);
    button1->text = res.get("SETTINGS_CANDLES", locale);
    row0.push_back(button1);

    TgBot::KeyboardButton::Ptr button2(new TgBot::KeyboardButton);
    button2->text = res.get("CANCEL_BUTTON", locale);
    row1.push_back(button2);

    keyboard->keyboard.push_back(row0);
    keyboard->keyboard.push_back(row1);
    return keyboard;
}

TgBot::ReplyKeyboardMarkup::Ptr KeyboardFactory::langKeyboard(StringResource &res, const std::string &locale) {
    TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup);
    std::vector<TgBot::KeyboardButton::Ptr> row0;
    std::vector<TgBot::KeyboardButton::Ptr> row1;
    TgBot::KeyboardButton::Ptr button0(new TgBot::KeyboardButton);
    button0->text = res.get("SETTINGS_EN", locale);
    row0.push_back(button0);

    TgBot::KeyboardButton::Ptr button1(new TgBot::KeyboardButton);
    button1->text = res.get("SETTINGS_RU", locale);
    row0.push_back(button1);

    TgBot::KeyboardButton::Ptr button2(new TgBot::KeyboardButton);
    button2->text = res.get("CANCEL_BUTTON", locale);
    row1.push_back(button2);

    keyboard->keyboard.push_back(row0);
    keyboard->keyboard.push_back(row1);
    return keyboard;
}
