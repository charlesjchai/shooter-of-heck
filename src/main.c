#include "curses.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <time.h>
#define SLEEP(ms)                                                              \
    do                                                                         \
    {                                                                          \
        struct timespec ts;                                                    \
        long long ns = (long long)ms * 1000000;                                \
        ts.tv_sec = ns / 1000000000;                                           \
        ts.tv_nsec = ns % 1000000000;                                          \
        nanosleep(&ts, NULL);                                                  \
    } while (0)
#endif

int main(void)
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    constexpr char spaceship1[] = "   A   \n"
                                  "  / \\  \n"
                                  "<{_ _}>\n"
                                  "  W W  ";
    constexpr char spaceship2[] = "   A   \n"
                                  "  / \\  \n"
                                  "<{_ _}>\n"
                                  "  v v  ";int hi;
    while ((hi = getch()) != 'q')
    {
        erase();
        printw("%s", spaceship1);
        refresh();
        SLEEP(100);
        erase();
        printw("%s", spaceship2);
        refresh();
        SLEEP(100);
    }
    endwin();
    return 0;
}