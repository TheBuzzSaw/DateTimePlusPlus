#ifndef TIMESPAN_HPP
#define TIMESPAN_HPP

#include <stdint.h>
#include <iostream>

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
        TimeSpan();
        explicit TimeSpan(int64_t ticks);
        TimeSpan(const TimeSpan& timeSpan);
        ~TimeSpan();

        inline int64_t Ticks() const { return _ticks; }

        TimeSpan& operator=(const TimeSpan& timeSpan);
        TimeSpan& operator+=(const TimeSpan& timeSpan);
        TimeSpan& operator-=(const TimeSpan& timeSpan);

        bool operator==(const TimeSpan& timeSpan) const;
        bool operator!=(const TimeSpan& timeSpan) const;
        bool operator<(const TimeSpan& timeSpan) const;
        bool operator<=(const TimeSpan& timeSpan) const;
        bool operator>(const TimeSpan& timeSpan) const;
        bool operator>=(const TimeSpan& timeSpan) const;

        const TimeSpan operator+(const TimeSpan& timeSpan) const;
        const TimeSpan operator-(const TimeSpan& timeSpan) const;
        const TimeSpan operator-() const;

        int64_t ToNanoseconds() const;
        int64_t ToMicroseconds() const;
        int64_t ToMilliseconds() const;
        int64_t ToSeconds() const;
        int64_t ToMinutes() const;
        int64_t ToHours() const;
        int64_t ToDays() const;
        int64_t ToWeeks() const;

        static const TimeSpan FromNanoseconds(int64_t nanoseconds);
        static const TimeSpan FromMicroseconds(int64_t microseconds);
        static const TimeSpan FromMilliseconds(int64_t milliseconds);
        static const TimeSpan FromSeconds(int64_t seconds);
        static const TimeSpan FromMinutes(int64_t minutes);
        static const TimeSpan FromHours(int64_t hours);
        static const TimeSpan FromDays(int64_t days);
        static const TimeSpan FromWeeks(int64_t weeks);

    private:
        int64_t _ticks;
};

template<typename CharT, typename TraitsT>
std::basic_ostream<CharT, TraitsT>& operator<<(
    std::basic_ostream<CharT, TraitsT>& stream, const TimeSpan& timeSpan)
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
