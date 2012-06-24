#include "DateTime.hpp"
#include "TickSpans.hpp"
#include <ctime>

static const int DaysInMonths[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31,
    30, 31 };

static const int64_t DaysPerYear = 365;
static const int64_t TicksPerYear = TicksPerDay * DaysPerYear;
static const int64_t DaysPerFourCenturies = DaysPerYear * 400 + 97;
static const int64_t DaysPerCentury = DaysPerYear * 100 + 24;
static const int64_t DaysPerFourYears = DaysPerYear * 4 + 1;

DateTime::DateTime() : mTicks(0)
{
}

DateTime::DateTime(int64_t inTicks) : mTicks(inTicks)
{
    Validate();
}

DateTime::DateTime(const DateTime& inDateTime) : mTicks(inDateTime.mTicks)
{
}

DateTime::~DateTime()
{
}

void DateTime::Validate()
{
    if (mTicks < 0) mTicks = 0;
}

int64_t DateTime::ExtractYears(int64_t& inDays) const
{
    int64_t outYear = 1;
    bool oneShy = false;

    if (inDays >= DaysPerFourCenturies)
    {
        int64_t chunks = inDays / DaysPerFourCenturies;
        outYear += chunks * 400;
        inDays -= chunks * DaysPerFourCenturies;
    }

    if (inDays == DaysPerFourCenturies - 1) oneShy = true;

    if (inDays >= DaysPerCentury)
    {
        int64_t chunks = inDays / DaysPerCentury;
        outYear += chunks * 100;
        inDays -= chunks * DaysPerCentury;
    }

    if (inDays >= DaysPerFourYears)
    {
        int64_t chunks = inDays / DaysPerFourYears;
        outYear += chunks * 4;
        inDays -= chunks * DaysPerFourYears;
    }

    if (inDays == DaysPerFourYears - 1) oneShy = true;

    if (inDays >= DaysPerYear)
    {
        int64_t chunks = inDays / DaysPerYear;
        outYear += chunks;
        inDays -= chunks * DaysPerYear;
    }

    if (inDays == 0 && oneShy)
    {
        inDays += 365;
        --outYear;
    }

    return outYear;
}

int64_t DateTime::ExtractMonth(int64_t& inDays, int inYear) const
{
    int64_t outMonth = 1;

    for (int64_t daysInMonth = DaysInMonth(outMonth, inYear);
        inDays > daysInMonth; daysInMonth = DaysInMonth(outMonth, inYear))
    {
        ++outMonth;
        inDays -= daysInMonth;
    }

    return outMonth;
}

const TimeSpan DateTime::TimeSinceMidnight() const
{
    return TimeSpan(mTicks % TicksPerDay);
}

void DateTime::SetTimeToMidnight()
{
    mTicks /= TicksPerDay;
    mTicks *= TicksPerDay;
}

bool DateTime::Set(int inYear, int inMonth, int inDay, int inHour, int inMinute,
    int inSecond, int inMillisecond, int inMicrosecond)
{
    bool outSuccess = false;

    if (inYear >= 1 && inYear <= 9999
        && inDay >= 1 && inDay <= DaysInMonth(inMonth, inYear)
        && inHour >= 0 && inHour <= 23
        && inMinute >= 0 && inMinute <= 59
        && inSecond >= 0 && inSecond <= 59
        && inMillisecond >= 0 && inMillisecond <= 999
        && inMicrosecond >= 0 && inMicrosecond <= 999)
    {
        int64_t year = inYear - 1;
        mTicks = year * TicksPerYear;

        int64_t chunks = year / 400;
        int64_t leapYears = chunks * 97;
        year -= chunks * 400;
        chunks = year / 100;
        leapYears += chunks * 24;
        year -= chunks * 100;
        chunks = year / 4;
        leapYears += chunks;

        mTicks += leapYears * TicksPerDay;

        for (int i = 1; i < inMonth; ++i)
        {
            mTicks += DaysInMonth(i, inYear) * TicksPerDay;
        }

        mTicks += TicksPerDay * (inDay - 1);
        mTicks += inHour * TicksPerHour;
        mTicks += inMinute * TicksPerMinute;
        mTicks += inSecond * TicksPerSecond;
        mTicks += inMillisecond * TicksPerMillisecond;
        mTicks += inMicrosecond * TicksPerMicrosecond;

        outSuccess = true;
    }

    return outSuccess;
}

int DateTime::DayOfWeek() const
{
    return (mTicks / TicksPerDay) % 7;
}

int DateTime::Year() const
{
    int64_t days = mTicks / TicksPerDay;
    return ExtractYears(days);
}

