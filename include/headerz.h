#pragma once

/* You may need to change this to pdcurses.h if you're running windows */
#include <ncurses.h>
#include <setjmp.h>
#include <stddef.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <time.h>
#define SLEEP(ms)                                                              \
    do                                                                         \
    {                                                                          \
        struct timespec _ts;                                                   \
        long long _ns = (long long)ms * 1000000;                               \
        _ts.tv_sec = _ns / 1000000000;                                         \
        _ts.tv_nsec = _ns % 1000000000;                                        \
        nanosleep(&_ts, NULL);                                                 \
    } while (0)
#endif // cool cross-platform SLEEP macro

extern jmp_buf env;

typedef enum
{
    ERRORCODE_IGNORE = OK,
    ERRORCODE_DEFAULT,
    ERRORCODE_WINDOW,       // Called when the window goes out of bounds
    ERRORCODE_INIT,         // Called when ncurses cannot start
} ErrorCode;

typedef struct
{
    int x;
    int y;
} Point;

typedef struct
{
    Point size;
    char **board;
} Canvas;
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
    char **sprites;
} GameObj;

// distance = √((x2 - x1)^2 + (y2 - y1)^2)
double point_dist(Point p1, Point p2);
double dot_product(Point p1, Point p2);

GameObj *new_gameobj(Point pos, Point size, char *sprites[]);
Point obj_find_size(const GameObj *obj); // todo

Canvas *new_canvas(Point size);
char canvas_getch(const Canvas *canvas, Point index);
void canvas_setch(Canvas *canvas, char val, Point index);

void canvas_erase(Canvas *canvas);
void obj_update(Canvas *canvas, const GameObj *obj, size_t sprite_index);