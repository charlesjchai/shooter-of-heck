#include "headerz.h"
#include "miniaudio.h"
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

jmp_buf exception_buffer;

int main(void)
{
    constexpr Point canvas_size = {80, 24};

    int status = setjmp(exception_buffer);
    if (status != 0)
    {
        endwin();
        switch (status)
        {
        case ERRORCODE_WINDOW_ERR:
            int y, x;
            getmaxyx(stdscr, y, x);
            fprintf(stderr, "Window is too small (%dx%d), at least %dx%d\n",
                    x, y, canvas_size.x, canvas_size.y);
            break;

        default:
            fprintf(stderr, "CRIKEY, PROCESS EXITED WITH EXIT CODE %d\n",
                    status);
            break;
        }
        
        return 1;
    }

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    constexpr char spaceship1[] = "   A   \n"
                                  "  / \\  \n"
                                  "<[_ _]>\n"
                                  "  W W  ";
    constexpr char spaceship2[] = "   A   \n"
                                  "  / \\  \n"
                                  "<{_ _}>\n"
                                  "  v v  ";

    // 2d array "canvas" that is modified and rendered
    char **canvas = calloc(canvas_size.x, sizeof(int *));
    for (int i = 0; i < canvas_size.x; i++)
    {
        canvas[i] = calloc(canvas_size.y, sizeof(int));
    }

    Point max_size; // Current size of terminal window
    getmaxyx(stdscr, max_size.y, max_size.x);

    WINDOW *win = newwin(canvas_size.y, canvas_size.x, 0, 0);
    if (win == NULL)
    {
        endwin();
        perror("Error initializing window\n");
        return 1;
    }

    int WATCH = OK;
    int ch;

    while ((ch = getch()) != 'q')
    {
        if (ch == KEY_RESIZE)
        {
            getmaxyx(stdscr, max_size.y, max_size.x);
        }
        if (canvas_size.x > max_size.x || canvas_size.y > max_size.y)
        {
            /*endwin();
            fprintf(stderr, "Window is too small (%dx%d), at least %dx%d\n",
                    max_size.x, max_size.y, canvas_size.x, canvas_size.y);
            return 1;*/
            longjmp(exception_buffer, ERRORCODE_WINDOW_ERR);
        }

        erase();
        printw("%s", spaceship1);
        refresh();
        SLEEP(100);
        erase();
        printw("%s", spaceship2);
        refresh();
        SLEEP(100);

        if (WATCH != OK)
        {
            longjmp(exception_buffer, WATCH);
        }
    }
    endwin();
    return 0;
}