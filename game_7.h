//
// Created by Dell on 12/8/2024.
//


#ifndef GAME_7_H
#define GAME_7_H

#include "BoardGame_Classes.h"




template <typename T>
class game_7_Board:public Board<T> {
public:
    game_7_Board();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class game_7_Player : public Player<T> {
public:
    game_7_Player (string name, T symbol);
    void getmove(int& x, int& y) ;


};



template <typename T>
class game_7_Random_Player : public RandomPlayer<T>{
public:
    game_7_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};


//*****************implementation*********************


#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "game_7.h"


using namespace std;
int first_x, first_y;




// Constructor for X_O_Board
template <typename T>
game_7_Board<T>::game_7_Board() {
    this->rows = this->columns = 4;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->board[0][0] = this->board[0][2] =this->board[3][1] = this->board[3][3] = 'O';
    this->board[0][1] = this->board[0][3] = this->board[3][0] = this->board[3][2] = 'X';
    this->n_moves = 0;
}

template <typename T>
bool game_7_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if(this->board[first_x][first_y] == 0) {
        cout << "\nThe cell you have chosen is empty" << endl;
        return false;
    }
    if (mark != this->board[first_x][first_y]) {
        cout << "\nThe symbol you choose is for the other player\n";
        return false;
    }

    if(!(x == first_x +1 && y == first_y) && !(x == first_x - 1 && y == first_y) && !(x == first_x && y == first_y +1) && !(x == first_x && y == first_y - 1) ) {
        cout << "\nMove is invalid\n";
        return false;
    }


    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){

            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] =this->board[first_x][first_y];
            this->board[first_x][first_y] = 0;
        }

        return true;
    }
    return false;
}




// Display the board and the pieces on it
template <typename T>
void game_7_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n--------------------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool game_7_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
       for (int j = 0; j < this->columns; j++) {
           if ((j+2 < this->columns && this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2] && this->board[i][j] != 0)||
           (i + 2 < this->rows&& this->board[i][j] == this->board[i+1][j] && this->board[i+1][j] == this->board[i+2][j] && this->board[i][j] != 0 )) {
               return true;
           }

           //digaonals
           if ((i + 2 < this->rows && j + 2 < this->columns && this->board[i][j] == this->board[i + 1][j + 1] &&
             this->board[i + 1][j + 1] == this->board[i + 2][j + 2]  && this->board[i][j] != 0)||
              (  i + 2 < this->rows && j - 2 >= 0  && this->board[i][j] == this->board[i + 1][j - 1] && this->board[i+1][j-1] == this->board[i+2][j-2] && this->board[i][j] != 0 )) {
               return true;
             }
       }
    }


    return false;
}


template <typename T>
bool game_7_Board<T>::is_draw() {
    return false;
}

template <typename T>
bool game_7_Board<T>::game_is_over() {

    return is_win() ;
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
game_7_Player<T>::game_7_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void game_7_Player<T>::getmove(int& x, int& y) {


    while (true) {
        string inputX, inputY , fx, fy;
        cout << "enter the index of the cell you want to move: ";
        cin >> fx >> fy;

        cout << "\nPlease enter your move x and y (0 to 3) separated by spaces: ";


        cin >> inputX >> inputY; // Read input as strings for validation

        // Check if both inputs are digits
        if (inputX.size() == 1 && inputY.size() == 1 && isdigit(inputX[0]) && isdigit(inputY[0]) && fx.size() == 1 && fy.size() == 1 && isdigit(fx[0]) && isdigit(fy[0])) {
            first_x =fx[0] - '0';
            first_y =fy[0] - '0';

            x = inputX[0] - '0'; // Convert character to integer
            y = inputY[0] - '0';

            // Validate range
            if (x >= 0 && x <= 3 && y >= 0 && y <= 3 && first_x >= 0 && first_x <= 3 && first_y >= 0 && first_y <= 3) {
                return; // Valid input, exit the loop
            } else {
                cout << "Coordinates must be between 0 and 3. Try again\n";
            }
        } else {
            cout << "Invalid input. Please enter DIGITS between 0 and 3\n";
        }
    }


}

// Constructor for X_O_Random_Player
template <typename T>
game_7_Random_Player<T>::game_7_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void game_7_Random_Player<T>::getmove(int& x, int& y) {
    first_x = rand() % this->dimension ;
    first_y = rand() % this->dimension ;
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}




#endif //GAME_7_H
