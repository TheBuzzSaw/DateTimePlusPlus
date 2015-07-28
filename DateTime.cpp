#include "DateTime.hpp"
#include <ctime>

static const int DaysInMonths[] =
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

static constexpr int64_t DaysPerYear = 365;
static constexpr int64_t TicksPerYear = TicksPerDay * DaysPerYear;
static constexpr int64_t DaysPerFourCenturies = DaysPerYear * 400 + 97;
static constexpr int64_t DaysPerCentury = DaysPerYear * 100 + 24;
static constexpr int64_t DaysPerFourYears = DaysPerYear * 4 + 1;

static int64_t ExtractYears(int64_t& days)
{
    int64_t year = 1;

    if (days >= DaysPerFourCenturies)
    {
        int64_t chunks = days / DaysPerFourCenturies;
        year += chunks * 400;
        days -= chunks * DaysPerFourCenturies;
    }

    if (days >= DaysPerCentury)
    {
        int64_t chunks = days / DaysPerCentury;
        if (chunks == 4) chunks = 3;
        year += chunks * 100;
        days -= chunks * DaysPerCentury;
    }

    if (days >= DaysPerFourYears)
    {
        int64_t chunks = days / DaysPerFourYears;
        year += chunks * 4;
        days -= chunks * DaysPerFourYears;
    }

    if (days >= DaysPerYear)
    {
        int64_t chunks = days / DaysPerYear;
        if (chunks == 4) chunks = 3;
        year += chunks;
        days -= chunks * DaysPerYear;
    }

    return year;
}

static int64_t ExtractMonth(int64_t& days, int year)
{
    int64_t month = 1;

    for (int64_t daysInMonth = DateTime::DaysInMonth(month, year);
        days >= daysInMonth; daysInMonth = DateTime::DaysInMonth(month, year))
    {
        ++month;
        days -= daysInMonth;
    }

    return month;
}

DateTime::DateTime(
    int year,
    int month,
    int day,
    int hour,
    int minute,
    int second,
    int millisecond,
    int microsecond,
    int ticks)
{
    if (InRange(year, 1, 9999) &&
        InRange(day, 1, DaysInMonth(month, year)) &&
        InRange(hour, 0, 23) &&
        InRange(minute, 0, 59) &&
        InRange(second, 0, 59) &&
        InRange(millisecond, 0, 999) &&
        InRange(microsecond, 0, 999) &&
        InRange(ticks, 0, 9))
    {
        int64_t days = day - 1;

        for (int i = 1; i < month; ++i)
            days += DaysInMonth(i, year);

        --year;
        days += (year * DaysPerYear) + (year / 4) - (year / 100) + (year / 400);

        _ticks =
            days * TicksPerDay +
            hour * TicksPerHour +
            minute * TicksPerMinute +
            second * TicksPerSecond +
            millisecond * TicksPerMillisecond +
            microsecond * TicksPerMicrosecond +
            ticks;
    }
    else
    {
        _ticks = 0;
    }
}

const DateTime DateTime::Date() const
{
    int64_t days = _ticks / TicksPerDay;
    return DateTime(days * TicksPerDay);
}

int DateTime::DayOfWeek() const
{
    return (_ticks / TicksPerDay) % 7;
}

int DateTime::Year() const
{
    int64_t days = _ticks / TicksPerDay;
    return ExtractYears(days);
}

int DateTime::Month() const
{
    int64_t days = _ticks / TicksPerDay;
    int64_t year = ExtractYears(days);
    return ExtractMonth(days, year);
}

int DateTime::Day() const
{
    int64_t days = _ticks / TicksPerDay;
    int64_t year = ExtractYears(days);
    ExtractMonth(days, year);
    return days + 1;
}

int DateTime::Hour() const
{
    int64_t hours = _ticks / TicksPerHour;
    return hours % 24;
}

int DateTime::Minute() const
{
    int64_t minutes = _ticks / TicksPerMinute;
    return minutes % 60;
}

int DateTime::Second() const
{
    int64_t seconds = _ticks / TicksPerSecond;
    return seconds % 60;
}

int DateTime::Millisecond() const
{
    int64_t milliseconds = _ticks / TicksPerMillisecond;
    return milliseconds % 1000;
}

int DateTime::Microsecond() const
{
    int64_t microseconds = _ticks / TicksPerMicrosecond;
    return microseconds % 1000;
}

DateTime& DateTime::operator+=(const TimeSpan& timeSpan)
{
    _ticks = SafeTicks(_ticks += timeSpan.Ticks());
    return *this;
}

DateTime& DateTime::operator-=(const TimeSpan& timeSpan)
{
    _ticks = SafeTicks(_ticks -= timeSpan.Ticks());
    return *this;
}

int DateTime::DaysInMonth(int month, int year)
{
    int days = 0;

    if (InRange(month, 1, 12))
    {
        days = DaysInMonths[month];

        if (month == 2 && IsLeapYear(year))
            days = 29;
    }

    return days;
}

int DateTime::DaysInYear(int year)
{
    return 365 + IsLeapYear(year);
}

bool DateTime::IsLeapYear(int year)
{
    if (year % 4)
        return false;

    if (year % 100)
        return true;

    return !(year % 400);
}

const char* DateTime::DayToString(int dayOfWeek)
{
    const char* dayName = "invalid day";

    switch (dayOfWeek)
    {
        case 0: dayName = "Monday"; break;
        case 1: dayName = "Tuesday"; break;
        case 2: dayName = "Wednesday"; break;
        case 3: dayName = "Thursday"; break;
        case 4: dayName = "Friday"; break;
        case 5: dayName = "Saturday"; break;
        case 6: dayName = "Sunday"; break;
        default: break;
    }

    return dayName;
}

static const DateTime GetDateTime(const tm& timeInfo)
{
    return DateTime(
        timeInfo.tm_year + 1900,
        timeInfo.tm_mon + 1,
        timeInfo.tm_mday,
        timeInfo.tm_hour,
        timeInfo.tm_min,
        Min(timeInfo.tm_sec, 59)); // Can exceed 59! :(

    // http://www.cplusplus.com/reference/clibrary/ctime/tm/
}

const DateTime DateTime::LocalTime()
{
    time_t rawTime;
    time(&rawTime);
    return GetDateTime(*localtime(&rawTime));
}

const DateTime DateTime::UtcTime()
{
    time_t rawTime;
    time(&rawTime);
    return GetDateTime(*gmtime(&rawTime));
}
