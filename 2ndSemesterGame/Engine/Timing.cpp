#include "Timing.h"

double Timing::FreqEveryMillSecond = Timing::freqInitialization();
double Timing::g_LastFrameTime_ms = 0;
LARGE_INTEGER Timing::g_LastFrameStartTick = { 0 };
