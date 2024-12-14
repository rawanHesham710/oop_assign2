
#ifndef CONNECT_FOUR_H
#define CONNECT_FOUR_H

#include "BoardGame_Classes.h"

template <typename T>
class ConnectFour_board : public Board<T> {
    public:
    ConnectFour_board();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};
template <typename T>
class ConnectFour_Player : public Player<T> {
public:
    ConnectFour_Player(string name, T symbol);
    void getmove(int& x, int& y);

};

template <typename T>
class ConnectFour_Random_Player : public RandomPlayer<T>{
public:
    ConnectFour_Random_Player(T symbol);
    void getmove(int &x, int &y) ;
};

//-----------------------------------------IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

template <typename T>
ConnectFour_board<T>::ConnectFour_board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char*[this->rows,this->columns];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool ConnectFour_board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            for (int x = this->rows - 1; x >= 0; x--) {
                if (this->board[x][y] == 0) { // Empty cell
                    this->board[x][y] = toupper(mark); // Place the player's piece
                    this->n_moves++;
                    return true;
                }
            }
        }
        return true;
    }
    return false;
}

template <typename T>
void ConnectFour_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n----------------------------------------------------------------";
    }
    cout << endl;
}

template <typename T>
bool ConnectFour_board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if ((j+3 < this ->columns && this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2] && this->board[i][j+2] == this->board[i][j+3] && this->board[i][j] != 0) ||
                (i+3 < this ->rows && this->board[i][j] == this->board[i+1][j] && this->board[i+1][j] == this->board[i+2][j] && this->board[i+2][j] == this->board[i+3][j] && this->board[i][j] != 0)) {
                return true;
            }
        }
    }

    // Check diagonals
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if ((i+3 < this ->rows && j+3 < this ->columns && this->board[i][j] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j+2] && this->board[i+2][j+2] == this->board[i+3][j+3] && this->board[i][j] != 0) ||
                (i+3 < this ->rows && j-3 >= 0 && this->board[i][j] == this->board[i+1][j-1] && this->board[i+1][j-1] == this->board[i+2][j-2] && this->board[i+2][j-2] == this->board[i+3][j-3] && this->board[i][j] != 0)) {
                return true;
            }
        }
    }
    return false;
}
template <typename T>
bool ConnectFour_board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool ConnectFour_board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
ConnectFour_Player<T>::ConnectFour_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void ConnectFour_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter the column number (0 to 6)";
    x = 0;
    cin >> y;

}

// Constructor for X_O_Random_Player
template <typename T>
ConnectFour_Random_Player<T>::ConnectFour_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void ConnectFour_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension-1;
    y = rand() % this->dimension;
    cout << "the computer choose the column number: (" << y << ")" << endl;
}
#endif //CONNECT_FOUR_H
