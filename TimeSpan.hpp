#ifndef TIMESPAN_HPP
#define TIMESPAN_HPP

#include <cstdint>
#include <iostream>

const int64_t LowestValue = 1LL << 63LL;
const int64_t NanosecondsPerTick = 100;
const int64_t TicksPerMicrosecond = 10;
const int64_t TicksPerMillisecond = TicksPerMicrosecond * 1000;
const int64_t TicksPerSecond = TicksPerMillisecond * 1000;
const int64_t TicksPerMinute = TicksPerSecond * 60;
const int64_t TicksPerHour = TicksPerMinute * 60;
const int64_t TicksPerDay = TicksPerHour * 24;
const int64_t TicksPerWeek = TicksPerDay * 7;

class TimeSpan
{
    public:
        constexpr TimeSpan() : _ticks(0) {}
        explicit constexpr TimeSpan(int64_t ticks) : _ticks(ticks) {}
        TimeSpan(int hour, int minute, int second);
        TimeSpan(const TimeSpan& other) = default;
        ~TimeSpan() = default;

        constexpr int64_t Ticks() const { return _ticks; }

        TimeSpan& operator=(const TimeSpan& other) = default;
        TimeSpan& operator+=(const TimeSpan& other);
        TimeSpan& operator-=(const TimeSpan& other);

        constexpr bool operator==(const TimeSpan& other) const
        {
            return _ticks == other._ticks;
        }

        constexpr bool operator!=(const TimeSpan& other) const
        {
            return _ticks != other._ticks;
        }

        constexpr bool operator<(const TimeSpan& other) const
        {
            return _ticks < other._ticks;
        }

        constexpr bool operator<=(const TimeSpan& other) const
        {
            return _ticks <= other._ticks;
        }

        constexpr bool operator>(const TimeSpan& other) const
        {
            return _ticks > other._ticks;
        }

        constexpr bool operator>=(const TimeSpan& other) const
        {
            return _ticks >= other._ticks;
        }

        constexpr const TimeSpan operator+(const TimeSpan& other) const
        {
            return TimeSpan(_ticks + other._ticks);
        }

        constexpr const TimeSpan operator-(const TimeSpan& other) const
        {
            return TimeSpan(_ticks - other._ticks);
        }

        constexpr const TimeSpan operator-() const
        {
            return TimeSpan(-_ticks);
        }

        constexpr int64_t ToNanoseconds() const
        {
            return _ticks * NanosecondsPerTick;
        }

        constexpr int64_t ToMicroseconds() const
        {
            return _ticks / TicksPerMicrosecond;
        }

        constexpr int64_t ToMilliseconds() const
        {
            return _ticks / TicksPerMillisecond;
        }

        constexpr int64_t ToSeconds() const
        {
            return _ticks / TicksPerSecond;
        }

        constexpr int64_t ToMinutes() const
        {
            return _ticks / TicksPerMinute;
        }

        constexpr int64_t ToHours() const
        {
            return _ticks / TicksPerHour;
        }

        constexpr int64_t ToDays() const
        {
            return _ticks / TicksPerDay;
        }

        constexpr int64_t ToWeeks() const
        {
            return _ticks / TicksPerWeek;
        }

        static constexpr const TimeSpan FromNanoseconds(int64_t nanoseconds)
        {
            return TimeSpan(nanoseconds / NanosecondsPerTick);
        }

        static constexpr const TimeSpan FromMicroseconds(int64_t microseconds)
        {
            return TimeSpan(microseconds * TicksPerMicrosecond);
        }

        static constexpr const TimeSpan FromMilliseconds(int64_t milliseconds)
        {
            return TimeSpan(milliseconds * TicksPerMillisecond);
        }

        static constexpr const TimeSpan FromSeconds(int64_t seconds)
        {
            return TimeSpan(seconds * TicksPerSecond);
        }

        static constexpr const TimeSpan FromMinutes(int64_t minutes)
        {
            return TimeSpan(minutes * TicksPerMinute);
        }

        static constexpr const TimeSpan FromHours(int64_t hours)
        {
            return TimeSpan(hours * TicksPerHour);
        }

        static constexpr const TimeSpan FromDays(int64_t days)
        {
            return TimeSpan(days * TicksPerDay);
        }

        static constexpr const TimeSpan FromWeeks(int64_t weeks)
        {
            return TimeSpan(weeks * TicksPerWeek);
        }

        static constexpr const TimeSpan MinValue()
        {
            return TimeSpan(LowestValue);
        }

        static constexpr const TimeSpan Zero()
        {
            return TimeSpan(0);
        }

        static constexpr const TimeSpan MaxValue()
        {
            return TimeSpan(~LowestValue);
        }

    private:
        int64_t _ticks;
};

template<typename CharT, typename TraitsT>
std::basic_ostream<CharT, TraitsT>& operator<<(
    std::basic_ostream<CharT, TraitsT>& stream,
    const TimeSpan& timeSpan)
{
    int64_t count = timeSpan.ToWeeks();
    stream << count << 'w';

    count = timeSpan.ToDays() - timeSpan.ToWeeks() * 7;
    stream << count << 'd';

    count = timeSpan.ToHours() - timeSpan.ToDays() * 24;
    stream << count << 'h';

    count = timeSpan.ToMinutes() - timeSpan.ToHours() * 60;
    stream << count << 'm';

    count = timeSpan.ToSeconds() - timeSpan.ToMinutes() * 60;
    stream << count << 's';

    count = timeSpan.ToMilliseconds() - timeSpan.ToSeconds() * 1000;
    stream << count << "ms";

    count = timeSpan.ToMicroseconds() - timeSpan.ToMilliseconds() * 1000;
    stream << count << "us";

    return stream;
}

#endif
