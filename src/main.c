#include "headerz.h"
#include "miniaudio.h"
#include <stdio.h>

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
                                  "<[_ _]>\n"
                                  "  W W  ";
    constexpr char spaceship2[] = "   A   \n"
                                  "  / \\  \n"
                                  "<{_ _}>\n"
                                  "  v v  ";
    constexpr Point target_size = {80, 24};
    Point max_size;
    getmaxyx(stdscr, max_size.y, max_size.x);

    WINDOW *win = newwin(target_size.y, target_size.x, 0, 0);
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
        if (target_size.x > max_size.x || target_size.y > max_size.y)
        {
            endwin();
            fprintf(stderr, "Window is too small (%dx%d), at least %dx%d\n",
                    max_size.x, max_size.y, target_size.x, target_size.y);
            return 1;
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
            endwin();
            fprintf(stderr, "CRIKEY, PROCESS EXITED WITH EXIT CODE %d\n",
                    WATCH);
            return WATCH;
        }
    }
    endwin();
    return 0;
}