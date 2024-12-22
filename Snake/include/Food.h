#ifndef FOOD_H
#define FOOD_H

#include <windows.h>
#include <cstdio>
#include <chrono>

#define WIDTH 50
#define HEIGHT 25

class Food
{
private:
    COORD pos;
    std::chrono::time_point<std::chrono::system_clock> lastGenTime;
    const int foodIntervalSeconds = 5; // Set the interval for generating food

public:
    void gen_food();

    COORD get_pos();
};

#endif // FOOD_H
