#include <iostream>
#include "wolfram.h"
#include <limits.h>
#include <stdio.h>
#include <ncurses.h>

using namespace std;

const int BOARD_Y = 21;
const int BOARD_X = 80;

// Binary conversion of decimal user input in future
int ruleset[8]; //= { 0, 1, 0, 1, 1, 0, 1, 0};
int wolframBoard[BOARD_Y][BOARD_X] = { };
int gen;

void automaton() {
    //1 in the middle for the traditional initial state
    wolframBoard[0][BOARD_X/2] = 1;

    //Get user's input, convert to binary and initialize the rule set array
    handle_user_input();

    //Run the ruleset on the initial state
    while(gen < BOARD_Y - 1) {
        find_next_generation();
    }
    print_generations();

    mvprintw(0, 0, "Press any key to continue or ESC to quit.");
    refresh();
    switch(getch()) {
        case 27:
            endwin();
            exit(1);
            break;
    }
    gen = 0;
    automaton();
}

void print_generations() {
    clear();
    for (int i = 0; i < BOARD_Y; i++) {
        for (int j = 0; j < BOARD_X; j++) {
            if (wolframBoard[i][j] == 0) {
                mvprintw(i, j, " ");
            }
            else {
                mvprintw(i, j, "X");
            }
        }
        cout << endl;
    }
    refresh();
}

void find_next_generation() {
    int left, center, right;
    //Gets environment's values while ignoring edge cases. (0's instead)
    for (int i = 0; i < BOARD_X; i++) {
        left    = wolframBoard[gen % BOARD_Y][(i + BOARD_X - 1) % BOARD_X];
        center  = wolframBoard[gen % BOARD_Y][i]; 
        right   = wolframBoard[gen % BOARD_Y][(i + 1) % BOARD_X];

        wolframBoard[(gen + 1) % BOARD_Y][i] = rule(left, center, right);
    }
    gen++;
}
//The next generation of a cell is dependent on the current generation's environment.
//The environment of each cell is that of itself and its two adjacent neighbors.
//That's three cells to account for that could be one of two states.
//That's 3 bits in binary that together can produce 8 different values.
//Every cell's environment can influence the future generation in 8 different ways.
//This function points to the ruleset array for the predetermined future state determined by the current environment's binary representation.
int rule (int a, int b, int c) {
    if (a == 1 && b == 1 && c == 1) {
        return ruleset[0];
    }
    if (a == 1 && b == 1 && c == 0) {
        return ruleset[1];
    }
    if (a == 1 && b == 0 && c == 1) {
        return ruleset[2];
    }
    if (a == 1 && b == 0 && c == 0) {
        return ruleset[3];
    }
    if (a == 0 && b == 1 && c == 1) {
        return ruleset[4];
    }
    if (a == 0 && b == 1 && c == 0) {
        return ruleset[5];
    }
    if (a == 0 && b == 0 && c == 1) {
        return ruleset[6];
    }
    //else (a == 0 && b == 0 && c == 0) {
        return ruleset[7];
    //}
}

void handle_user_input()
{   clear();
    mvprintw(0, 0, "Type in the number of the rule you'd like to run and press enter.");
    refresh();

    //trick to get string of input from user rather than typical ncurses single char ASCII value inputs
    string input;

    //terminal does the editing
    nocbreak();
    echo();
    //reads from buffer after ENTER
    int ch = getch();

    while (ch !=  '\n') {
        input.push_back(ch);
        ch = getch();
    }
    //converts the user's string to int
    int x = stoi(input);

    //fix ncurses settings
    raw();
    noecho();

    //Grabs the flipped binary value from the int and inserts into array
    for (int i = sizeof(x) * CHAR_BIT; i--; )
    {
        if (i < 8) { 
            char temp = ('0' + ((x >> i) & 1));
            int x = temp - '0';
            ruleset[i] = x; 
        }
    }

    //Flip the array
    for (int i = 0; i < 8/2; i++) {
        int temp = ruleset[i];
        ruleset[i] = ruleset[7 - i];
        ruleset[7 - i] = temp;
    }
}