#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
#define WIDTH 90
#define HEIGHT 55

void init_game();
//void draw_hello(char* hello_frase, int len_hello_frase);
void print_frame(int grid[HEIGHT][WIDTH]);
void fill_with_random(int grid[HEIGHT][WIDTH]);
int game_logic(int grid[HEIGHT][WIDTH], int grid1[HEIGHT][WIDTH]);
int count(int grid[HEIGHT][WIDTH], int i, int j);
void refresh_grid(int grid[HEIGHT][WIDTH], int grid1[HEIGHT][WIDTH]);
void draw_menu(char* hello_frase, int len_hello_frase, int* option);
int main() {
    initscr();
    init_game();
    refresh();
    endwin();
    return 0;
}

/* This function creates grids, current grid and future grid. The current
one is filled according to the selected option in the menu. Either 
randomly or as set with the cursor. Then there is an evolution process 
inside the loop waiting for q to exit. */

void init_game() {
    int grid[HEIGHT][WIDTH];
    int grid1[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid1[i][j] = 0;
        }
    }

    
    char* hello_frase = "GAME OF LIFE";
    int len_hello_frase = strlen(hello_frase);
    //draw_hello(hello_frase, len_hello_frase);
    int option = 1;
    draw_menu(hello_frase, len_hello_frase, &option);
    char keyboard_command;
    int generation = 0;

    fill_with_random(grid);
    while ((keyboard_command = getch()) != 'q') {
        clear();
        if (generation == 0) {
            print_frame(grid);
        } else {
            game_logic(grid, grid1);
            refresh_grid(grid, grid1);
            print_frame(grid);
            
        }
        generation++;
        printw("FRAME: %d", generation);
    }
}

/* In this function, the neighbors are counted using the count function 
and, depending on whether the current cell is alive or dead, conclusions 
about its future are drawn. */

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

/* Initial screen */

// void draw_hello(char* hello_frase, int len_hello_frase) {
//     char* press_any = "press any key to start or <q> for escape";
//     int len_press_any = strlen(press_any);
//     for (int i = 0; i < HEIGHT; i++) {
//         for (int j = 0; j < WIDTH; j++) {
//             if (i == HEIGHT / 2 && j == (WIDTH - len_hello_frase) / 2) {
//                 printw("%s", hello_frase);
//                 j = j + len_hello_frase - 1;
//             } else if (i == HEIGHT / 2 + 3 && j == (WIDTH - len_press_any) / 2) {
//                 printw("%s", press_any);
//                 j = j + len_press_any - 1;
//             } else {
//                 printw(" ");
//             }
//         }
//         printw("\n");
//     }
// }

void draw_menu(char* hello_frase, int len_hello_frase, int* option) {
    int star = 0;
    if (*option == 1) {
        star = HEIGHT / 2 + 3;
    } else {
        star =  HEIGHT / 2 + 5;
    }
    char* option1 = "random game";
    char* option2 = "set new game";
    int len_option1 = strlen(option1);
    int len_option2 = strlen(option2);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == HEIGHT / 2 && j == (WIDTH - len_hello_frase) / 2) {
                printw("%s", hello_frase);
                j = j + len_hello_frase - 1;
            } else if (i == HEIGHT / 2 + 3 && j == (WIDTH - len_option1) / 2) {
                printw("%s", option1);
                j = j + len_option1 - 1;
            } else if (i == HEIGHT / 2 + 5 && j == (WIDTH - len_option2) / 2) {
                printw("%s", option2);
                j = j + len_option2 - 1;
            } else if (*option == 1 && i == star && j == (WIDTH - len_option1) / 2 - 1) {
                printw("*%s",option1);
                j = j + len_option1;
            } else if (*option == 2 && i == star && j == (WIDTH - len_option2) / 2 - 1) {
                printw("*%s", option2);
                j = j + len_option2;
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

void refresh_grid(int grid[HEIGHT][WIDTH], int grid1[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = grid1[i][j];
        }
    }
}
