#include "Timing.h"
#ifdef __MINGW32__

double Timing::FreqEveryMillSecond = Timing::freqInitialization();
double Timing::g_LastFrameTime_ms = 0;
LARGE_INTEGER Timing::g_LastFrameStartTick = { 0 };
#endif
#ifdef __APPLE__
double Timing::g_LastFrameTime_ms = 0;
double Timing::g_LastFrameStartTick = 0;
#endif
