#include "Stopwatch.hpp"

Stopwatch::Stopwatch() : _isRunning(false)
{
}

Stopwatch::~Stopwatch()
{
}

const TimeSpan Stopwatch::Elapsed() const
{
    TimeSpan elapsed = _elapsed;

    if (_isRunning)
        elapsed += ReadTimer() - _start;

    return elapsed;
}

void Stopwatch::Start()
{
    if (!_isRunning)
    {
        _isRunning = true;
        _start = ReadTimer();
    }
}

void Stopwatch::Stop()
{
    if (_isRunning)
    {
        _isRunning = false;
        _elapsed += ReadTimer() - _start;
    }
}

void Stopwatch::Reset()
{
    _elapsed = TimeSpan();

    if (_isRunning)
        _start = ReadTimer();
}
