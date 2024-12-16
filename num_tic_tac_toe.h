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
    Num_X_O_player (string name,T Symbol);
    void getmove(int& x, int& y);
private:
    T current_symbol = 0;
    T player_symbol = 0;

};

template <typename T>
class Num_X_O_Random_Player : public RandomPlayer<T>{
public:
    Num_X_O_Random_Player (T Symbol);
    void getmove(int &x, int &y) override;
private:
    T current_symbol = 0;
    T player_symbol = 0;

};

template <typename T>
vector<T> odd_numbers = {1,3,5,7,9};
template <typename T>
vector<T> even_numbers = {2,4,6,8};

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


            if(mark % 2 == 0) {
                auto it = find(even_numbers<T>.begin(), even_numbers<T>.end(), mark);
                even_numbers<T>.erase(it);
            }
            else {
                auto it = find(odd_numbers<T>.begin(), odd_numbers<T>.end(), mark);
                odd_numbers<T>.erase(it);
            }
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
Num_X_O_player<T>::Num_X_O_player(string name,T Symbol) : Player<T>(name,Symbol){
    player_symbol = Symbol;
}

template <typename T>
void Num_X_O_player<T>::getmove(int& x, int& y) {
        cout << "\n" << this->name << " Please enter your number (1 to 9) from this list: { ";
        if(player_symbol == 1) {
            for (int i = 0; i < odd_numbers<T>.size(); i++) {
                cout << odd_numbers<T>[i] << " ";
            }
            cout << "}";
            cin >> current_symbol;
            while (find(odd_numbers<T>.begin(), odd_numbers<T>.end(), current_symbol) == odd_numbers<T>.end()) {
                cout << "\n" << this->name << " invalid Please enter your number (1 to 9) from this list: {";
                for (int i = 0; i < odd_numbers<T>.size(); i++) {
                    cout << odd_numbers<T>[i] << ",";
                }
                cout << "} ";
                cin >> current_symbol;
            }

        }
        else {
            for (int i = 0; i < even_numbers<T>.size(); i++) {
                cout << even_numbers<T>[i] << " ";
            }
            cout << "}";
            cin >> current_symbol;
            while (find(even_numbers<T>.begin(), even_numbers<T>.end(), current_symbol) == even_numbers<T>.end()) {
                cout << "\n" << this->name << " invalid Please enter your number (1 to 9) from this list: {";
                for (int i = 0; i < even_numbers<T>.size(); i++) {
                    cout << even_numbers<T>[i] << ",";
                }
                cout << "} ";
                cin >> current_symbol;
            }
        }

        this->symbol = current_symbol;
        cout << "\n"<< this->name <<" Please enter your move x and y (0 to 2) separated by spaces: ";
        cin >> x >> y;
        }

// Constructor for Num_X_O__Random_Player
template <typename T>
Num_X_O_Random_Player<T>::Num_X_O_Random_Player(T Symbol) : RandomPlayer<T>(Symbol) {

    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
    player_symbol = Symbol;
}

template <typename T>
void Num_X_O_Random_Player<T>::getmove(int& x, int& y) {

    x = rand() % this->dimension;
    y = rand() % this->dimension;
    if(player_symbol == 1) {
        int currentIndex = rand() % odd_numbers<T>.size();
        current_symbol = odd_numbers<T>[currentIndex];
    }
    else {
        int currentIndex = rand() % even_numbers<T>.size();
        current_symbol = even_numbers<T>[currentIndex];
    }

    this->symbol = current_symbol;
    cout << "the computer played the number " << this->symbol << "in the cell (" << x << "," << y << ")" << endl;
}
#endif //NUM_TIC_TAC_TOE_H
