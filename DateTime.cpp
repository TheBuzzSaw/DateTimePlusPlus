#include "DateTime.hpp"
#include <ctime>

static const int DaysInMonths[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31,
    30, 31 };

static const int64_t TicksPerYear = TicksPerDay * 365;
static const int64_t TicksPerLeapYear = TicksPerDay * 366;

DateTime::DateTime() : mTicks(0)
{
}

DateTime::DateTime(int64_t inTicks) : mTicks(inTicks)
{
}

DateTime::DateTime(const DateTime& inDateTime) : mTicks(inDateTime.mTicks)
{
}

DateTime::~DateTime()
{
}

DateTime& DateTime::operator=(const DateTime& inDateTime)
{
    mTicks = inDateTime.mTicks;
    return *this;
}

DateTime DateTime::Now()
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

void DateTime::SetTimeToMidnight()
{
    mTicks /= TicksPerDay;
    mTicks *= TicksPerDay;
}

bool DateTime::Set(int inYear, int inMonth, int inDay, int inHour, int inMinute,
    int inSecond, int inMillisecond)
{
    bool outSuccess = false;

    if (inYear >= 1 && inYear <= 9999 && inHour >= 0 && inHour <= 23
        && inMinute >= 0 && inMinute <= 59 && inSecond >= 0 && inSecond <= 59
        && inMillisecond >= 0 && inMillisecond <= 999)
    {
        int maxDays = DaysInMonth(inMonth, inYear);

        if (inDay > 0 && inDay < maxDays)
        {
            mTicks = (inYear - 1) * TicksPerYear;

            for (int i = 4; i < inYear; i += 4)
            {
                if (IsLeapYear(i))
                    mTicks += TicksPerDay;
            }

            for (int i = 1; i < inMonth; ++i)
            {
                mTicks += DaysInMonth(i, inYear) * TicksPerDay;
            }

            for (int i = 1; i < inDay; ++i)
            {
                mTicks += TicksPerDay;
            }

            mTicks += inHour * TicksPerHour;
            mTicks += inMinute * TicksPerMinute;
            mTicks += inSecond * TicksPerSecond;
            mTicks += inMillisecond * TicksPerMillisecond;

            outSuccess = true;
        }
    }

    return outSuccess;
}

void DateTime::AddDays(int64_t inDays)
{
    mTicks += inDays * TicksPerDay;
}

void DateTime::AddHours(int64_t inHours)
{
    mTicks += inHours * TicksPerHour;
}

void DateTime::AddMinutes(int64_t inMinutes)
{
    mTicks += inMinutes * TicksPerMinute;
}

void DateTime::AddSeconds(int64_t inSeconds)
{
    mTicks += inSeconds * TicksPerSecond;
}

void DateTime::AddMilliseconds(int64_t inMilliseconds)
{
    mTicks += inMilliseconds * TicksPerMillisecond;
}

int DateTime::DayOfWeek() const
{
    return (mTicks / TicksPerDay) % 7;
}

int DateTime::Year() const
{
    int64_t days = mTicks / TicksPerDay;
    int64_t outYear = 1;
    int64_t daysInYear = DaysInYear(outYear);

    while (days >= daysInYear)
    {
        ++outYear;
        days -= daysInYear;
        daysInYear = DaysInYear(outYear);
    }

    return outYear;
}

int DateTime::Month() const
{
    int64_t days = mTicks / TicksPerDay;
    int64_t year = 1;
    int64_t daysInYear = DaysInYear(year);

    while (days >= daysInYear)
    {
        ++year;
        days -= daysInYear;
        daysInYear = DaysInYear(year);
    }

    int64_t outMonth = 1;
    int64_t daysInMonth = DaysInMonth(outMonth, year);

    while (daysInMonth > 0 && days >= daysInMonth)
    {
        ++outMonth;
        days -= daysInMonth;
        daysInMonth = DaysInMonth(outMonth, year);
    }

    return outMonth;
}

int DateTime::Day() const
{
    int64_t days = mTicks / TicksPerDay;
    int64_t year = 1;
    int64_t daysInYear = DaysInYear(year);

    while (days >= daysInYear)
    {
        ++year;
        days -= daysInYear;
        daysInYear = DaysInYear(year);
    }

    int64_t month = 1;
    int64_t daysInMonth = DaysInMonth(month, year);

    while (daysInMonth > 0 && days >= daysInMonth)
    {
        ++month;
        days -= daysInMonth;
        daysInMonth = DaysInMonth(month, year);
    }

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

TimeSpan DateTime::operator-(const DateTime& inDateTime) const
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
