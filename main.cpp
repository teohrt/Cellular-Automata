#include <iostream>
#include <ncurses.h>
#include "main.h"
#include "gameOfLife.h"
#include "wolfram.h"

int main() {
    //Initialize ncurses
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    menu();
    return 0;
}

void menu() {
    bool run = true;
    while(run){
        mvprintw(3, 27, "---------------------");
        mvprintw(4, 27, "CELLULAR AUTOMATA CLI");
        mvprintw(5, 27, "---------------------");
        mvprintw(7, 11, "C++ Implementations of Different Cellular Automata");
        mvprintw(8, 11, "Type the number of the automaton you'd like to run");
        mvprintw(10, 24, "0: Wolfram's Elementary CA");
        mvprintw(11, 24, "1: Conway's Game of Life");
        mvprintw(13, 22, "Press ESC to quit the program");
        refresh();
        switch (getch()) {
            case 48:
                wolfram();
                run = false;
                break;
            case 49:
                endwin();
                gameOfLife();
                run = false;
                break;
            case 27:
                endwin();
                exit(0);
                break;
            default:
                mvprintw(15, 21, "!!!YOU DIDN'T TYPE AN OPTION!!!");
                refresh();
                break;
        }
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