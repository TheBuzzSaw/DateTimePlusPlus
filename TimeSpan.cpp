#include "TimeSpan.hpp"
#include "TickSpans.hpp"

TimeSpan::TimeSpan() : mTicks(0)
{
}

TimeSpan::TimeSpan(int64_t inTicks) : mTicks(inTicks)
{
}

TimeSpan::TimeSpan(const TimeSpan& inTimeSpan) : mTicks(inTimeSpan.mTicks)
{
}

TimeSpan::~TimeSpan()
{
}

TimeSpan& TimeSpan::operator=(const TimeSpan& inTimeSpan)
{
    mTicks = inTimeSpan.mTicks;
    return *this;
}

TimeSpan& TimeSpan::operator+=(const TimeSpan& inTimeSpan)
{
    mTicks += inTimeSpan.mTicks;
    return *this;
}

TimeSpan& TimeSpan::operator-=(const TimeSpan& inTimeSpan)
{
    mTicks -= inTimeSpan.mTicks;
    return *this;
}

bool TimeSpan::operator==(const TimeSpan& inTimeSpan) const
{
    return mTicks == inTimeSpan.mTicks;
}

bool TimeSpan::operator!=(const TimeSpan& inTimeSpan) const
{
    return mTicks != inTimeSpan.mTicks;
}

bool TimeSpan::operator<(const TimeSpan& inTimeSpan) const
{
    return mTicks < inTimeSpan.mTicks;
}

bool TimeSpan::operator<=(const TimeSpan& inTimeSpan) const
{
    return mTicks <= inTimeSpan.mTicks;
}

bool TimeSpan::operator>(const TimeSpan& inTimeSpan) const
{
    return mTicks > inTimeSpan.mTicks;
}

bool TimeSpan::operator>=(const TimeSpan& inTimeSpan) const
{
    return mTicks >= inTimeSpan.mTicks;
}

const TimeSpan TimeSpan::operator+(const TimeSpan& inTimeSpan) const
{
    return TimeSpan(mTicks + inTimeSpan.mTicks);
}

const TimeSpan TimeSpan::operator-(const TimeSpan& inTimeSpan) const
{
    return TimeSpan(mTicks - inTimeSpan.mTicks);
}

const TimeSpan TimeSpan::operator-() const
{
    return TimeSpan(-mTicks);
}

int64_t TimeSpan::Microseconds() const
{
    return mTicks / TicksPerMicrosecond;
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

const TimeSpan TimeSpan::FromNanoseconds(int64_t inNanoseconds)
{
    return TimeSpan(inNanoseconds / NanosecondsPerTick);
}

const TimeSpan TimeSpan::FromMicroseconds(int64_t inMicroseconds)
{
    return TimeSpan(inMicroseconds * TicksPerMicrosecond);
}

const TimeSpan TimeSpan::FromMilliseconds(int64_t inMilliseconds)
{
    return TimeSpan(inMilliseconds * TicksPerMillisecond);
}

const TimeSpan TimeSpan::FromSeconds(int64_t inSeconds)
{
    return TimeSpan(inSeconds * TicksPerSecond);
}

const TimeSpan TimeSpan::FromMinutes(int64_t inMinutes)
{
    return TimeSpan(inMinutes * TicksPerMinute);
}

const TimeSpan TimeSpan::FromHours(int64_t inHours)
{
    return TimeSpan(inHours * TicksPerHour);
}

const TimeSpan TimeSpan::FromDays(int64_t inDays)
{
    return TimeSpan(inDays * TicksPerDay);
}

const TimeSpan TimeSpan::FromWeeks(int64_t inWeeks)
{
    return TimeSpan(inWeeks * TicksPerWeek);
}
