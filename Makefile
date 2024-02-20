all:
	gcc -Wall -Werror -Wextra -g -o game game_of_life.c -lncurses