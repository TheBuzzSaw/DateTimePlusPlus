#include "DateTime.hpp"
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    cout << "size: " << sizeof(DateTime) << endl;

    DateTime a = DateTime::Now();
    DateTime b = a;
    b.SetTimeToMidnight();

    TimeSpan gap = a - b;

    cout << gap.Hours() << " hours\n";
    cout << gap.Minutes() << " minutes\n";

    int day = a.DayOfWeek();

    cout << DateTime::DayToString(day) << endl;
    cout << a.Year() << "-" << a.Month() << "-" << a.Day() << endl;
    cout << a.Hour() << ":" << a.Minute() << ":" << a.Second() << ":"
        << a.Millisecond() << endl;

    DateTime c;
    c.Set();
    cout << c.Ticks() << endl;

    return 0;
}
