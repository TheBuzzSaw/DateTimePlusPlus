#include "DateTime.hpp"

#include <iostream>
using namespace std;

void Sleep(TimeSpan timeSpan);
const DateTime GetNativeTime();
void ResetTimer();
const TimeSpan ReadTimer();

int main(int argc, char** argv)
{
    cout << "size: " << sizeof(DateTime) << endl;
    cout << "Max: " << TimeSpan::MaxValue.Ticks() << endl;
    cout << "Min: " << TimeSpan::MinValue.Ticks() << endl;

    DateTime a = DateTime::LocalTime();
    DateTime b = a.Date();

    TimeSpan gap = a - b;

    cout << gap << endl;

    a += TimeSpan::FromMinutes(5);

    int day = a.DayOfWeek();
    cout << DateTime::DayToString(day) << endl;
    cout << "5 minutes from now: " << a << endl;
    cout << "today with date only: " << a.Date() << endl;
    cout << "standard UTC time: " << DateTime::UtcTime() << endl;
    cout << "native UTC time: " << GetNativeTime() << endl;

    a = DateTime(2012, 12, 31);
    cout << "Dec 31, yes? " << a << endl;
    cout << a.Ticks() << endl;

    ResetTimer();
    Sleep(TimeSpan::FromSeconds(2));
    cout << ReadTimer() << endl;

    return 0;
}
