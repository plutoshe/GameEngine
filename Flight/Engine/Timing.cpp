#include "Timing.h"

double Timing::g_LastFrameTime_ms = 0;
#ifdef __MINGW32__
LARGE_INTEGER Timing::g_LastFrameStartTick = { 0 };
#endif
#ifdef __APPLE__
double Timing::g_LastFrameStartTick = 0;
#endif
