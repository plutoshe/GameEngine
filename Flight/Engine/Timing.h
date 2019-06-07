#pragma once
#ifdef __MINGW32__
    #include <Windows.h>
#endif
#ifdef __APPLE__
#include <CoreServices/CoreServices.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <unistd.h>

#endif
#include "Log.h"


class Timing
{
public:
#ifdef __MINGW32__
    static LARGE_INTEGER GetCurrentCPUCounter() {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        return li;
    }
#endif

    static double CalcLastFrameTime_ms() {
        // Grab the CPU tick counter
#ifdef __MINGW32__
    static double GetCPUCounterFrequency_ms() {
        return FreqEveryMillSecond;
    }
        LARGE_INTEGER currentTick = GetCurrentCPUCounter();
        if (g_LastFrameStartTick.QuadPart > 0) {
            // How many ticks have elapsed since we last did this
            long long elapsedTicks = currentTick.QuadPart - g_LastFrameStartTick.QuadPart;

            // Calculate the frame time - converting ticks to ms.
            g_LastFrameTime_ms = elapsedTicks / GetCPUCounterFrequency_ms();
        }
        else {
            g_LastFrameTime_ms = 13.3; // Assume a 60Hz frame for first call.
        }
        // Note start of this frame
        g_LastFrameStartTick = currentTick;
#endif
#ifdef __APPLE__
        double currentTick = mach_absolute_time();
        g_LastFrameTime_ms = currentTick - g_LastFrameStartTick;
        g_LastFrameStartTick = currentTick;
#endif


        return g_LastFrameTime_ms;
    }
private:
#ifdef __MINGW32__
    static double freqInitialization() {
        LARGE_INTEGER li;
        if (!QueryPerformanceFrequency(&li))
            ERROR_LOG("QueryPerformanceFrequency failed!\n");
        return double(li.QuadPart) / 1000.0;
    }
    static LARGE_INTEGER g_LastFrameStartTick;
#endif
#ifdef __APPLE__
    static double g_LastFrameStartTick;
#endif
    static double g_LastFrameTime_ms;

};
