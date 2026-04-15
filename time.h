#pragma once
#include <SDL3/SDL_stdinc.h>

class Time
{
    Uint64 last_time_ = 0;
    Uint64 frame_time_ = 0;
    float delta_time_ = 0.0;
    float time_scale_ = 1.0;
    Uint64 target_interval_ = 0;
    int target_fps_ = 0;

public:
    Time();
    Time(Time&) = delete;
    Time(Time&&) = delete;
    Time& operator=(Time&) = delete;
    Time& operator=(Time&&) = delete;

    void update();
    void sync();

    float getDeltaTime() const;
    float getDeltaTimeUnscaled() const;

    void setTimeScale(float scale);
    float getTimeScale() const;

    void setTargetFps(int fps);
    int getTargetFps() const;
};