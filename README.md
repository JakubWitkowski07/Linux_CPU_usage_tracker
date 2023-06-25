CPU USAGE TRACKER
Scope of application is calculating cpu and every core of cpu usage and show results every second.
Application uses multithreading and includes threads which are responsible for reading needed data
from /proc/stat file, calculating data and printing it in console. App includes watchdog thread too
which allows to check if other threads are working and if something hangs, app is closing with relevant
comment written into logs and console.

USAGE:
Application can be compiled with GCC and CLANG.
To compile and run with CLANG:
1) Go to appropriate directory by using console
2) Run 'make CCNAME=clang' command
3) Run './CUT' command

To compile and run with GCC:
1) Go to appropriate directory by using console
2) Run 'make' command
3) Run './CUT' command

Closing is done with using SIGINT or SIGTERM signal.
To close with SIGINT use 'Ctrl+C'.

ADDITIONAL INFO:
For compilation with CLANG there are added flags:
"-Wno-padded -Wno-disabled-macro-expansion -Wno-missing-field-initializers"
because of warnings which appear during compilation and not exit during compilation with GCC.
Causes of the warnings do not affect the correct operation of the application.