#ifndef DATETIME_H
#define DATETIME_H

#include <stdint.h>

class DateTime
{
    public:
        DateTime();
        DateTime(const DateTime& inDateTime);
        ~DateTime();

        DateTime& operator=(const DateTime& inDateTime);
        bool operator==(const DateTime& inDateTime) const;
        bool operator!=(const DateTime& inDateTime) const;
        bool operator<(const DateTime& inDateTime) const;
        bool operator<=(const DateTime& inDateTime) const;
        bool operator>(const DateTime& inDateTime) const;
        bool operator>=(const DateTime& inDateTime) const;

        inline int64_t Ticks() const { return mTicks; }

        void RemoveTime();
        bool Set(int inYear, int inMonth, int inDay);
        bool Set(int inYear, int inMonth, int inDay, int inHour, int inMinute,
            int inSecond);

        int DayOfWeek() const;
        int Year() const;
        int Month() const;
        int Day() const;
        int Hour() const;
        int Minute() const;
        int Second() const;

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
