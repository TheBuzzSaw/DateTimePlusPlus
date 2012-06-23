#ifndef DATETIME_HPP
#define DATETIME_HPP

#include "TimeSpan.hpp"

class DateTime
{
    public:
        DateTime();
        DateTime(int64_t inTicks);
        DateTime(const DateTime& inDateTime);
        ~DateTime();

        inline int64_t Ticks() const { return mTicks; }

        DateTime& operator=(const DateTime& inDateTime);
        DateTime& operator+=(const TimeSpan& inTimeSpan);
        DateTime& operator-=(const TimeSpan& inTimeSpan);

        bool operator==(const DateTime& inDateTime) const;
        bool operator!=(const DateTime& inDateTime) const;
        bool operator<(const DateTime& inDateTime) const;
        bool operator<=(const DateTime& inDateTime) const;
        bool operator>(const DateTime& inDateTime) const;
        bool operator>=(const DateTime& inDateTime) const;

        DateTime operator+(const TimeSpan& inTimeSpan) const;
        DateTime operator-(const TimeSpan& inTimeSpan) const;
        TimeSpan operator-(const DateTime& inDateTime) const;

        void SetTimeToMidnight();
        bool Set(int inYear, int inMonth, int inDay, int inHour = 0,
            int inMinute = 0, int inSecond = 0, int inMillisecond = 0,
            int inMicrosecond = 0);

        int DayOfWeek() const;
        int Year() const;
        int Month() const;
        int Day() const;
        int Hour() const;
        int Minute() const;
        int Second() const;
        int Millisecond() const;

        static int DaysInMonth(int inMonth, int inYear = 1);
        static int DaysInYear(int inYear);
        static bool IsLeapYear(int inYear);
        static const char* DayToString(int inDayOfWeek);
        static DateTime Now();

    protected:
    private:
        int64_t mTicks;
};

template<typename CharT, typename TraitsT>
std::basic_ostream<CharT, TraitsT>& operator<<(
    std::basic_ostream<CharT, TraitsT>& inStream, const DateTime& inDateTime)
{
    inStream << inDateTime.Year() << '-' << inDateTime.Month() << '-'
        << inDateTime.Day() << ' ';

    inStream << inDateTime.Hour() << ':';

    int minute = inDateTime.Minute();
    if (minute < 10) inStream << '0';
    inStream << minute << ':';

    int second = inDateTime.Second();
    if (second < 10) inStream << '0';
    inStream << second;

    return inStream;
}

#endif
