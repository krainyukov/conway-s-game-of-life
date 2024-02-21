#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
#define WIDTH 190
#define HEIGHT 55

void init_game();
void draw_hello();
void print_frame(int grid[HEIGHT][WIDTH]);
void fill_with_random(int grid[HEIGHT][WIDTH]);
int game_logic(int grid[HEIGHT][WIDTH], int grid1[HEIGHT][WIDTH]);
int count(int grid[HEIGHT][WIDTH], int i, int j);

int main() {
    initscr();
    init_game();
    refresh();
    endwin();
    return 0;
}

void init_game() {
    // int size = sizeof(int*) * HEIGHT + sizeof(int) * HEIGHT * WIDTH;
    // int **grid1 = (int**)malloc(size);
    // int* first_element = (int*)(grid1 + HEIGHT);
    int grid[HEIGHT][WIDTH];
    int grid1[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid1[i][j] = 0;
        }
    }
    fill_with_random(grid);
    char* hello_frase = "GAME OF LIFE";
    int len_hello_frase = strlen(hello_frase);
    draw_hello(hello_frase, len_hello_frase);
    char keyboard_command;
    int generation = 0;
    while ((keyboard_command = getch()) != 'q') {
        clear();
        if (generation == 0) {
            print_frame(grid);
        } else {
            game_logic(grid, grid1);
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    grid[i][j] = grid1[i][j];
                }
            }
            print_frame(grid);
            
        }
        generation++;
        printw("%d", generation);
    }
}

int game_logic(int grid[HEIGHT][WIDTH], int grid1[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j] == 0) {
                switch (count(grid, i, j)) {
                case 3:
                    grid1[i][j] = 1;
                    break;
                default:
                    grid1[i][j] = 0;
                    break;
                }
            } else {
                switch (count(grid, i, j)) {
                case 2:
                    grid1[i][j] = 1;
                    break;
                case 3:
                    grid1[i][j] = 1;
                    break;
                default:
                    grid1[i][j] = 0;
                    break;
                }
            }
        }
    }
    return 1;
}

int count(int grid[HEIGHT][WIDTH], int i, int j) {
    int count = 0;
    for (int a = -1; a < 2; a++) {
        for (int s = -1; s < 2; s++) {
            if (grid[(i + a) % HEIGHT][(j + s) % WIDTH] == 1) count++;
        }
    }
    if (grid[i][j] == 1) count--;
    return count;
}

void draw_hello(char* hello_frase, int len_hello_frase) {
    char* press_any = "press any key to start or <q> for escape";
    int len_press_any = strlen(press_any);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == HEIGHT / 2 && j == (WIDTH - len_hello_frase) / 2) {
                printw("%s", hello_frase);
                j = j + len_hello_frase - 1;
            } else if (i == HEIGHT / 2 + 3 && j == (WIDTH - len_press_any) / 2) {
                printw("%s", press_any);
                j = j + len_press_any - 1;
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }
}

void print_frame(int grid[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j] == 0) {
                printw(" ");
            } else {
                printw("o");
            }
        }
        printw("\n");
    }
}

void fill_with_random(int grid[HEIGHT][WIDTH]) {
    srand(time(0));
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = (rand()) % 2;
        }
    }
}

