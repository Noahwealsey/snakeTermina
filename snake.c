#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define COLS 200
#define LINES 200

typedef struct {
    int x;
    int y;
} vector2d;

int hash() {
    return rand() % 20;
}

vector2d output(vector2d input) {
    input.x = hash();
    input.y = hash();
    return input;
}

int main() {
    WINDOW *win = initscr();
    keypad(win, true);
    nodelay(win, true);
    cbreak();
    noecho();
    curs_set(0);  // Hide the cursor

    int score = 0;

    vector2d food = {2, 4};
    vector2d dir = {0, 0};
    vector2d pos = {1, 1};
    vector2d tail[100];

    int len = 1;

    while (true) {
        int pressed = wgetch(win);
        switch (pressed) {
            case KEY_RIGHT:
                dir.x = 1;
                dir.y = 0;
                break;
            case KEY_LEFT:
                dir.x = -1;
                dir.y = 0;
                break;
            case KEY_UP:
                dir.y = -1;
                dir.x = 0;
                break;
            case KEY_DOWN:
                dir.y = 1;
                dir.x = 0;
                break;
        }

        // Update tail positions
        for (int i = len - 1; i > 0; i--) {
            tail[i] = tail[i - 1];
        }
        tail[0] = pos;  // Assign the current position to the first element of the tail array

        pos.x += dir.x;
        pos.y += dir.y;

        erase();

        // Draw tail
        for (int i = 0; i < len; i++) {
            mvaddch(tail[i].y, tail[i].x, '*');
        }

        mvaddch(pos.y, pos.x, '*');
        mvaddch(food.y, food.x, '0');

        if (pos.x == food.x && pos.y == food.y) {
            score++;
            food = output(food);
            len++;  // Increase the length of the snake

            // Ensure food spawns within the visible screen area
            if (food.x <= 0 || food.y <= 0 || food.x >= COLS - 1 || food.y >= LINES - 1) {
                food = output(food);
            }
        }

        mvprintw(0, 0, "Score: %d", score);
        refresh();
        usleep(100000);
    }

    endwin();
    return 0;
}
