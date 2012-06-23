#include "DateTime.hpp"

#include <iostream>
using namespace std;

void Sleep(TimeSpan inTimeSpan);
DateTime GetNativeTime();
TimeSpan RawTimer();
void ResetTimer();
TimeSpan ReadTimer();

int main(int argc, char** argv)
{
    ResetTimer();
    cout << "size: " << sizeof(DateTime) << endl;

    DateTime a = DateTime::Now();
    DateTime b = a;
    b.SetTimeToMidnight();

    TimeSpan gap = a - b;

    cout << gap << endl;

    a += TimeSpan::Minutes(5);

    int day = a.DayOfWeek();
    cout << DateTime::DayToString(day) << endl;
    cout << a << endl;
    cout << GetNativeTime() << endl;

    Sleep(TimeSpan::Seconds(1));
    cout << ReadTimer() << endl;

    return 0;
}
