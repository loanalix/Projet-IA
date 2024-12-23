#pragma once
#ifndef TIME_H
#define TIME_H

#include <unordered_map>


class Time {

private:

    struct Timer {
        std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
        std::chrono::duration<double, std::milli> duration;
        std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime;
    };
    std::unordered_map<std::string, Timer> timers;

    static Time* instance;
    Time(int fpsLimit);

    int fpsLimit;
    int fps;
    int fpsProcess;
    int frameCount;
    int frameCountProcess;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> fpsLastCheckTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> fpsLastCheckTimeProcess;
    std::chrono::duration<double, std::milli> targetFrameDuration;


public:
    static Time* GetInstance(int fpsLimit = 60);

    Time(const Time&) = delete;
    Time& operator=(const Time&) = delete;

    double GetElapsedTime();

    double GetElapsedTimeForTimer(const std::string& timerID);

    int GetFPS();
    int GetFPSProcess();
    bool ShouldRender();

    void SetFPS(int fps);

    int GetFPSTarget();

    void StartTimer(const std::string& timerID, double durationMilliseconds);

    bool IsTimerReached(const std::string& timerID);

    bool TimerExists(const std::string& timerID);

    void RemoveTimer(const std::string& timerID);

	double GetActualTime();

	//int GetActualTimeInt();
};


#endif // TIME_H
