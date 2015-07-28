#ifndef DATETIME_HPP
#define DATETIME_HPP

#include "TimeSpan.hpp"

constexpr int64_t MinTickCount = 0LL;
constexpr int64_t MaxTickCount = 3155378975999999999LL;

template<typename T>
constexpr T Min(const T& a, const T& b)
{
    return b < a ? b : a;
}

template<typename T>
constexpr T Max(const T& a, const T& b)
{
    return a < b ? b : a;
}

template<typename T>
constexpr T Bound(const T& value, const T& low, const T& high)
{
    return Min(Max(value, low), high);
}

template<typename T>
constexpr bool InRange(const T& value, const T& low, const T& high)
{
    return low <= value && value <= high;
}

constexpr int64_t SafeTicks(int64_t ticks)
{
    return Bound(ticks, MinTickCount, MaxTickCount);
}

class DateTime
{
    public:
        constexpr DateTime() : _ticks(0) {}
        explicit constexpr DateTime(int64_t ticks) : _ticks(SafeTicks(ticks)) {}
        DateTime(
            int year,
            int month,
            int day,
            int hour = 0,
            int minute = 0,
            int second = 0,
            int millisecond = 0,
            int microsecond = 0,
            int ticks = 0);
        constexpr DateTime(const DateTime&) = default;
        ~DateTime() = default;

        constexpr int64_t Ticks() const { return _ticks; }
        constexpr operator bool() const { return _ticks > 0; }

        DateTime& operator=(const DateTime& other) = default;
        DateTime& operator+=(const TimeSpan& timeSpan);
        DateTime& operator-=(const TimeSpan& timeSpan);

        constexpr bool operator==(const DateTime& other) const
        {
            return _ticks == other._ticks;
        }

        constexpr bool operator!=(const DateTime& other) const
        {
            return _ticks != other._ticks;
        }

        constexpr bool operator<(const DateTime& other) const
        {
            return _ticks < other._ticks;
        }

        constexpr bool operator<=(const DateTime& other) const
        {
            return _ticks <= other._ticks;
        }

        constexpr bool operator>(const DateTime& other) const
        {
            return _ticks > other._ticks;
        }

        constexpr bool operator>=(const DateTime& other) const
        {
            return _ticks >= other._ticks;
        }

        constexpr DateTime operator+(const TimeSpan& timeSpan) const
        {
            return DateTime(_ticks + timeSpan.Ticks());
        }

        constexpr DateTime operator-(const TimeSpan& timeSpan) const
        {
            return DateTime(_ticks - timeSpan.Ticks());
        }

        const TimeSpan operator-(const DateTime& other) const
        {
            return TimeSpan(_ticks - other._ticks);
        }

        constexpr const TimeSpan TimeOfDay() const
        {
            return TimeSpan(_ticks % TicksPerDay);
        }

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

        static constexpr DateTime MinValue()
        {
            return DateTime(MinTickCount);
        }

        static constexpr DateTime MaxValue()
        {
            return DateTime(MaxTickCount);
        }

    private:
        int64_t _ticks;
};

template<typename CharT, typename TraitsT>
std::basic_ostream<CharT, TraitsT>& operator<<(
    std::basic_ostream<CharT, TraitsT>& stream,
    const DateTime& dateTime)
{
    stream
        << dateTime.Year()
        << '-'
        << dateTime.Month()
        << '-'
        << dateTime.Day()
        << ' ';

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
