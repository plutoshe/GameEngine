#pragma once
#include <windows.h>

#include "Log.h"


class Timing
{
public:
	static LARGE_INTEGER GetCurrentCPUCounter() {
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return li;
	}
	static double GetCPUCounterFrequency_ms() {
		return FreqEveryMillSecond;
	}

	static double CalcLastFrameTime_ms() {
		// Grab the CPU tick counter
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

		return g_LastFrameTime_ms;
	}
private:
	static double freqInitialization() {
		LARGE_INTEGER li;
		if (!QueryPerformanceFrequency(&li))
			ERROR_LOG("QueryPerformanceFrequency failed!\n");
		return double(li.QuadPart) / 1000.0;
	}
	static LARGE_INTEGER g_LastFrameStartTick;
	static double FreqEveryMillSecond;
	static double g_LastFrameTime_ms;

};
