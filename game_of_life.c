#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#define WIDTH 80
#define HEIGHT 25

void init_game();
void draw_hello();
void print_frame(int grid[HEIGHT][WIDTH]);
void fill_with_random(int grid[HEIGHT][WIDTH]);
int neighbours(int previous_frame[HEIGHT][WIDTH], int i, int j);
void game_logic(int previous_frame[HEIGHT][WIDTH], int second_frame[HEIGHT][WIDTH]);

int main() {
    initscr();
    init_game();
    refresh();
    endwin();
    return 0;
}

void init_game() {
    // int size = sizeof(int*) * HEIGHT + sizeof(int) * HEIGHT * WIDTH;
    // int **grid = (int**)malloc(size);

    // //int* first_element = (int*)(grid + HEIGHT);
 
    int grid[HEIGHT][WIDTH];
    int grid1[HEIGHT][WIDTH];
    fill_with_random(grid);
    char* hello_frase = "GAME OF LIFE";
    int len_hello_frase = strlen(hello_frase);
    draw_hello(hello_frase, len_hello_frase);
    char keyboard_command;
    int generation = 0;
    while ((keyboard_command = getch()) != 'q') {
        clear();
        if ((keyboard_command = getch()) == 'd') {
            game_logic(grid, grid1);
            printw("generation %d", generation);
            print_frame(grid1);
        } else {
            print_frame(grid);
        }
        
    }
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
            printw("%d", grid[i][j]);
        }
        printw("\n");
    }
}

void fill_with_random(int grid[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = rand() % 2;
        }
    }
}

void game_logic(int previous_frame[HEIGHT][WIDTH], int second_frame[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (previous_frame[i][j] == 0) {
                switch (neighbours(previous_frame, i, j)) {
                    case 3:
                        second_frame[i][j] = 0;
                        break;
                    default:
                        second_frame[i][j] = 0;
                        break;
                }    

            }
        }
    }
}

int neighbours(int previous_frame[HEIGHT][WIDTH], int i, int j) {
    int count = 0;
    for (int a = -1; a < 2; a++) {
        for (int b = -1; b < 2; b++) {
            if (previous_frame[i + a][j + a] == 1) {
                count++;
            }    
        }
    }
    if (previous_frame[i][j] == 1) {
        printw("count %d\n", count);
        return count - 1;
    }
    return count;
}
