#include "Timer.h"

Timer::Timer()
{
    prevTick = 0;
    currentTicks = 0;
}

Timer::~Timer()
{

}

void Timer::Start()
{
    prevTick = currentTicks = SDL_GetTicks();// grabs milli secs from when SDL starts
}

void Timer::UpdateFrameTicks()
{
    prevTick = currentTicks;
    currentTicks = SDL_GetTicks();

}

float Timer::GetDeltaTime() const
{
    return (currentTicks - prevTick) / MILLI_TO_SEC; // get time in seconds
}

unsigned int Timer::GetSleepTime(const unsigned int fps_) const
{
    unsigned int milliSecsPerFrame = MILLI_TO_SEC / fps_;
    if (milliSecsPerFrame == 0) {
        return 0;
    }
    unsigned int sleepTime = milliSecsPerFrame - (SDL_GetTicks() - currentTicks);
    if (sleepTime > milliSecsPerFrame) {
        return milliSecsPerFrame;
    }

    return sleepTime;
    
}

float Timer::GetCurrentTickMilli() const
{
    return static_cast<float>(currentTicks);
}

float Timer::GetCurrentTickSec() const
{
    return currentTicks / MILLI_TO_SEC;
}
