#include "TimeSpan.hpp"
#include "TickSpans.hpp"

static const int64_t LowestValue = 1LL << 63LL;

const TimeSpan TimeSpan::MinValue(LowestValue);
const TimeSpan TimeSpan::Zero(0);
const TimeSpan TimeSpan::MaxValue(~LowestValue);

TimeSpan::TimeSpan() : _ticks(0)
{
}

TimeSpan::TimeSpan(int64_t ticks) : _ticks(ticks)
{
}

TimeSpan::TimeSpan(const TimeSpan& other) : _ticks(other._ticks)
{
}

TimeSpan::~TimeSpan()
{
}

TimeSpan& TimeSpan::operator=(const TimeSpan& other)
{
    _ticks = other._ticks;
    return *this;
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

bool TimeSpan::operator==(const TimeSpan& other) const
{
    return _ticks == other._ticks;
}

bool TimeSpan::operator!=(const TimeSpan& other) const
{
    return _ticks != other._ticks;
}

bool TimeSpan::operator<(const TimeSpan& other) const
{
    return _ticks < other._ticks;
}

bool TimeSpan::operator<=(const TimeSpan& other) const
{
    return _ticks <= other._ticks;
}

bool TimeSpan::operator>(const TimeSpan& other) const
{
    return _ticks > other._ticks;
}

bool TimeSpan::operator>=(const TimeSpan& other) const
{
    return _ticks >= other._ticks;
}

const TimeSpan TimeSpan::operator+(const TimeSpan& other) const
{
    return TimeSpan(_ticks + other._ticks);
}

const TimeSpan TimeSpan::operator-(const TimeSpan& other) const
{
    return TimeSpan(_ticks - other._ticks);
}

const TimeSpan TimeSpan::operator-() const
{
    return TimeSpan(-_ticks);
}

int64_t TimeSpan::ToNanoseconds() const
{
    return _ticks * NanosecondsPerTick;
}

int64_t TimeSpan::ToMicroseconds() const
{
    return _ticks / TicksPerMicrosecond;
}

int64_t TimeSpan::ToMilliseconds() const
{
    return _ticks / TicksPerMillisecond;
}

int64_t TimeSpan::ToSeconds() const
{
    return _ticks / TicksPerSecond;
}

int64_t TimeSpan::ToMinutes() const
{
    return _ticks / TicksPerMinute;
}

int64_t TimeSpan::ToHours() const
{
    return _ticks / TicksPerHour;
}

int64_t TimeSpan::ToDays() const
{
    return _ticks / TicksPerDay;
}

int64_t TimeSpan::ToWeeks() const
{
    return _ticks / TicksPerWeek;
}

const TimeSpan TimeSpan::FromNanoseconds(int64_t nanoseconds)
{
    return TimeSpan(nanoseconds / NanosecondsPerTick);
}

const TimeSpan TimeSpan::FromMicroseconds(int64_t microseconds)
{
    return TimeSpan(microseconds * TicksPerMicrosecond);
}

const TimeSpan TimeSpan::FromMilliseconds(int64_t milliseconds)
{
    return TimeSpan(milliseconds * TicksPerMillisecond);
}

const TimeSpan TimeSpan::FromSeconds(int64_t seconds)
{
    return TimeSpan(seconds * TicksPerSecond);
}

const TimeSpan TimeSpan::FromMinutes(int64_t minutes)
{
    return TimeSpan(minutes * TicksPerMinute);
}

const TimeSpan TimeSpan::FromHours(int64_t hours)
{
    return TimeSpan(hours * TicksPerHour);
}

const TimeSpan TimeSpan::FromDays(int64_t days)
{
    return TimeSpan(days * TicksPerDay);
}

const TimeSpan TimeSpan::FromWeeks(int64_t weeks)
{
    return TimeSpan(weeks * TicksPerWeek);
}
