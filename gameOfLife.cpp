#include <iostream>
#include <string>
#include <fstream>
#include <ncurses.h>

using namespace std;

const int BOARD_Y = 21;
const int BOARD_X = 80;
const char ALIVE = 'X'; 
const char DEAD = '.';
char board[BOARD_Y][BOARD_X];
char update[BOARD_Y][BOARD_X];
string FILENAMES[] = { "explosion.txt", "glider_gun.txt" } ;

bool load_file();
void start_simulation();
void update_round();

int main() {
    if (load_file()) {
        start_simulation();
    }
    else {
        cout << "Error Loading File" << endl;
    }
    return 0;
}

bool load_file()  {
    ifstream loadFile;
    cout << "This is a C++ simulator of Conway's Game of Life." << endl;
    cout << "Type the number of the file you'd like to run." << endl;
    cout << "Followed by ENTER." << endl;
    cout << "0: Explosion" << endl << endl;
    cout << "1: Glider Gun" << endl << endl;


    int choice;
    cin>>choice;

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
    initscr();
    raw();
    noecho();
    //curs_set(0);
    keypad(stdscr, TRUE);
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
    endwin();
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
            else if (board[y][x] == ALIVE && (count == 2 || count == 3)) {   //Rule Number 2
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