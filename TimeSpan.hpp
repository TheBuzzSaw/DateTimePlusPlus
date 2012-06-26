#ifndef TIMESPAN_HPP
#define TIMESPAN_HPP

#include <stdint.h>
#include <iostream>

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

        int64_t Microseconds() const;
        int64_t Milliseconds() const;
        int64_t Seconds() const;
        int64_t Minutes() const;
        int64_t Hours() const;
        int64_t Days() const;
        int64_t Weeks() const;

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
    int64_t count = timeSpan.Weeks();
    stream << count << 'w';

    count = timeSpan.Days() - timeSpan.Weeks() * 7;
    stream << count << 'd';

    count = timeSpan.Hours() - timeSpan.Days() * 24;
    stream << count << 'h';

    count = timeSpan.Minutes() - timeSpan.Hours() * 60;
    stream << count << 'm';

    count = timeSpan.Seconds() - timeSpan.Minutes() * 60;
    stream << count << 's';

    count = timeSpan.Milliseconds() - timeSpan.Seconds() * 1000;
    stream << count << "ms";

    count = timeSpan.Microseconds() - timeSpan.Milliseconds() * 1000;
    stream << count << "us";

    return stream;
}

#endif
