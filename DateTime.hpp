#ifndef DATETIME_HPP
#define DATETIME_HPP

#include "TimeSpan.hpp"

class DateTime
{
    public:
        DateTime();
        explicit DateTime(int64_t ticks);
        DateTime(int year, int month, int day, int hour = 0, int minute = 0,
            int second = 0, int millisecond = 0, int microsecond = 0,
            int ticks = 0);
        DateTime(const DateTime& other);
        ~DateTime();

        inline int64_t Ticks() const { return _ticks; }
        inline operator bool() const { return _ticks > 0; }

        DateTime& operator=(const DateTime& other);
        DateTime& operator+=(const TimeSpan& timeSpan);
        DateTime& operator-=(const TimeSpan& timeSpan);

        bool operator==(const DateTime& other) const;
        bool operator!=(const DateTime& other) const;
        bool operator<(const DateTime& other) const;
        bool operator<=(const DateTime& other) const;
        bool operator>(const DateTime& other) const;
        bool operator>=(const DateTime& other) const;

        const DateTime operator+(const TimeSpan& timeSpan) const;
        const DateTime operator-(const TimeSpan& timeSpan) const;
        const TimeSpan operator-(const DateTime& other) const;

        const TimeSpan TimeOfDay() const;
        const DateTime Date() const;

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

        static const DateTime MinValue;
        static const DateTime MaxValue;

    private:
        int64_t _ticks;
};

template<typename CharT, typename TraitsT>
std::basic_ostream<CharT, TraitsT>& operator<<(
    std::basic_ostream<CharT, TraitsT>& stream, const DateTime& dateTime)
{
    stream << dateTime.Year() << '-' << dateTime.Month() << '-'
        << dateTime.Day() << ' ';

    stream << dateTime.Hour() << ':';

    int minute = dateTime.Minute();
    if (minute < 10) stream << '0';
    stream << minute << ':';

    int second = dateTime.Second();
    if (second < 10) stream << '0';
    stream << second;

    return stream;
}

#endif
