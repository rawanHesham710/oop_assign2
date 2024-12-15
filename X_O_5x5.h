#ifndef X_O_5X5_H
#define X_O_5X5_H


#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

// Class Definitions
int check = 0;

template <typename T>
class X_O_5x5:public Board<T> {
private:
    int countX;
    int countO;
public:
    X_O_5x5();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    pair<int, int> count_wins();
};

template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
};


template <typename T>
class X_O_Random_Player : public RandomPlayer<T>{
public:
    X_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





// X_O_5x5_board Implementation
template<typename T>
X_O_5x5<T>::X_O_5x5() {
     this->rows = this->columns = 5;
     this->board = new char*[this->rows];
     for (int i = 0; i < this->rows; i++) {
      this->board[i] = new char[this->columns];
      for (int j = 0; j < this->columns; j++) {
       this->board[i][j] = 0;
      }
     }
     this->n_moves = 0;
}

template<typename T>
bool X_O_5x5<T>::update_board(int x, int y, T mark) {
    if(this->n_moves == 24) {
        check++;
        return true;
    }
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {

             if (mark == 0){
                 this->n_moves--;  // to reset the cell and decrement the counter
                 this->board[x][y] = 0;
             }
             else {
              this->n_moves++;
              this->board[x][y] = toupper(mark);
                 check++;
             }


          return true;
         }
  return false;
}

template <typename T>
void X_O_5x5<T>::display_board() {
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
pair<int, int> X_O_5x5<T>::count_wins() {
    countX = 0; // Number of wins for 'X'
    countO = 0; // Number of wins for 'O'

    // Check rows and columns
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) { // Only check for consecutive 3 cells
            // Check rows
            if (this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j + 1] == this->board[i][j + 2]) {
                if (this->board[i][j] == 'X') {
                    countX++;
                } else if (this->board[i][j] == 'O') {
                    countO++;
                }
            }
            // Check columns
            if (this->board[j][i] == this->board[j + 1][i] &&
                this->board[j + 1][i] == this->board[j + 2][i]) {
                if (this->board[j][i] == 'X') {
                    countX++;
                } else if (this->board[j][i] == 'O') {
                    countO++;
                }
            }
        }
    }

    // Check principle diagonal and anti-diagonal
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Principle diagonal
            if (this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i + 1][j + 1] == this->board[i + 2][j + 2]) {
                if (this->board[i][j] == 'X') {
                    countX++;
                } else if (this->board[i][j] == 'O') {
                    countO++;
                }
            }
            // Anti-diagonal
            if (this->board[i][j + 2] == this->board[i + 1][j + 1] &&
                this->board[i + 1][j + 1] == this->board[i + 2][j]) {
                if (this->board[i][j + 2] == 'X') {
                    countX++;
                } else if (this->board[i][j + 2] == 'O') {
                    countO++;
                }
            }
        }
    }

    return {countX, countO};
}

template <typename T>
bool X_O_5x5<T>::is_win() {

    if (this->n_moves < 24) {
        // Return true if there's at least one win
        return false;
    }
     // Count wins after move 24
    auto [countX, countO] = count_wins();

    if (this->n_moves == 24 && countO > countX) {
        return true; // Player 2 wins
    }

    // Check if Player 1 wins at move 25
    if (check == 25 && countX > countO) {
        return true; // Player 1 wins
    }

    return false; // No winner

}

template<typename T>
bool X_O_5x5<T>::is_draw() {
    if (this->n_moves > 24 && !is_win()) {
        return true;
    }
    return false;
}

template<typename T>
bool X_O_5x5<T>::game_is_over() {
    return is_win() || is_draw();
}

//------------------------------------------

template<typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}


template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    while (true) {
        if(check == 24) {
            return;
        }
    cout << "\n" << this->name << ", please enter your move x and y (0 to 4) separated by a space: ";

        string inputX, inputY;
        cin >> inputX >> inputY; // Read input as strings for validation

        // Check if both inputs are digits
        if (inputX.size() == 1 && inputY.size() == 1 && isdigit(inputX[0]) && isdigit(inputY[0])) {
            x = inputX[0] - '0'; // Convert character to integer
            y = inputY[0] - '0';

            // Validate range
            if (x >= 0 && x <= 4 && y >= 0 && y <= 4) {
                return; // Valid input, exit the loop
            }
            else{
                cout << "Coordinates must be between 0 and 4. Try again: ";
            }
        }
        else {
            cout << "Invalid input. Please enter digits between 0 and 4: ";
        }
    }
}


template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    cout << "Random player moves are" << x << ", " << y << endl;
}






#endif // X_O_5X5_H
