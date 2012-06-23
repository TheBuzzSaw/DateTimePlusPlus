#include "DateTime.hpp"
#include <ctime>

void Sleep(TimeSpan inTimeSpan)
{
    usleep(inTimeSpan.Microseconds());
}

DateTime GetNativeTime()
{
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    int64_t ticks = ts.tv_nsec / NanosecondsPerTick;
    ticks += ts.tv_sec * TicksPerSecond;

    DateTime epoch;
    epoch.Set(1970, 1, 1);

    return epoch + TimeSpan(ticks);
}

static TimeSpan timerBase;

TimeSpan RawTimer()
{
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);

    int64_t ticks = ts.tv_nsec / NanosecondsPerTick;
    ticks += ts.tv_sec * TicksPerSecond;

    return ticks;
}

void ResetTimer()
{
    timerBase = RawTimer();
}

TimeSpan ReadTimer()
{
    return RawTimer() - timerBase;
}
