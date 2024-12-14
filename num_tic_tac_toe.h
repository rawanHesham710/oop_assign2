#ifndef NUM_TIC_TAC_TOE_H
#define NUM_TIC_TAC_TOE_H

#include <set>

#include "BoardGame_Classes.h"

template <typename T>
class Num_X_O_Board:public Board<T> {
public:
    Num_X_O_Board();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Num_X_O_player : public Player<T> {
public:
    Num_X_O_player (string name,T Symbol,vector<int> numbers);
    void getmove(int& x, int& y);
    T getsymbol();
private:
    T current_symbol;
    vector<int> numbers;
};

template <typename T>
class Num_X_O_Random_Player : public RandomPlayer<T>{
public:
    Num_X_O_Random_Player (T Symbol,vector<int> numbers);
    void getmove(int &x, int &y) override;
    T getsymbol();
private:
    T current_symbol;
    vector<int> numbers;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

// Constructor for Num_X_O_Board
template <typename T>
Num_X_O_Board<T>::Num_X_O_Board(){
    this->rows = this->columns = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Num_X_O_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = mark;
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Num_X_O_Board<T>::display_board() {
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

// Returns true if there is any winner
template <typename T>
bool Num_X_O_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] + this->board[i][1] + this->board[i][2] == 15 && this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0) ||
            (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15 && this->board[0][i] != 0 && this->board[1][i] != 0 && this->board[2][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15 && this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0) ||
        (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15 && this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0] != 0)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Num_X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Num_X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


// Constructor for Num_X_O_player
template <typename T>
Num_X_O_player<T>::Num_X_O_player(string name,T Symbol, vector<int> numbers) : Player<T>(name, Symbol) , current_symbol(Symbol), numbers(numbers) {}

template<typename T>
T Num_X_O_player<T>::getsymbol() {
    return this->symbol;
}

template <typename T>
void Num_X_O_player<T>::getmove(int& x, int& y) {
        cout << "\n" << this->name << " Please enter your number (1 to 9) from this list: { ";
        for (int i = 0; i < this->numbers.size(); i++) {
            cout << this->numbers[i] << " ";
        }
        cout << "}";
        cin >> current_symbol;

        while (
            find(this->numbers.begin(), this->numbers.end(), current_symbol) == this->numbers.end()) {
            cout << "\n" << this->name << " invalid Please enter your number (1 to 9) from this list: {";
            for (int i = 0; i < this->numbers.size(); i++) {
                cout << this->numbers[i] << ",";
            }
            cout << "} ";
            cin >> current_symbol;
        }

        this->numbers.erase(find(this->numbers.begin(), this->numbers.end(), current_symbol));
        this->symbol = current_symbol;
        cout << "\n"<< this->name <<" Please enter your move x and y (0 to 2) separated by spaces: ";
        cin >> x >> y;
        }

// Constructor for Num_X_O__Random_Player
template <typename T>
Num_X_O_Random_Player<T>::Num_X_O_Random_Player(T Symbol, vector<int> numbers) : RandomPlayer<T>(Symbol), numbers(numbers) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Num_X_O_Random_Player<T>::getmove(int& x, int& y) {
    current_symbol = rand() % 10;

    while (find(this->numbers.begin(), this->numbers.end(), current_symbol) == this->numbers.end()) {
        current_symbol = rand() % 10;
    }
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    this->symbol = current_symbol;
    this->numbers.erase(find(this->numbers.begin(), this->numbers.end(), current_symbol));
    cout << "the computer played the number " << this->symbol << "in the cell (" << x << "," << y << ")" << endl;

}
#endif //NUM_TIC_TAC_TOE_H
