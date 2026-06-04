#include "time.h"
#include <thread>
#include <SDL3/SDL_timer.h>

Time::Time(int target_fps) { setTargetFps(target_fps); }

float Time::update()
{
    frame_time_ += target_interval_;
    while (true) {
        Uint64 remaining = 0;
        if (frame_time_ > SDL_GetTicksNS())
            remaining = frame_time_ - SDL_GetTicksNS();

        if (remaining <= 2000000) {
            while (SDL_GetTicksNS() < frame_time_)
                std::this_thread::yield();
            break;
        }

        SDL_DelayPrecise(remaining - 1000000);
    }

    Uint64 current_time = SDL_GetTicksNS();
    delta_time_ = float((current_time - last_time_) / 1e9);
    last_time_ = current_time;

    return getDeltaTime();
}

float Time::getDeltaTime() const { return delta_time_; }

void Time::setTargetFps(int fps)
{
    target_fps_ = fps > 0 ? fps : 0;

    if (target_fps_ > 0)
        target_interval_ = Uint64(1e9) / target_fps_;
    else
        target_interval_ = 0;

    last_time_ = SDL_GetTicksNS();
    frame_time_ = last_time_;
}

int Time::getTargetFps() const { return target_fps_; }