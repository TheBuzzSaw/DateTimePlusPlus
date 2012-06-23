DateTimePlusPlus
================

This is a small C++ library designed to mimic the behavior of System.DateTime
and System.TimeSpan from C#. It is not meant to be a precise port. Rather, the
only standard is that the classes make use of the same 64-bit signed integer
'ticks' value (representing 100-nanosecond intervals since January 1, 0001).

Requirements
------------

The project files are for the Code::Blocks IDE. See http://www.codeblocks.org/
for more information. If you want to submit other build files, submit a patch!

The DateTime and TimeSpan classes are completely self-contained and portable.
They should work as is across any compiler or platform. (If they don't, submit
a patch!)

On the side, there is some native code for obtaining high resolution timestamps.
The Windows code makes use of the standard Win32 API. The UNIX code makes use
of `clock_gettime` from `time.h`.

License
-------

All of this code is in the **public domain**. Use it for whatever you like. It
is strictly research for me in making good, clean time-related tools.

If you have a contribution, submit a pull request! All I ask is that you allow
your contributions into the public domain as I have done. Aside from that, I
just want to make these tools better and better.
