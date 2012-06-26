#include "DateTime.hpp"
#include <Windows.h>
#include <iostream>
using namespace std;

void Sleep(TimeSpan timeSpan)
{
    Sleep(timeSpan.ToMilliseconds());
}

const DateTime GetNativeTime()
{
    FILETIME fileTime;
    GetSystemTimeAsFileTime(&fileTime);
    int64_t result = fileTime.dwHighDateTime;
    result <<= 32;
    result |= fileTime.dwLowDateTime;

    return DateTime(1601, 1, 1) + TimeSpan(result);
}

static TimeSpan timerBase;
static int64_t frequency = 0;

const TimeSpan RawTimer()
{
    TimeSpan timeSpan;

    if (frequency > 0)
    {
        LARGE_INTEGER count;
        QueryPerformanceCounter(&count);
        int64_t microseconds = (count.QuadPart * 1000000) / frequency;
        timeSpan = TimeSpan::FromMicroseconds(microseconds);
    }
    else
    {
        timeSpan = TimeSpan::FromMilliseconds(GetTickCount());
    }

    return timeSpan;
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
