#include <iostream>
#include "gameOfLife.h"
#include "wolfram.h"

using namespace std;

void menu();
void gameOfLife();
void wolfram();

int main() {
    menu();
    return 0;
}

void menu() {
    cout << "C++ Implementations of Different Cellular Automata" << endl;
    cout << "Type the number of the automaton you'd like to run, then hit ENTER." << endl;
    cout << "0: Wolfram's Elementary CA" << endl << "1: Conway's Game of Life" << endl << endl;

    int choice;
    cin >> choice;

    switch (choice) {
        case 0:
            wolfram();
            break;
        case 1:
            gameOfLife();
            break;
        default:
            cout << "You didn't type an option" << endl;
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
    better_structure();
}