#ifndef _3X3X_O_H
#define _3X3X_O_H

#include "BoardGame_Classes.h"
int counter = 0;
char check = ' ';

template <typename T>
class SUS_Board:public Board<T> {
public:
    SUS_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    void check_Win(T symbol);
private:
    bool row_count[3] = {false, false, false};
    bool col_count[3] = {false, false, false};
    bool dig_count[2] = {false, false};
    int S_count;
    int U_count;
};

template <typename T>
class SUS_Player : public Player<T> {
public:
    SUS_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T>{
public:
    SUS_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};


#include <bits/stdc++.h>
using namespace std;

template <typename T>
SUS_Board<T>::SUS_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->S_count = 0;
    this->U_count = 0;
    this->n_moves = 0;
}

template <typename T>
bool SUS_Board<T>::update_board(int x, int y, T symbol) {
    check = symbol;
    if(this->n_moves == 9){
        this->n_moves++;
        return true;
    }
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        counter++;
        return true;
    }
    return false;
}

template <typename T>
void SUS_Board<T>::display_board() {
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

// Checks for "SUS" sequences
template <typename T>
void SUS_Board<T>::check_Win(T symbol) {
    string word;
    for (int i = 0; i < this->rows; i++) {
        if(!row_count[i]){
        word = "";
        for (int j = 0; j < this->columns; j++) {
            word += this->board[i][j];
        }
        if (word == "SUS" && symbol == 'S') {
            S_count++;
            cout << " s counter" << S_count << endl;
            row_count[i] = true;
        }
        if (word == "SUS" && symbol == 'U') {
            U_count++;
            cout << " u counter" << U_count << endl;
            row_count[i] = true;
        }
        }
    }

    for (int j = 0; j < this->columns; j++) {
        if(!col_count[j]){
            word = "";
            for (int i = 0; i < this->rows; i++) {
                word += this->board[i][j];
            }
            if (word == "SUS" && symbol == 'S') {
                S_count++;
                cout << " s counter" << S_count << endl;
                col_count[j] = true;
            }
            if (word == "SUS" && symbol == 'U') {
                U_count++;
                cout << " u counter" << U_count << endl;
                col_count[j] = true;
            }
        }
    }

    word = "";
    word += this->board[0][0];
    word += this->board[1][1];
    word += this->board[2][2];
    if(!dig_count[0]){
        if (word == "SUS" && symbol == 'S') {
            S_count++;
            cout << " s counter" << S_count << endl;
            dig_count[0] = true;
        }
        if (word == "SUS" && symbol == 'U') {
            U_count++;
            cout << " u counter" << U_count << endl;
            dig_count[0] = true;
        }
    }

    word = "";
    word += this->board[0][2];
    word += this->board[1][1];
    word += this->board[2][0];
    if(!dig_count[1]){
        if (word == "SUS" && symbol == 'S') {
            S_count++;
            cout << " s counter" << S_count << endl;
            dig_count[1] = true;
        }
        if (word == "SUS" && symbol == 'U') {
            U_count++;
            cout << " u counter" << U_count << endl;
            dig_count[1] = true;
        }
    }
}

template <typename T>
bool SUS_Board<T>::is_win() {
    check_Win(check);
    if (this->n_moves == 9 && S_count > U_count) {
        return true;
    }

    if (this->n_moves == 10 && U_count > S_count) {
        return true;
    }
    return false;
}

template <typename T>
bool SUS_Board<T>::is_draw() {
    return (this->n_moves == 10 && !is_win() );
}

template <typename T>
bool SUS_Board<T>::game_is_over() {
    return this->n_moves > 10;
}

//--------------------------------------

// Constructor for SUS_Player
template <typename T>
SUS_Player<T>::SUS_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void SUS_Player<T>::getmove(int& x, int& y) {
    if(counter == 9)
        return;

    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for SUS_Random_Player
template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}


#endif