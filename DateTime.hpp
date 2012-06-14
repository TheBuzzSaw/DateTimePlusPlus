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
        bool operator==(const DateTime& inDateTime) const;
        bool operator!=(const DateTime& inDateTime) const;
        bool operator<(const DateTime& inDateTime) const;
        bool operator<=(const DateTime& inDateTime) const;
        bool operator>(const DateTime& inDateTime) const;
        bool operator>=(const DateTime& inDateTime) const;
        TimeSpan operator-(const DateTime& inDateTime) const;

        void SetTimeToMidnight();
        bool Set(int inYear = 1, int inMonth = 1, int inDay = 1, int inHour = 0,
            int inMinute = 0, int inSecond = 0, int inMillisecond = 0);

        void AddDays(int64_t inDays);
        void AddHours(int64_t inHours);
        void AddMinutes(int64_t inMinutes);
        void AddSeconds(int64_t inSeconds);
        void AddMilliseconds(int64_t inMilliseconds);

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

#endif
