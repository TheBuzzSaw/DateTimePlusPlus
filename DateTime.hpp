#ifndef DATETIME_HPP
#define DATETIME_HPP

#include "TimeSpan.hpp"

class DateTime
{
    public:
        DateTime();
        explicit DateTime(int64_t ticks);
        DateTime(int year, int month, int day, int hour = 0, int minute = 0,
            int second = 0, int millisecond = 0, int microsecond = 0);
        DateTime(const DateTime& dateTime);
        ~DateTime();

        inline int64_t Ticks() const { return _ticks; }
        inline operator bool() const { return _ticks > 0; }

        DateTime& operator=(const DateTime& dateTime);
        DateTime& operator+=(const TimeSpan& timeSpan);
        DateTime& operator-=(const TimeSpan& timeSpan);

        bool operator==(const DateTime& dateTime) const;
        bool operator!=(const DateTime& dateTime) const;
        bool operator<(const DateTime& dateTime) const;
        bool operator<=(const DateTime& dateTime) const;
        bool operator>(const DateTime& dateTime) const;
        bool operator>=(const DateTime& dateTime) const;

        const DateTime operator+(const TimeSpan& timeSpan) const;
        const DateTime operator-(const TimeSpan& timeSpan) const;
        const TimeSpan operator-(const DateTime& dateTime) const;

        const TimeSpan TimeSinceMidnight() const;
        const DateTime DateOnly() const;
        bool Set(int year, int month, int day, int hour = 0,
            int minute = 0, int second = 0, int millisecond = 0,
            int microsecond = 0);

        int DayOfWeek() const;
        int Year() const;
        int Month() const;
        int Day() const;
        int Hour() const;
        int Minute() const;
        int Second() const;
        int Millisecond() const;
        int Microsecond() const;

        static int DaysInMonth(int month, int year = 1);
        static int DaysInYear(int year);
        static bool IsLeapYear(int year);
        static const char* DayToString(int dayOfWeek);
        static const DateTime LocalTime();
        static const DateTime UtcTime();

    private:
        void Validate();
        int64_t ExtractYears(int64_t& days) const;
        int64_t ExtractMonth(int64_t& days, int year) const;

        int64_t _ticks;
};

template<typename CharT, typename TraitsT>
std::basic_ostream<CharT, TraitsT>& operator<<(
    std::basic_ostream<CharT, TraitsT>& inStream, const DateTime& dateTime)
{
    inStream << dateTime.Year() << '-' << dateTime.Month() << '-'
        << dateTime.Day() << ' ';

    inStream << dateTime.Hour() << ':';

    int minute = dateTime.Minute();
    if (minute < 10) inStream << '0';
    inStream << minute << ':';

    int second = dateTime.Second();
    if (second < 10) inStream << '0';
    inStream << second;

    return inStream;
}

#endif
