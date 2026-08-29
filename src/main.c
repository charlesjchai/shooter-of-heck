#include "headerz.h"
#include "miniaudio.h"
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

jmp_buf env;

int main(void)
{
    /*char **canvass = calloc(80, sizeof(int *));
    for (int i = 0; i < 80; i++)
    {
        canvass[i] = calloc(24, sizeof(int));
    }canvass[0][1] = 'a';
    obj_update(canvass, (Point){80, 24}, (GameObj){.pos = (Point){77, 20},
    .size = (Point){5, 5}, .sprites[0] = "XOXOX\nOXOXO\nXOXOX\nOXOXO\nXOXOX"},
    0); for (int i = 0; i < 24; i++) { for (int j = 0; j < 80; j++) { printf("%c
    ", canvass[j][i] == 0 ? '.' : canvass[j][i]);
        }
        puts("\n");
    }
    SLEEP(4000);*/
    constexpr Point canvas_size = {80, 24};

    int status = setjmp(env);
    if (status != 0)
    { // Uh oh, handle exceptions!
        endwin();
        switch (status)
        {
        case ERRORCODE_WINDOW_ERR:
            int y, x;
            getmaxyx(stdscr, y, x);
            fprintf(stderr, "Window is too small (%dx%d), at least %dx%d\n", x,
                    y, canvas_size.x, canvas_size.y);
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

    GameObj player_ship = {.pos = (Point){0, 0},
                           .size = (Point){7, 4},
                           .sprites = { "   A   \n"
                                            "  / \\  \n"
                                            "<[_ _]>\n"
                                            "  W W  "}};

    // 2d array "canvas" that is modified and rendered
    char **canvas = calloc(canvas_size.x, sizeof(int *));
    for (int i = 0; i < canvas_size.x; i++)
    {
        canvas[i] = calloc(canvas_size.y, sizeof(int));
    }

    Point max_size; // Current size of terminal window
    getmaxyx(stdscr, max_size.y, max_size.x);
    
    WINDOW *win = newwin(canvas_size.y, canvas_size.x, 0, 0);
    box(win, 0, 0);
    wrefresh(win);
    refresh();
    if (win == nullptr)
        longjmp(env, ERRORCODE_INIT_ERR);

    int WATCH = OK;
    int ch;

    while ((ch = getch()) != 'q')
    {
        if (canvas_size.x > max_size.x || canvas_size.y > max_size.y)
        {
            /*endwin();
            fprintf(stderr, "Window is too small (%dx%d), at least %dx%d\n",
                    max_size.x, max_size.y, canvas_size.x, canvas_size.y);
            return 1;*/
            longjmp(env, ERRORCODE_WINDOW_ERR);
        }
        if (ch == KEY_RESIZE)
        {
            getmaxyx(stdscr, max_size.y, max_size.x);
        }

        // werase(win);

        wrefresh(win);
        SLEEP(1000);

        if (WATCH != OK)
            longjmp(env, WATCH);
    }
    endwin();
    return 0;
}