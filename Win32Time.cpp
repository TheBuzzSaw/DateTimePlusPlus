#include "DateTime.hpp"
#include <Windows.h>

void Sleep(TimeSpan inTimeSpan)
{
    Sleep(inTimeSpan.Milliseconds());
}

const DateTime GetNativeTime()
{
    FILETIME fileTime;
    GetSystemTimeAsFileTime(&fileTime);
    uint64_t result = fileTime.dwHighDateTime;
    result <<= 32;
    result |= fileTime.dwLowDateTime;

    DateTime base;
    base.Set(1601, 1, 1);

    return base + TimeSpan(int64_t(result));
}

static TimeSpan timerBase;

const TimeSpan RawTimer()
{
    return TimeSpan(GetTickCount() * TicksPerMillisecond);
}

void ResetTimer()
{
    timerBase = RawTimer();
}

const TimeSpan ReadTimer()
{
    return RawTimer() - timerBase;
}
