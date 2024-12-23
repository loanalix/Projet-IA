#include "pch.h"

Time* Time::instance = nullptr;

Time* Time::GetInstance(int fpsLimit) {
    if (instance == nullptr) {
        instance = new Time(fpsLimit);
    }
    return instance;
}

Time::Time(int fpsLimit) : fpsLimit(fpsLimit), fps(0), fpsProcess(0), frameCount(0), frameCountProcess(0){
    lastFrameTime = std::chrono::high_resolution_clock::now();
    fpsLastCheckTime = lastFrameTime;
    fpsLastCheckTimeProcess = lastFrameTime;
    targetFrameDuration = std::chrono::duration<double, std::milli>(1000.0 / fpsLimit);
}

double Time::GetElapsedTime() {
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = now - lastFrameTime;
    lastFrameTime = now;
    return elapsed.count();  
}

double Time::GetElapsedTimeForTimer(const std::string& timerID) {
    if (timers.find(timerID) != timers.end()) {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(now - timers[timerID].lastFrameTime);
        timers[timerID].lastFrameTime = now;
        return elapsed.count();
    }

    return 0.0;
}

int Time::GetFPS() {
    frameCount++;
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = now - fpsLastCheckTime;

    if (elapsed.count() >= 1.0) {
        fps = frameCount;
        frameCount = 0;
        fpsLastCheckTime = now;
    }

    return fps;
}

int Time::GetFPSProcess()
{
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = now - fpsLastCheckTimeProcess;

    if (elapsed.count() >= 1.0) {
        fpsProcess = frameCountProcess;
        frameCountProcess = 0;
        fpsLastCheckTimeProcess = now;
    }

    return fpsProcess;
}

bool Time::ShouldRender() {
    frameCountProcess++;
    auto now = std::chrono::high_resolution_clock::now();
    auto frameDuration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(now - lastFrameTime);

    if (frameDuration >= targetFrameDuration) {
        lastFrameTime = now;  
        return true;
    }
    return false;
}

void Time::SetFPS(int fps) {
    fpsLimit = fps;
    targetFrameDuration = std::chrono::duration<double, std::milli>(1000.0 / fpsLimit);
}

int Time::GetFPSTarget() {
    return fpsLimit;
}

void Time::StartTimer(const std::string& timerID, double durationMilliseconds) {
    Timer timer;
    timer.startTime = std::chrono::high_resolution_clock::now();
    timer.duration = std::chrono::duration<double, std::milli>(durationMilliseconds);

    timers[timerID] = timer;
}

bool Time::IsTimerReached(const std::string& timerID) {
    if (timers.find(timerID) != timers.end()) {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(now - timers[timerID].startTime);

        if (elapsed >= timers[timerID].duration) {
            timers[timerID].startTime = now;
            return true;
        }
    }

    return false;
}

bool Time::TimerExists(const std::string& timerID) {
    return timers.find(timerID) != timers.end();
}

void Time::RemoveTimer(const std::string& timerID) {
    timers.erase(timerID);
}

double Time::GetActualTime()
{
    //return the actual time not a duration
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(now.time_since_epoch()).count();
}

//int Time::GetActualTimeInt()
//{
//	auto now = std::chrono::high_resolution_clock::now();
//	std::chrono::duration<double> elapsed = now - lastFrameTime;
//	return elapsed.count();
//}
