#ifndef TIMER_H
#define TIMER_H
#include "NonCopyable.h"
#include "NonMovable.h"
#include <chrono>

class Timer : public NonCopyable, public NonMovable
{
public:
    Timer();
    ~Timer() = default;

    float getDelta();
    float getFPS(const float deltaTime) const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_timePrev;
};

#endif