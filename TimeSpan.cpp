#include "TimeSpan.hpp"

TimeSpan::TimeSpan(int hour, int minute, int second)
{
    if (InRange(hour, 0, 23) &&
        InRange(minute, 0, 59) &&
        InRange(second, 0, 59))
    {
        _ticks = hour * TicksPerHour +
            minute * TicksPerMinute +
            second * TicksPerSecond;
    }
    else
    {
        _ticks = 0;
    }
}

TimeSpan& TimeSpan::operator+=(const TimeSpan& other)
{
    _ticks += other._ticks;
    return *this;
}

TimeSpan& TimeSpan::operator-=(const TimeSpan& other)
{
    _ticks -= other._ticks;
    return *this;
}
