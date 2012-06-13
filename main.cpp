#include "DateTime.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    DateTime dt;
    dt.Set(2012, 6, 13, 15, 0, 0);
    dt = DateTime::Now();
    //dt.RemoveTime();

    int day = dt.DayOfWeek();

    cout << DateTime::DayToString(day) << endl;
    cout << dt.Year() << "-" << dt.Month() << "-" << dt.Day() << endl;
    cout << dt.Hour() << ":" << dt.Minute() << ":" << dt.Second() << endl;

    return 0;
}
