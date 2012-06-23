#include "DateTime.hpp"
#include <Windows.h>

void Sleep(TimeSpan inTimeSpan)
{
    Sleep(inTimeSpan.Milliseconds());
}

DateTime GetNativeTime()
{
    FILETIME fileTime;
    GetSystemTimeAsFileTime(&fileTime);
    uint64_t result = fileTime.dwHighDateTime;
    result <<= 32;
    result |= fileTime.dwLowDateTime;

    DateTime base;
    base.Set(1601, 1, 1);

    return base + int64_t(result);
}

static TimeSpan timerBase;

TimeSpan RawTimer()
{
    return GetTickCount() * TicksPerMillisecond;
}

void ResetTimer()
{
    timerBase = RawTimer();
}

TimeSpan ReadTimer()
{
    return RawTimer() - timerBase;
}
