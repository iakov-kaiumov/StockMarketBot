#ifndef TELEGRAMBOT_TIMER_H
#define TELEGRAMBOT_TIMER_H

#include <chrono>
#include <functional>
#include <thread>

class Timer {
public:
    void add(int delay, std::function<void()> callback) {
        std::thread([=]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            callback();
        }).detach();
    }
};

#endif //TELEGRAMBOT_TIMER_H
