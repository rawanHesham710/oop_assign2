//
// Created by Dell on 12/6/2024.
//

#ifndef MISERE_H
#define MISERE_H
#include "BoardGame_Classes.h"

bool win = false;
int score = 0;
template <typename T>
class X_O_Board:public Board<T> {

public:
    X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    bool loser();

};

template <typename T>
class m_Player : public Player<T> {
public:
    m_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class m_Random_Player : public RandomPlayer<T>{
public:
    m_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION


#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if( win == true){
        return true;
    }
    if(this->n_moves == 9) {
        this->n_moves++;
        return true;
    }
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            score++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}


// Display the board and the pieces on it
template <typename T>
void X_O_Board<T>::display_board() {
    if (win == true || score == 9) {
        return;
    }
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}




template <typename T>
bool X_O_Board<T>::is_win() {
    if (win) {
        return true;
    }

    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {

            win = true;
            }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {


        win = true;
        }

    return false;

}

// Return true if 9 moves are done and no winner
template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves == 10 && !is_win());
}

template <typename T>
bool X_O_Board<T>::game_is_over() {

    return this->n_moves > 10;

}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
 m_Player<T>::m_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void m_Player<T>::getmove(int& x, int& y) {
    if(score == 9 || win) {
        return;
    }

    cout << "\n" << this->name << ", please enter your move x and y (0 to 2) separated by a space: ";

    while (true) {
        string inputX, inputY;
        cin >> inputX >> inputY; // Read input as strings for validation

        // Check if both inputs are digits
        if (inputX.size() == 1 && inputY.size() == 1 && isdigit(inputX[0]) && isdigit(inputY[0])) {
            x = inputX[0] - '0'; // Convert character to integer
            y = inputY[0] - '0';

            // Validate range
            if (x >= 0 && x <= 2 && y >= 0 && y <= 2) {
                return; // Valid input, exit the loop
            }
            else{
                cout << "Coordinates must be between 0 and 2. Try again: ";
            }
        }
        else {
            cout << "Invalid input. Please enter digits between 0 and 2: ";
        }
    }

}

// Constructor for X_O_Random_Player
template <typename T>
m_Random_Player<T>::m_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void m_Random_Player<T>::getmove(int& x, int& y) {
    if(score == 9 || win) {
        return;
    }
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}






#endif //MISERE_H
