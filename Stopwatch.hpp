#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include "TimeSpan.hpp"
#include "NativeTimers.hpp"

class Stopwatch
{
    public:
        Stopwatch();
        ~Stopwatch();

        inline const bool IsRunning() const { return _isRunning; }

        const TimeSpan Elapsed() const;

        void Start();
        void Stop();
        void Reset();

    protected:
    private:
        bool _isRunning;
        TimeSpan _elapsed;
        TimeSpan _start;
};

#endif
