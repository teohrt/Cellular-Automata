#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <ncurses.h>
#include "wolfram.h"
#include "main.h"

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

    mvprintw((BOARD_Y), 0, "Press any key to continue or ESC to quit.");
    refresh();
    switch(getch()) {
        case 27:
            clear();
            menu();
            return;
    }
    gen = 0;
    clear();
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
        return ruleset[7];
    }
    if (a == 1 && b == 1 && c == 0) {
        return ruleset[6];
    }
    if (a == 1 && b == 0 && c == 1) {
        return ruleset[5];
    }
    if (a == 1 && b == 0 && c == 0) {
        return ruleset[4];
    }
    if (a == 0 && b == 1 && c == 1) {
        return ruleset[3];
    }
    if (a == 0 && b == 1 && c == 0) {
        return ruleset[2];
    }
    if (a == 0 && b == 0 && c == 1) {
        return ruleset[1];
    }
    //else (a == 0 && b == 0 && c == 0) {
        return ruleset[0];
    //}
}

void handle_user_input()
{   
    clear();
    mvprintw(3, 21, "-------------------------------------");
    mvprintw(4, 21, "WOLFRAM ELEMENTARY CELLULAR AUTOMATON");
    mvprintw(5, 21, "-------------------------------------");
    mvprintw(7, 10, "Rule 30, 60, 90, 105, 182, 147 are interesting generations.");
    mvprintw(9, 24, "Type in the integer of the rule");
    mvprintw(10, 29, "to see the evolution."); 
    mvprintw(11, 17, "(Numbers 0 - 255 are all possible rule sets)");
    mvprintw(13, 29, "Then press press ENTER.");
    mvprintw(14, 34, "('Q' to QUIT)");
    mvprintw(16, 15, "These generations would continue to evolve infinitely");
    mvprintw(17, 21, "But ... our terminal is only so big!");
    refresh();

    //Trick to get string of input from user rather than the typical ncurses single char ASCII value 
    string input;
    
    //Terminal does the editing
    nocbreak();
    echo();
    //Reads from buffer after ENTER
    int ch = getch();

    while (ch !=  '\n') {
        input.push_back(ch);
        ch = getch();
    }

    //Fix ncurses settings
    raw();
    noecho();

    if (input == "Q") {
        clear();
        menu();
        return;
    }

    //Error handling the user's input string
    bool only_numbers = (input.find_first_not_of("0123456789") == string::npos);

    if (!only_numbers) {
        mvprintw(20, 12, "!!!!!!Make sure to type a number between 0 and 255!!!!!!");
        handle_user_input();
        return;
    }

    //Converts the user's string to int
    int x = stoi(input);

    if (x < 0 || x > 255) {
        mvprintw(20, 12, "!!!!!!Make sure to type a number between 0 and 255!!!!!!");
        handle_user_input();
        return;
    }

    //Grabs the binary value from the int and inserts into array
    for (int i = sizeof(x) * CHAR_BIT; i--; )
    {
        if (i < 8) { 
            char temp = ('0' + ((x >> i) & 1));
            int x = temp - '0';
            ruleset[i] = x; 
        }
    }
}