#ifndef TIMESPAN_HPP
#define TIMESPAN_HPP

#include <stdint.h>
#include <iostream>

class TimeSpan
{
    public:
        TimeSpan();
        explicit TimeSpan(int64_t inTicks);
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

        const TimeSpan operator+(const TimeSpan& inTimeSpan) const;
        const TimeSpan operator-(const TimeSpan& inTimeSpan) const;
        const TimeSpan operator-() const;

        int64_t Microseconds() const;
        int64_t Milliseconds() const;
        int64_t Seconds() const;
        int64_t Minutes() const;
        int64_t Hours() const;
        int64_t Days() const;
        int64_t Weeks() const;

        static const TimeSpan FromNanoseconds(int64_t inNanoseconds);
        static const TimeSpan FromMicroseconds(int64_t inMicroseconds);
        static const TimeSpan FromMilliseconds(int64_t inMilliseconds);
        static const TimeSpan FromSeconds(int64_t inSeconds);
        static const TimeSpan FromMinutes(int64_t inMinutes);
        static const TimeSpan FromHours(int64_t inHours);
        static const TimeSpan FromDays(int64_t inDays);
        static const TimeSpan FromWeeks(int64_t inWeeks);

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

    count = inTimeSpan.Milliseconds() - inTimeSpan.Seconds() * 1000;
    inStream << count << "ms";

    count = inTimeSpan.Microseconds() - inTimeSpan.Milliseconds() * 1000;
    inStream << count << "us";

    return inStream;
}

#endif
