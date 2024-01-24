CFLAGS = -Wall -Wextra -std=c11 -pedantic -ggdb

s: snake.c
	$(CC) $(CFLAGS) -o s snake.c -lncurses

t: test1.c
	$(CC) $(CFLAGS) -o t test1.c -lncurses
