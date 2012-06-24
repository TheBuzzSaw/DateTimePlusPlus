#include "DateTime.hpp"

#include <iostream>
using namespace std;

void Sleep(TimeSpan inTimeSpan);
const DateTime GetNativeTime();
const TimeSpan RawTimer();
void ResetTimer();
const TimeSpan ReadTimer();

int main(int argc, char** argv)
{
    cout << "size: " << sizeof(DateTime) << endl;

    DateTime a = DateTime::LocalTime();
    DateTime b = a;
    b.SetTimeToMidnight();

    TimeSpan gap = a - b;

    cout << gap << endl;

    a += TimeSpan::FromMinutes(5);

    int day = a.DayOfWeek();
    cout << DateTime::DayToString(day) << endl;
    cout << "5 minutes from now: " << a << endl;
    cout << "native UTC time: " << GetNativeTime() << endl;

    a.Set(2012, 12, 31);
    cout << "Dec 31, yes? " << a << endl;

    ResetTimer();
    Sleep(TimeSpan::FromSeconds(1));
    cout << ReadTimer() << endl;

    return 0;
}
