#include "DateTime.hpp"
#include <Windows.h>
#include <iostream>
using namespace std;

void Sleep(TimeSpan inTimeSpan)
{
    Sleep(inTimeSpan.Milliseconds());
}

const DateTime GetNativeTime()
{
    FILETIME fileTime;
    GetSystemTimeAsFileTime(&fileTime);
    int64_t result = fileTime.dwHighDateTime;
    result <<= 32;
    result |= fileTime.dwLowDateTime;

    DateTime base;
    base.Set(1601, 1, 1);

    return base + TimeSpan(result);
}

static TimeSpan timerBase;
static int64_t frequency = 0;

const TimeSpan RawTimer()
{
    TimeSpan outTimeSpan;

    if (frequency > 0)
    {
        LARGE_INTEGER count;
        QueryPerformanceCounter(&count);
        int64_t microseconds = (count.QuadPart * 1000000) / frequency;
        outTimeSpan = TimeSpan::FromMicroseconds(microseconds);
    }
    else
    {
        outTimeSpan = TimeSpan::FromMilliseconds(GetTickCount());
    }

    return outTimeSpan;
}

void ResetTimer()
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    frequency = freq.QuadPart;
    cout << "frequency: " << frequency << endl;

    timerBase = RawTimer();
}

const TimeSpan ReadTimer()
{
    return RawTimer() - timerBase;
}
