//
// Created by kkeiper1103 on 11/25/22.
//

#ifndef MODULE5_MILESTONE_TIMER_H
#define MODULE5_MILESTONE_TIMER_H

#include <GLFW/glfw3.h>
#include <functional>

class Timer {
protected:
    double t = 0.0, dt = 0.01;
    double currentTime = 0.0, accumulator = 0.0;

public:
    explicit Timer(double timeStep = 0.01);

    void tick(const std::function<void(double)>& update);
};


#endif //MODULE5_MILESTONE_TIMER_H
