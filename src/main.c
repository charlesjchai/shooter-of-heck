#include "headerz.h"
#include "miniaudio.h"
#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

jmp_buf env;

int main(void)
{
    constexpr Point canvas_size = {80, 24};
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

    int status = setjmp(env);
    if (status != 0)
    { // Uh oh, handle exceptions!
        endwin();
        switch (status)
        {
        case ERRORCODE_INIT:
            perror(
                "Failed to initialize window, possibly due to terminal size");
            break;

        case ERRORCODE_WINDOW:
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
    //nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);timeout(33);

    GameObj *player_ship = new_gameobj((Point){0, 19}, (Point){7, 4},
                                       (char *[]){"   A   \n"
                                                  "  / \\  \n"
                                                  "<[_ _]>\n"
                                                  "  W W  ",
                                                  "   A   \n"
                                                  "  / \\  \n"
                                                  "<{_ _}>\n"
                                                  "  v v  "});

    // 2d array "canvas" that is modified and rendered
    Canvas *canvas = new_canvas(canvas_size);

    Point term_size; // Current size of terminal window
    getmaxyx(stdscr, term_size.y, term_size.x);
    
    if (canvas_size.x > term_size.x || canvas_size.y > term_size.y)
        longjmp(env, ERRORCODE_WINDOW);

    WINDOW *win =
        newwin(canvas_size.y, canvas_size.x, /*(term_size.y - canvas_size.y) / 2*/0,
               (term_size.x - canvas_size.x) / 2);
    if (win == nullptr)
        longjmp(env, ERRORCODE_INIT);

    uint64_t counter = 4;
    int WATCH = OK;
    int ch;

    while ((ch = getch()) != 'q')
    {
        if (canvas_size.x > term_size.x || canvas_size.y > term_size.y)
        {
            longjmp(env, ERRORCODE_WINDOW);
        }
        if (ch == KEY_RESIZE)
        {
            getmaxyx(stdscr, term_size.y, term_size.x);

            WATCH = mvwin(win, /*(term_size.y - canvas_size.y) / 2*/0,
                          (term_size.x - canvas_size.x) / 2) == 0
                        ? 0
                        : ERRORCODE_WINDOW;
            touchwin(stdscr);
            fprintf(stderr, "%dx%d %dx%d\n", term_size.x, term_size.y,
                    canvas_size.x, canvas_size.y);
        }
        if (ch == KEY_LEFT)
            player_ship->pos.x--;
        if (ch == KEY_RIGHT)
            player_ship->pos.x++;
        if (ch == KEY_UP)
            player_ship->pos.y--;
        if (ch == KEY_DOWN)
            player_ship->pos.y++;
        canvas_erase(canvas);
        werase(win);
        obj_update(canvas, player_ship, counter / 2 % 2 == 0 ? 0 : 1);
        for (int i = 0; i < 24; i++)
        {
            for (int j = 0; j < 80; j++)
            {
                Point index = {j, i};
                wprintw(win, "%c",
                        canvas_getch(canvas, index) == 0
                            ? '.'
                            : canvas_getch(canvas, index));
            }
        }
        wnoutrefresh(stdscr);
        wnoutrefresh(win);
        doupdate();

        counter++;
        if (WATCH != OK)
            longjmp(env, WATCH);
        //SLEEP(33);
    }
    endwin();
    return 0;
}