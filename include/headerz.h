#pragma once

/* You may need to change this to pdcurses.h if you're running windows */
#include <ncurses.h>

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
#endif // cool cross-platform SLEEP macro

typedef enum
{
    ERRORCODE_IGNORE = OK,
    ERRORCODE_WINDOW_ERR,
} ErrorCode;

typedef struct
{
    int x;
    int y;
} Point;
typedef struct
{
    Point pos; // pos is the center as well
    Point size;

    /* List of strings (sprites)
       ex.   A
            / \
          <{_ _}>
            W W     */
    char **sprites;
} GameObj;

// distance = √((x2 - x1)^2 + (y2 - y1)^2)
double point_dist(Point p1, Point p2);
double dot_product(Point p1, Point p2);
