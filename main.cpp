#include <iostream>
#include "gameOfLife.h"
#include "wolfram.h"
#include <ncurses.h>

using namespace std;

const int BOARD_Y = 21;
const int BOARD_X = 80;

void menu();
void gameOfLife();
void wolfram();

int main() {
    menu();
    return 0;
}

void menu() {
    //Initialize ncurses
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    while(1){
        clear();
        mvprintw(3, 27, "---------------------");
        mvprintw(4, 27, "CELLULAR AUTOMATA CLI");
        mvprintw(5, 27, "---------------------");
        mvprintw(7, 11, "C++ Implementations of Different Cellular Automata");
        mvprintw(8, 11, "Type the number of the automaton you'd like to run");
        mvprintw(10, 24, "0: Wolfram's Elementary CA");
        mvprintw(11, 24, "1: Conway's Game of Life");
        refresh();
        switch (getch()) {
            case 48:
                wolfram();
                break;
            case 49:
                endwin();
                gameOfLife();
                break;
            default:
                cout << "You didn't type an option" << endl;
                break;
        }
        break;
    }
}

void gameOfLife() {
    if (load_file()) {
        start_simulation();
    }
    else {
        cout << "Error Loading File" << endl;
    }
}

void wolfram() {
    automaton();
}