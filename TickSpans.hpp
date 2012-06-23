#ifndef TICKSPANS_HPP
#define TICKSPANS_HPP

const int64_t NanosecondsPerTick = 100;
const int64_t TicksPerMicrosecond = 10;
const int64_t TicksPerMillisecond = TicksPerMicrosecond * 1000;
const int64_t TicksPerSecond = TicksPerMillisecond * 1000;
const int64_t TicksPerMinute = TicksPerSecond * 60;
const int64_t TicksPerHour = TicksPerMinute * 60;
const int64_t TicksPerDay = TicksPerHour * 24;
const int64_t TicksPerWeek = TicksPerDay * 7;

#endif