int DateTime::Month() const
{
    int64_t days = mTicks / TicksPerDay;
    int64_t year = ExtractYears(days);
    return ExtractMonth(days, year);
}

int DateTime::Day() const
{
    int64_t days = mTicks / TicksPerDay;
    int64_t year = ExtractYears(days);
    ExtractMonth(days, year);
    return days + 1;
}

int DateTime::Hour() const
{
    int64_t hours = mTicks / TicksPerHour;
    return hours % 24;
}

int DateTime::Minute() const
{
    int64_t minutes = mTicks / TicksPerMinute;
    return minutes % 60;
}

int DateTime::Second() const
{
    int64_t seconds = mTicks / TicksPerSecond;
    return seconds % 60;
}

int DateTime::Millisecond() const
{
    int64_t milliseconds = mTicks / TicksPerMillisecond;
    return milliseconds % 1000;
}

int DateTime::Microsecond() const
{
    int64_t microseconds = mTicks / TicksPerMicrosecond;
    return microseconds % 1000;
}

DateTime& DateTime::operator=(const DateTime& inDateTime)
{
    mTicks = inDateTime.mTicks;
    return *this;
}

DateTime& DateTime::operator+=(const TimeSpan& inTimeSpan)
{
    mTicks += inTimeSpan.Ticks();
    Validate();
    return *this;
}

DateTime& DateTime::operator-=(const TimeSpan& inTimeSpan)
{
    mTicks -= inTimeSpan.Ticks();
    Validate();
    return *this;
}

bool DateTime::operator==(const DateTime& inDateTime) const
{
    return mTicks == inDateTime.mTicks;
}

bool DateTime::operator!=(const DateTime& inDateTime) const
{
    return mTicks != inDateTime.mTicks;
}

bool DateTime::operator<(const DateTime& inDateTime) const
{
    return mTicks < inDateTime.mTicks;
}

bool DateTime::operator<=(const DateTime& inDateTime) const
{
    return mTicks <= inDateTime.mTicks;
}

bool DateTime::operator>(const DateTime& inDateTime) const
{
    return mTicks > inDateTime.mTicks;
}

bool DateTime::operator>=(const DateTime& inDateTime) const
{
    return mTicks >= inDateTime.mTicks;
}

const DateTime DateTime::operator+(const TimeSpan& inTimeSpan) const
{
    return DateTime(mTicks + inTimeSpan.Ticks());
}

const DateTime DateTime::operator-(const TimeSpan& inTimeSpan) const
{
    return DateTime(mTicks - inTimeSpan.Ticks());
}

const TimeSpan DateTime::operator-(const DateTime& inDateTime) const
{
    return TimeSpan(mTicks - inDateTime.mTicks);
}

int DateTime::DaysInMonth(int inMonth, int inYear)
{
    int outDays = 0;

    if (inMonth >= 1 && inMonth <= 12)
    {
        outDays = DaysInMonths[inMonth];

        if (inMonth == 2 && IsLeapYear(inYear))
            outDays = 29;
    }

    return outDays;
}

int DateTime::DaysInYear(int inYear)
{
    return IsLeapYear(inYear) ? 366 : 365;
}

bool DateTime::IsLeapYear(int inYear)
{
    if (inYear % 4)
        return false;

    if (inYear % 100)
        return true;

    if (inYear % 400)
        return false;

    return true;
}

const char* DateTime::DayToString(int inDayOfWeek)
{
    const char* outDayName = "invalid day";

    switch (inDayOfWeek)
    {
        case 0:
            outDayName = "Monday";
            break;

        case 1:
            outDayName = "Tuesday";
            break;

        case 2:
            outDayName = "Wednesday";
            break;

        case 3:
            outDayName = "Thursday";
            break;

        case 4:
            outDayName = "Friday";
            break;

        case 5:
            outDayName = "Saturday";
            break;

        case 6:
            outDayName = "Sunday";
            break;

        default:
            break;
    }

    return outDayName;
}

const DateTime DateTime::LocalTime()
{
    time_t rawTime;
    time(&rawTime);
    tm* timeInfo = localtime(&rawTime);
    int second = timeInfo->tm_sec;

    // http://www.cplusplus.com/reference/clibrary/ctime/tm/
    if (second > 59)
        second = 59;

    DateTime outDateTime;
    outDateTime.Set(timeInfo->tm_year + 1900, timeInfo->tm_mon + 1,
        timeInfo->tm_mday, timeInfo->tm_hour, timeInfo->tm_min, second);

    return outDateTime;
}
