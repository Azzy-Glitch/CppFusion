
#include "Food.h"
#include <iostream>
#include <ctime>
#include <chrono>

void Food::gen_food()
{
    auto currentTime = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastGenTime);

    if (duration.count() >= foodIntervalSeconds)
    {
        pos.X = (rand() % (WIDTH - 3)) + 1;
        pos.Y = (rand() % (HEIGHT - 3)) + 1;
        lastGenTime = std::chrono::system_clock::now();
    }
}

COORD Food::get_pos() { return pos; }
