/* File Path: basics/hello_world.c */
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{       

    int exitCode;
    FILE *fp;
    int goto_prev = FALSE , y, x;

    char msg[] = "Hello World !!!";
    int i,j;
    char str[88];

    initscr();                      /* Start curses mode              */
    if(has_colors() == FALSE){
        endwin();
        printf("you terminal sucks");
        exit(1);
    }
    raw();                          //diable line buffering
    keypad(stdscr, TRUE);
    noecho();

    init_pair(1, COLOR_RED, COLOR_BLACK);
    printw("Kill me");
    mvchgat(0, 0, -1, A_BLINK, 1, NULL);

    getmaxyx(stdscr, i, j);
    
    attron(COLOR_PAIR(1));
    mvprintw(i/2., (j - strlen(msg))/2., "%s", msg);
    mvprintw(i - 2., 0., "the no.rows and columns in this windowa are %d, %d\n",i, j);
    attroff(COLOR_PAIR(1));

    getstr(str);
    mvprintw(23, 0, "You entered %s\n", str);

    printw("press any key to exit \n");

    exitCode = getch();

    refresh();                      /* Print it on to the real screen */ 

    endwin();                       /* End curses mode                */

    return 0;
}
