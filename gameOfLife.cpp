#include <iostream>
#include <string>
#include <fstream>
#include <ncurses.h>
#include "gameOfLife.h"
#include "main.h"

const char ALIVE = 'X'; 
const char DEAD = '.';
char board[BOARD_Y][BOARD_X];
char update[BOARD_Y][BOARD_X];
string FILENAMES[] = { "explosion.txt", "glider_gun.txt", "spaceship.txt" } ;

bool load_file()  {
    int choice;
    ifstream loadFile;
    bool run = true;
    clear();
    while(run) {  
        mvprintw(5, 19, "Type the number of the initial state file");
        mvprintw(6, 17, "you'd like to load into Conway's Game of Life");
        mvprintw(8, 28, "0: Explosion State");
        mvprintw(9, 28, "1: Glider Gun State");
        mvprintw(10, 28, "2: Spaceship Battle State");
        refresh();
        switch (getch()) {
            case 48: 
                choice = 0;
                run = false;
                break;
            case 49:
                choice = 1;
                run = false;
                break;
            case 50:
                choice = 2;
                run = false;
                break;

            default:
                mvprintw(12, 28, "You didn't type an option");
                refresh();
                break;
        }
    }

    loadFile.open(FILENAMES[choice].c_str());
    if (!loadFile) return false; //File not found

    //Populate Board
    for (int y = 0; y < BOARD_Y; y++) {
        for (int x = 0; x < BOARD_X; x++) {
            loadFile >> board[y][x];
        }
    }
    loadFile.close();
    return true;
}

void start_simulation() {
    int roundCount = 0;
    clear();
    mvprintw(0, 0, "Press any key to start the simulation. ESC to quit...");
    refresh();
    while(getch() != 27){
        clear();
        //prints round
        for (int y = 0; y < BOARD_Y; y++) {
            for (int x = 0; x < BOARD_X; x++) {
                mvaddch(y, x, board[y][x]);
            }
        }
        roundCount++;
        update_round();
        mvprintw(BOARD_Y, 0, "Press any key to progress the rounds. ESC to quit.                 Round: %d", roundCount);
        refresh();
    }
    clear();
    menu();
    return;
}

/*
Rules of Life:
1. Living cells with fewer than 2 living neighbors die by underpopulation
2. Living cells wth 2 or 3 living neighbors continue to live
3. Living cells with more than 3 living neghbors die by overcrowding  
4. Dead cells with 3 living neighbors come alive by reproduction
*/

//May the odds be ever in your favor
void update_round() {
    //Initialize temp board
    char temp[BOARD_Y][BOARD_X];
    for (int y = 0; y < BOARD_Y; y++) {
        for (int x = 0; x < BOARD_X; x++) {
            temp[y][x] = DEAD;
        }
    }

    //Iterate through every cell in the board
    for (int y = 0; y < BOARD_Y; y++) {
        for (int x = 0; x < BOARD_X; x++) {
            //Count living neighbors
            int count = 0;
            if (board[y -1][x -1] == ALIVE) {       //top left
                count++;
            }
            if (board[y - 1][x] == ALIVE) {         //top
                count++;
            }
            if (board[y - 1][x + 1] == ALIVE) {     //top right
                count++;
            }
            if (board[y][x - 1] == ALIVE) {         //left
                count++;
            }
            if (board[y][x + 1] == ALIVE) {         //right
                count++;
            }
            if (board[y + 1][x - 1] == ALIVE) {     //bottom left
                count++;
            }
            if (board[y + 1][x] == ALIVE) {         //bottom
                count++;
            }
            if (board[y + 1][x + 1] == ALIVE) {     //bottom right
                count++;
            }

            //Enforce rules of life
            if (board[y][x] == ALIVE && count < 2) {                        //Rule Number 1
                temp[y][x] = DEAD;
            }
            else if (board[y][x] == ALIVE && (count == 2 || count == 3)) {  //Rule Number 2
                temp[y][x] = ALIVE;
            }
            else if (board[y][x] == ALIVE && count > 3) {                   //Rule Number 3
                temp[y][x] = DEAD;
            }
            else if (board[y][x] == DEAD && count == 3) {                   //Rule Number 4
                temp[y][x] = ALIVE;
            }
        }
    }

    //update board from the temp board
    for (int y = 0; y < BOARD_Y; y++) {
        for (int x = 0; x < BOARD_X; x++) {
            board[y][x] = temp[y][x];
        }
    }
}