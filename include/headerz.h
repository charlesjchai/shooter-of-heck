#pragma once

/* You may need to change this to pdcurses.h if you're running windows */
#include <ncurses.h>
#include <stddef.h>

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
    ERRORCODE_INIT_ERR,
} ErrorCode;

typedef struct
{
    int x;
    int y;
} Point;
typedef struct
{
    Point pos; // pos is the top left corner of the object
    Point size;

    /* List of strings (sprites)
       ex. "   A   \n"
           "  / \\  \n"
           "<[_ _]>\n"
           "  W W  "
        size = {7, 4}
       NOTE: Sprites should have a newline on the right, except for the last
       line */
    char *sprites[5];
} GameObj;

// distance = √((x2 - x1)^2 + (y2 - y1)^2)
double point_dist(Point p1, Point p2);
double dot_product(Point p1, Point p2);

Point obj_find_size(GameObj obj); // todo

void obj_update(char **canvas, Point canvas_size, GameObj obj,
                size_t sprite_index);