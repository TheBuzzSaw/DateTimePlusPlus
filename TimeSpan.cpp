#include "TimeSpan.hpp"

TimeSpan::TimeSpan(int hour, int minute, int second)
{
    if (0 <= hour && hour <= 23
        && 0 <= minute && minute <= 59
        && 0 <= second && second <= 59)
    {
        _ticks
            = hour * TicksPerHour
            + minute * TicksPerMinute
            + second * TicksPerSecond;
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
