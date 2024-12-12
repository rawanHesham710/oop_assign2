#ifndef GAME_8_H
#define GAME_8_H

#include "BoardGame_Classes.h"

template <typename T>
class game8_Board:public Board<T> {
public:
    game8_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    void displaySmallBoard();
    void updateSmallBoard();
    char countWin(int starti,int startj, int endi,int endj);
    private:
    char smallBoard[3][3] = {};

};

template <typename T>
class game8_Player : public Player<T> {
public:
    game8_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class game8_Random_Player : public RandomPlayer<T>{
public:
    game8_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};



//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for game8_Board
template <typename T>
game8_Board<T>::game8_Board() {
    this->rows = this->columns = 9;
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
bool game8_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
            updateSmallBoard();
        }
        return true;
    }
    return false;
}
template<typename T>
void game8_Board<T>::updateSmallBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char result = countWin((i * 3), (j * 3), (i * 3) + 2, (j * 3) + 2);
            if (result == 'X' || result == 'O') {
                smallBoard[i][j] = result;
            }
        }
    }
}

// Display the board and the pieces on it
template <typename T>
void game8_Board<T>::displaySmallBoard() {
    for (int i = 0; i < 3; i++) {
        cout << "\n| ";
        for (int j = 0; j < 3; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << smallBoard[i][j] << " |";
        }
        cout << "\n-----------------------------  ";
    }
}

template <typename T>
void game8_Board<T>::display_board() {
    displaySmallBoard();
    cout << endl << endl << endl;
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
            if((j+1) % 3 == 0) {
                cout << "     ";
            }
        }
        cout << "\n-----------------------------     ---------------------------   -----------------------------";
        if((i+1) % 3 == 0) {
            cout << endl;
        }
    }
}

// Returns true if there is any winner
template<typename T>
char game8_Board<T>::countWin(int starti, int startj, int endi, int endj) {
    for (int i = starti; i <= endi; i++) {
        for (int j = startj; j <= endj; j++) {
            if ((j+2 < this ->columns && this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2]  && this->board[i][j] != 0) ||
                (i+2 < this ->rows && this->board[i][j] == this->board[i+1][j] && this->board[i+1][j] == this->board[i+2][j]  && this->board[i][j] != 0)) {
                return this->board[i][j];
            }
            if ((i+2 < this ->rows && j+2 < this ->columns && this->board[i][j] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j+2] && this->board[i][j] != 0) ||
                (i+2 < this ->rows && j-2 >= 0 && this->board[i][j] == this->board[i+1][j-1] && this->board[i+1][j-1] == this->board[i+2][j-2]  && this->board[i][j] != 0)) {
                return this->board[i][j];
            }
        }
    }
    return ' ';
}

template <typename T>
bool game8_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((smallBoard[i][0] == smallBoard[i][1] && smallBoard[i][1] == smallBoard[i][2] && smallBoard[i][0] != 0) ||
            (smallBoard[0][i] == smallBoard[1][i] && smallBoard[1][i] == smallBoard[2][i] && smallBoard[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((smallBoard[0][0] == smallBoard[1][1] && smallBoard[1][1] == smallBoard[2][2] && smallBoard[0][0] != 0) ||
        (smallBoard[0][2] == smallBoard[1][1] && smallBoard[1][1] == smallBoard[2][0] && smallBoard[0][2] != 0)) {
        return true;
    }

    return false;
}

template <typename T>
bool game8_Board<T>::is_draw() {
    return (this->n_moves == 81 && !is_win());
}

template <typename T>
bool game8_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for game8_Player
template <typename T>
game8_Player<T>::game8_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void game8_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for game8_Random_Player
template <typename T>
game8_Random_Player<T>::game8_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void game8_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}


#endif //GAME_8_H