#include <ncurses.h>
#include <stdio.h>

int main(void) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);



    endwin();
    return 0;
}
