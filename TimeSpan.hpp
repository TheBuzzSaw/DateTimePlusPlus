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
        TimeSpan(int64_t inTicks);
        TimeSpan(const TimeSpan& inTimeSpan);
        ~TimeSpan();

        inline int64_t Ticks() const { return mTicks; }

        TimeSpan& operator=(const TimeSpan& inTimeSpan);
        TimeSpan& operator+=(const TimeSpan& inTimeSpan);
        TimeSpan& operator-=(const TimeSpan& inTimeSpan);

        bool operator==(const TimeSpan& inTimeSpan);
        bool operator!=(const TimeSpan& inTimeSpan);
        bool operator<(const TimeSpan& inTimeSpan);
        bool operator<=(const TimeSpan& inTimeSpan);
        bool operator>(const TimeSpan& inTimeSpan);
        bool operator>=(const TimeSpan& inTimeSpan);

        int64_t Microseconds() const;
        int64_t Milliseconds() const;
        int64_t Seconds() const;
        int64_t Minutes() const;
        int64_t Hours() const;
        int64_t Days() const;
        int64_t Weeks() const;

        static TimeSpan Microseconds(int64_t inMicroseconds);
        static TimeSpan Milliseconds(int64_t inMilliseconds);
        static TimeSpan Seconds(int64_t inSeconds);
        static TimeSpan Minutes(int64_t inMinutes);
        static TimeSpan Hours(int64_t inHours);
        static TimeSpan Days(int64_t inDays);
        static TimeSpan Weeks(int64_t inWeeks);

    protected:
    private:
        int64_t mTicks;
};

template<typename CharT, typename TraitsT>
std::basic_ostream<CharT, TraitsT>& operator<<(
    std::basic_ostream<CharT, TraitsT>& inStream, const TimeSpan& inTimeSpan)
{
    int64_t count = inTimeSpan.Weeks();
    inStream << count << 'w';

    count = inTimeSpan.Days() - inTimeSpan.Weeks() * 7;
    inStream << count << 'd';

    count = inTimeSpan.Hours() - inTimeSpan.Days() * 24;
    inStream << count << 'h';

    count = inTimeSpan.Minutes() - inTimeSpan.Hours() * 60;
    inStream << count << 'm';

    count = inTimeSpan.Seconds() - inTimeSpan.Minutes() * 60;
    inStream << count << 's';

    return inStream;
}

#endif
