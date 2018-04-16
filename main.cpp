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
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    while(1){
        clear();
        mvprintw(0, 0, "C++ Implementations of Different Cellular Automata");
        mvprintw(1, 0, "Type the number of the automaton you'd like to run");
        mvprintw(2, 0, "0: Wolfram's Elementary CA - Rule 90");
        mvprintw(3, 0, "1: Conway's Game of Life");
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