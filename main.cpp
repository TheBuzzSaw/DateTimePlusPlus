#include "DateTime.hpp"

#include <iostream>
using namespace std;

DateTime GetNativeTime();

int main(int argc, char** argv)
{
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

    return 0;
}
