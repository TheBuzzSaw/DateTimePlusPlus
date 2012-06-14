#include "TimeSpan.hpp"

TimeSpan::TimeSpan(int64_t inTicks) : mTicks(inTicks)
{
}

TimeSpan::TimeSpan(const TimeSpan& inTimeSpan)
{
    mTicks = inTimeSpan.mTicks;
}

TimeSpan::~TimeSpan()
{
}

TimeSpan& TimeSpan::operator=(const TimeSpan& inTimeSpan)
{
    mTicks = inTimeSpan.mTicks;
    return *this;
}

bool TimeSpan::operator==(const TimeSpan& inTimeSpan)
{
    return mTicks == inTimeSpan.mTicks;
}

bool TimeSpan::operator!=(const TimeSpan& inTimeSpan)
{
    return mTicks != inTimeSpan.mTicks;
}

bool TimeSpan::operator<(const TimeSpan& inTimeSpan)
{
    return mTicks < inTimeSpan.mTicks;
}

bool TimeSpan::operator<=(const TimeSpan& inTimeSpan)
{
    return mTicks <= inTimeSpan.mTicks;
}

bool TimeSpan::operator>(const TimeSpan& inTimeSpan)
{
    return mTicks > inTimeSpan.mTicks;
}

bool TimeSpan::operator>=(const TimeSpan& inTimeSpan)
{
    return mTicks >= inTimeSpan.mTicks;
}

int64_t TimeSpan::Milliseconds() const
{
    return mTicks / TicksPerMillisecond;
}

int64_t TimeSpan::Seconds() const
{
    return mTicks / TicksPerSecond;
}

int64_t TimeSpan::Minutes() const
{
    return mTicks / TicksPerMinute;
}

int64_t TimeSpan::Hours() const
{
    return mTicks / TicksPerHour;
}

int64_t TimeSpan::Days() const
{
    return mTicks / TicksPerDay;
}

int64_t TimeSpan::Weeks() const
{
    return mTicks / TicksPerWeek;
}
