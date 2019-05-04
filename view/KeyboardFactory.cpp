#include "KeyboardFactory.h"
#include "../Phrases.h"

TgBot::ReplyKeyboardMarkup::Ptr KeyboardFactory::mainKeyboard() {
    TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup);
    std::vector<TgBot::KeyboardButton::Ptr> row0;
    std::vector<TgBot::KeyboardButton::Ptr> row1;

    TgBot::KeyboardButton::Ptr button0(new TgBot::KeyboardButton);
    button0->text = PHRASES::PRICE_BUTTON;
    row0.push_back(button0);

    TgBot::KeyboardButton::Ptr button1(new TgBot::KeyboardButton);
    button1->text = PHRASES::GRAPH_BUTTON;
    row0.push_back(button1);

    TgBot::KeyboardButton::Ptr button2(new TgBot::KeyboardButton);
    button2->text = PHRASES::ORDERS_BUTTON;
    row0.push_back(button2);

    TgBot::KeyboardButton::Ptr button3(new TgBot::KeyboardButton);
    button3->text = PHRASES::NEW_BUTTON;
    row1.push_back(button3);

    TgBot::KeyboardButton::Ptr button4(new TgBot::KeyboardButton);
    button4->text = PHRASES::CLOSE_BUTTON;
    row1.push_back(button4);

    TgBot::KeyboardButton::Ptr button5(new TgBot::KeyboardButton);
    button5->text = PHRASES::INFO_BUTTON;
    row1.push_back(button5);

    keyboard->keyboard.push_back(row0);
    keyboard->keyboard.push_back(row1);
    return keyboard;
}

TgBot::ReplyKeyboardMarkup::Ptr KeyboardFactory::shareKeyboard() {
    TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup);
    std::vector<TgBot::KeyboardButton::Ptr> row0;
    std::vector<TgBot::KeyboardButton::Ptr> row1;
    TgBot::KeyboardButton::Ptr button0(new TgBot::KeyboardButton);
    button0->text = PHRASES::K_BUTTON;
    row0.push_back(button0);

    TgBot::KeyboardButton::Ptr button1(new TgBot::KeyboardButton);
    button1->text = PHRASES::P_BUTTON;
    row0.push_back(button1);

    TgBot::KeyboardButton::Ptr button2(new TgBot::KeyboardButton);
    button2->text = PHRASES::CANCEL_BUTTON;
    row1.push_back(button2);

    keyboard->keyboard.push_back(row0);
    keyboard->keyboard.push_back(row1);
    return keyboard;
}

TgBot::ReplyKeyboardMarkup::Ptr KeyboardFactory::timeKeyboard() {
    TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup);
    std::vector<TgBot::KeyboardButton::Ptr> row0;
    std::vector<TgBot::KeyboardButton::Ptr> row1;
    std::vector<TgBot::KeyboardButton::Ptr> row2;
    TgBot::KeyboardButton::Ptr button0(new TgBot::KeyboardButton);
    button0->text = PHRASES::TIME1_BUTTON;
    row0.push_back(button0);

    TgBot::KeyboardButton::Ptr button1(new TgBot::KeyboardButton);
    button1->text = PHRASES::TIME2_BUTTON;
    row0.push_back(button1);

    TgBot::KeyboardButton::Ptr button2(new TgBot::KeyboardButton);
    button2->text = PHRASES::TIME3_BUTTON;
    row1.push_back(button2);

    TgBot::KeyboardButton::Ptr button3(new TgBot::KeyboardButton);
    button3->text = PHRASES::TIME4_BUTTON;
    row1.push_back(button3);

    TgBot::KeyboardButton::Ptr button4(new TgBot::KeyboardButton);
    button4->text = PHRASES::CANCEL_BUTTON;
    row2.push_back(button4);

    keyboard->keyboard.push_back(row0);
    keyboard->keyboard.push_back(row1);
    keyboard->keyboard.push_back(row2);
    return keyboard;
}

TgBot::ReplyKeyboardMarkup::Ptr KeyboardFactory::cancelKeyboard() {
    TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup);
    std::vector<TgBot::KeyboardButton::Ptr> row0;
    TgBot::KeyboardButton::Ptr button0(new TgBot::KeyboardButton);
    button0->text = PHRASES::CANCEL_BUTTON;
    row0.push_back(button0);
    keyboard->keyboard.push_back(row0);
    return keyboard;
}
