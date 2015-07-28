#include "DateTime.hpp"
#include <ctime>

static constexpr auto Clock =
#ifdef CLOCK_MONOTONIC_RAW
    CLOCK_MONOTONIC_RAW
#elif defined(CLOCK_MONOTONIC)
    CLOCK_MONOTONIC
#else
#error No valid UNIX clock defined!
#endif
    ;

const DateTime GetNativeTime()
{
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    return
        DateTime(1970, 1, 1) +
        TimeSpan::FromSeconds(ts.tv_sec) +
        TimeSpan::FromNanoseconds(ts.tv_nsec);
}

static TimeSpan timerBase;

const TimeSpan RawTimer()
{
    timespec ts;
    clock_gettime(Clock, &ts);

    return
        TimeSpan::FromSeconds(ts.tv_sec) +
        TimeSpan::FromNanoseconds(ts.tv_nsec);
}

void ResetTimer()
{
    timerBase = RawTimer();
}

const TimeSpan ReadTimer()
{
    return RawTimer() - timerBase;
}
