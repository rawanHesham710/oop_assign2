#include "game_1.h"
#include <bits/stdc++.h>
using namespace std;

template <typename T>
PyramidBoard<T>::PyramidBoard(){
    this->rows = 3;
    this->columns = 5;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool PyramidBoard<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < (2 - x) || y > (2 + x)) {
        cout << "The position (" << x << ", " << y << ") is not within the pyramid boundaries.Try again."<<endl;
        return false;
    }
    if (this->board[x][y] != 0) {
        cout << "The position (" << x << ", " << y << ") is already Taken. Try again."<<endl;
        return false;
    }
    this->board[x][y] = symbol;
    ++this->n_moves;
    return true;
}

template <typename T>
void PyramidBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            // Skip the specific indices
            if ((i == 0 && (j == 0 || j == 1 || j == 3 || j == 4)) ||
                (i == 1 && (j == 0 || j == 4))) {
                cout << "      "; // Add spacing to align properly
                continue;
            }
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n--------------------------------------";
    }
    cout << endl;
}

template <typename T>
bool PyramidBoard<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns ; j++) {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i][j + 1] &&  this->board[i][j + 1] == this->board[i][j + 2]) {
                return true;
            }
        }
    }
    if ((this->board[0][2] != 0 && this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0]) ||
        (this->board[0][2] != 0 && this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4]) ||
        (this->board[0][2] != 0 && this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2]) ) {
        return true;
    }
    return false;
}


template <typename T>
bool PyramidBoard<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}

template <typename T>
bool PyramidBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

// PyramidPlayer Definitions
template <typename T>
PyramidPlayer<T>::PyramidPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void PyramidPlayer<T>::getmove(int& x, int& y) {
    bool valid = false;
    while (!valid) {
        cout << "\n" << this->name << ", please enter your move (row and column): ";
        if (cin >> x >> y) {
            valid = true;
        }
        else{
            cout << "Invalid input. Please enter numeric values for row and column.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

template <typename T>
PyramidRandomPlayer<T>::PyramidRandomPlayer(T symbol) : PyramidPlayer<T>("Random Computer Player", symbol) {
    srand(static_cast<unsigned int>(time(0))); 
}

template <typename T>
void PyramidRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % 3;
    y = rand() % 5;
}

