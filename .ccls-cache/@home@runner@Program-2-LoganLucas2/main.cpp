/**------------------------------------------
    Program 2: Great 13

    Course: CS 141, Fall 2022.
    System: Linux x86_64 and G++
    Author: Logan Lucas, George Maratos and David Hayes
 ---------------------------------------------**/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <map>
#include <string>

/* Everything below this comment is starter code, and you are not
allowed to modify */

using namespace std;

// Function that displays the instructions to the user

void display_instructions()
{
    cout << "Class: CS 141" << endl
         << "Program 2: Great 13" << endl << endl
         << "Make a series of jumps until there is a single piece left" << endl
         << "anywhere on board. On each move you must jump an adjacent" << endl
         << "piece   into   an  empty  square,  jumping  horizontally," << endl
         << "vertically, or diagonally." << endl << endl
         << "Input of 'R' resets the board back to the beginning, and " << endl
         << "'X' exits the game." << endl;
}

// The internal representation of the board as an array. Do not modify directly.

char board[13]{};

/* These two functions are how you will get and set elements on the board. Only
use these two when changing, or reading the board. */

char get_element(char position)
{
    if ((position < 'A') || (position > 'M')) {
        cout << "Failed to get element at position " << position << endl
             << "Make sure the given position is an uppercase letter " << endl
             << "between A-M." << endl;
        exit(1);
    }
    return board[position - 'A'];
}

void set_element(char position, char value)
{
    if ((position < 'A') || (position > 'M')) {
        cout << "Failed to set element at postion " << position << endl
             << "Make sure the given position is an uppercase letter " << endl
             << "between A-M." << endl;
        exit(1);
    }
    board[position - 'A'] = value;
}

// print out the board with the legend on the right

void display_board()
{
    cout << endl;
    cout << setw(7) << "Board" << setw(12) << "Position" << endl;
    cout << setw(5) << board[0] << setw(11) << 'A' << endl
         << setw(3) << board[1] << ' ' << board[2] << ' ' << board[3]
         << setw(11) << "B C D" << endl
         << board[4] << ' ' << board[5] << ' ' << board[6] << ' '
         << board[7] << ' ' << board[8] << ' '
         << " E F G H I" << endl
         << setw(3) << board[9] << ' ' << board[10] << ' ' << board[11]
         << setw(11) << "J K L" << endl
         << setw(5) << board[12] << setw(11) << 'M' << endl;
    cout << endl;
}

/* This is the end of the starter code, and below is where you can
add your own code. Feel free to add helper functions or variables.
*/

/* forward declarations for the functions you will write later. This
is so the order of the function definitions, in this file,  does not
matter. */

void make_move();
void initialize_board();
bool game_over();

// my functions
bool check_move(string userMove);
void modify_board(string userMove);


int main()
{
    display_instructions();
    initialize_board();
    do {
        make_move();

        } while (!game_over() && !cin.eof()); 
    if (game_over()) {
        cout << "Congrats you win!" << endl;
    }
    
    return 0;
}

// prompts the user to make a move
void make_move()
{
    bool validMove = true;
    string userMove;
    string upperTemp;

    display_board();
    
    cout << "Enter positions from, jump, and to (e.g. EFG): ";
    cin >> userMove;

    // converts input to uppercase
    for (int i = 0; i < userMove.size(); i++) {
        upperTemp += toupper(userMove[i]); 
    }
    userMove = upperTemp;

    validMove = check_move(userMove);

    if (!validMove) {
        make_move();
    }
    else {
        modify_board(userMove);
    }
}

// checks if the user input is valid
bool check_move(string userMove) {
    bool validMove = true;
    bool validSequence;
    
    string horizontal[10] = {"BCD", "DCB", "EFG", "FGH", "GHI", "IHG", "HGF", "GFE", "JKL", "LKJ"};
    string vertical[10] = {"BFJ", "JFB", "ACG", "CGK", "GKM", "MKG", "KGC", "GCA", "DHL", "LHD"};
    string diagonal[12] = {"ABE", "EBA", "DGJ", "JGD", "ILM", "MLI", "ADI", "IDA", "BGL", "LGB", "EJM", "MJE"};

    // creates an array of characters from userMove string
    char userMoveArray[userMove.size() - 1];
    for (int i = 0; i < userMove.size(); i++) {
        userMoveArray[i] = userMove[i];
    }
    char move = userMoveArray[0];
    char jump = userMoveArray[1];
    char land = userMoveArray[2];
    
    // checks input size and exits, resets, or prints error
    if (userMove.size() != 3) {
        if (userMove == "X") {
            cout << "Exiting." << endl; 
            exit(1);
        }
        else if (userMove == "R") {
            cout << "Restarting game." << endl;
            initialize_board();
            validMove = false;
        }
        else {
            cout << "*** Invalid sequence. Please retry." << endl;
            validMove = false;
        }
    }

    // only runs when all other test cases are passed
    if (validMove) {
        // checks for valid input range
        for (int i = 0; i < userMove.size(); i++) {
            if (userMoveArray[i] < 'A' || userMoveArray[i] > 'M') {
                cout << "*** Given move has positions not on the board! Please retry." << endl;
                validMove = false;
            }
        } 
    }
    // only runs when all other test cases are passed
    if (validMove) {
        // checks if move jumps over a space
        if (get_element(jump) == '.') {
            cout << "*** Must jump a piece. Please retry." << endl;
            validMove = false;
        }
        // checks if jumping peg is a space
        else if (get_element(move) == '.') {
            cout << "*** Source needs a piece. Please retry." << endl;
            validMove = false;
        }
        // checks if peg lands in an empty space
        else if (get_element(land) != '.') {
            cout << "*** Destination must be empty. Please retry." << endl;
            validMove = false;
        }
    }

    // only runs when all other test cases are passed
    if (validMove) {
        // checks for valid move
        validSequence = false;
        for (int i = 0; i < 10; i++) {
            if (userMove == horizontal[i] || userMove == vertical[i]) {
                validSequence = true;
            }
        }
        for (int i = 0; i < 12; i++) {
            if (userMove == diagonal[i]) {
                validSequence = true;
            }
        }
        if (!validSequence) {
            cout << "*** Move is invalid. Please retry." << endl;
            validMove = false;
        }   
    }
    return validMove;
}

// changes the board's visual after a valid move is made
void modify_board(string userMove) {
    // creates an array of characters from userMove string
    char userMoveArray[userMove.size() - 1];
    for (int i = 0; i < userMove.size(); i++) {
        userMoveArray[i] = userMove[i];
    }

    char move = userMoveArray[0];
    char jump = userMoveArray[1];
    char land = userMoveArray[2];

    set_element(move, '.');
    set_element(jump, '.');
    set_element(land, '#');
}

// checks if the user wins the game
bool game_over()
{
    int pegCount = 0;

    for (char i = 'A'; i <= 'M'; i++) {
        if (get_element(i) == '#') {
            pegCount += 1;
        }
    }
    if (pegCount == 1) {
        return true;
    }
    return false;
}

void initialize_board()
{
    for (char i = 'A'; i <= 'M'; i++) {
        if (i != 'G') {
            set_element(i, '#');
        }
        // sets the middle peg to '.'
        else {
            set_element(i, '.');
        }
    }
}