#include "DateTime.hpp"
#include <ctime>

DateTime GetNativeTime()
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    int64_t ticks = ts.tv_nsec / NanosecondsPerTick;
    ticks += ts.tv_sec * TicksPerSecond;

    DateTime epoch;
    epoch.Set(1970, 1, 1);

    return epoch + TimeSpan(ticks);
}
