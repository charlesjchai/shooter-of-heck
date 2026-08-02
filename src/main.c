#include <stdio.h>
#include <ncurses.h>

void window_resize(WINDOW *win, int height, int width) {
    clear(); // clear previous layout
    refresh();

    mvwin(win, (LINES - height) / 2, (COLS - width) / 2);

    box(win, 0, 0);
    
    wrefresh(win);
}

int main(void) {
    // initializes and clears the screen
    initscr();
    cbreak(); // don't have to press enter key
    noecho(); // hides user input

    keypad(stdscr, TRUE); // detect KEY_RESIZE

    int width = 80;
    int height = 24;

    // sets the window in the middle of the screen
    WINDOW *win = newwin(height, width, LINES / 2 - height / 2, COLS / 2 - width / 2);
    
    refresh();
    box(win, 0, 0); // draws the
    wrefresh(win);

    int in;
    do {
        if (LINES < height || COLS < width) {
            delwin(win);
            endwin(); // crashes the program if it is resized too small
            fprintf(stderr, "YOUR WINDOW IS TOO SMALL, AT LEAST %d COLS AND %d LINES\n", width, height);
            return 1;
        }
        switch (in) {
            case KEY_RESIZE:
                window_resize(win, height, width);
                break;
        }
    } while ((in = getch()) != 'q');

    delwin(win);
    endwin();
    // ends ncurses

    return 0;
}
