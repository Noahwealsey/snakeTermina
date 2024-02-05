#include <panel.h>

#define NLINES 40
#define NCOLS 20

typedef struct{
    bool resized, moved;
    int x, y, w, h;
    char label[256];
    int label_color;
    PANEL *next;
}PANEL_DATA;

void init_wins(WINDOW **mywin , int count){
	int x, y, i;
	char label[100];
	y = 6;
	x =10;
	for (int i = 0; i < count; i++)
	{
		mywin[i] = newiwn(NLINES, NCOLS, y, x);
		sprintf(label, "window no. is %d", i + 1);
		y = y + 3;
		x = x + 7;
	}
}



int main()
{	WINDOW *my_wins[3];
	WINDOW *old_win, *new_wins;
	PANEL  *my_panels[3];
	PANEL_DATA *top, *stack_top;
	char label[200];
	int newx, newy, newh, neww;
	int lines = 10, cols = 40, y = 2, x = 4, i;
    int ch; 

	initscr();
    start_color();
	cbreak();
	noecho();
    keypad(stdscr, TRUE);

	/* Create windows for the panels */
	my_wins[0] = newwin(lines, cols, y, x);
	my_wins[1] = newwin(lines, cols, y + 1  , x + 5);
	my_wins[2] = newwin(lines, cols, y + 2, x + 10);

    init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	
	init_wins(my_wins, 3);

	my_panels[0] = new_panel(my_wins[0]); 	/* Push 0, order: stdscr-0 */
	my_panels[1] = new_panel(my_wins[1]); 	/* Push 1, order: stdscr-0-1 */
	my_panels[2] = new_panel(my_wins[2]); 	/* Push 2, order: stdscr-0-1-2 */

    set_panel_userptr(my_panels[0], my_panels[1]);
    set_panel_userptr(my_panels[1], my_panels[2]);
    set_panel_userptr(my_panels[2], my_panels[0]);

	update_panels();

    attron(COLOR_PAIR(4));
    mvprintw(LINES - 2, 0, "use tab to browsse through panels");
    mvprintw(LINES - 3, 0, "Press m to move the panels");
    attroff(COLOR_PAIR(4));
	/* Show it on the screen */
	refresh();
	
	stack_top =  my_panels[2];
	top  =  (PANEL_DATA*)panel_userptr(stack_top);
	newx = top->x;
	newy = top->y;
	newh = top->h;
	neww = top->w;

	while((ch = getch()) != KEY_BACKSPACE)
	{
		switch(ch)
		{
			case 9:
				top = (PANEL_DATA*)panel_userptr(stack_top);
				top_panel(top->next);
				stack_top = top->next;
				top = (PANEL_DATA*)panel_userptr(stack_top);
				newx = top->x;
				newy = top->y;
				newh = top->h;
				neww = top->w;
				break;
			
			case 'r':
				if(top->moved)
					top->moved = false;
				top->resized = true;
				attron(COLOR_PAIR(4));
			    mvprintw(LINES - 3, 0, "Press r to resize the panels");
				refresh();
				attroff(COLOR_PAIR(4));
				break;

			case 'm':
				if(top->resized)
					top->resized = false;
				top->moved = true;
				attron(COLOR_PAIR(4));
			    mvprintw(LINES - 3, 0, "Press m to move the panels");
				refresh();
				attroff(COLOR_PAIR(4));
				break;

			case KEY_RIGHT:
				if(top->resized){
					newx++;
					neww--;
				}
				if(top->moved){
					newx++;
				}
			case KEY_LEFT:
				if(top->resized){
					newx--;
					neww++;
				}
				if(top->moved){
					newx--;
				}

			case KEY_UP:
				if(top->resized){
					newy++;
					newh--;
				}
				if(top->moved){
					newy++;
				}
			case KEY_DOWN:
				if(top->resized){
					newy--;
					newh++;
				}
				if(top->moved){
					newy--;
				}
			
			case 10:
				move(LINES - 4, 0);
				clrtoeol();
				refresh();
				if(top->resized){
					old_win = panel_window(new_panel);

					attron(COLOR_PAIR(4));
					mvprintw(LINES - 4, 0, "RESIZING WAS SUCCESSFUL");
					attroff(COLOR_PAIR(4));
					top->resized = false;

				}
				if(top->moved){
					attron(COLOR_PAIR(4));
					mvprintw(LINES - 4, 0, "MOVED WAS SUCCESSFULY");
					attroff(COLOR_PAIR(4));
					top->moved = false;

				}

		}
		update_panels();
		doupdate();
	}
	endwin();
	return 0;
}