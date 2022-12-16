//
// Created by kkeiper1103 on 11/25/22.
//

#include "Timer.h"

Timer::Timer(double timeStep) : dt(timeStep) {
    currentTime = glfwGetTime();
}

void Timer::tick(const std::function<void(double)> &update) {
    double newTime = glfwGetTime();
    double frameTime = newTime - currentTime;
    if ( frameTime > 0.25 )
        frameTime = 0.25;
    currentTime = newTime;

    accumulator += frameTime;

    while ( accumulator >= dt )
    {
        update(dt);

        accumulator -= dt;
        t += dt;
    }

}
