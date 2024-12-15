#ifndef PYRAMID_TICTACTOE_H
#define PYRAMID_TICTACTOE_H

#include "BoardGame_Classes.h"

// PyramidBoard Class
template <typename T>
class PyramidBoard : public Board<T> {
public:
    PyramidBoard();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

// PyramidPlayer Class
template <typename T>
class PyramidPlayer : public Player<T> {
public:
    PyramidPlayer(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class PyramidRandomPlayer : public PyramidPlayer<T> {
public:
    PyramidRandomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class pyramid_MinMax_Player : public Player<T> {
public:
    pyramid_MinMax_Player(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getBestMove();
};


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
        return false;
    }
    if (this->board[x][y] == 0 || symbol == 0) {
        if (symbol == 0) {
            this->board[x][y] = 0;
            this->n_moves--;
        } else {
            this->board[x][y] = toupper(symbol);
            this->n_moves++;
        }
        return true;
    }
    return false;
}

template <typename T>
void PyramidBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            // Skip the specific indices
            if ((i == 0 && (j == 0 || j == 1 || j == 3 || j == 4)) ||
                (i == 1 && (j == 0 || j == 4))) {
                cout << "        ";
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


template <typename T>
pyramid_MinMax_Player<T>::pyramid_MinMax_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

// Method to get the best move for the player
template <typename T>
void pyramid_MinMax_Player<T>::getmove(int& x, int& y) {
    std::pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

// Minimax algorithm to evaluate the board
template <typename T>
int pyramid_MinMax_Player<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    } else if (this->boardPtr->is_draw()) {
        return 0;
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, s)) {
                int value = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (isMaximizing) {
                    bestValue = std::max(bestValue, value);
                } else {
                    bestValue = std::min(bestValue, value);
                }
            }
        }
    }

    return bestValue;
}

// Find the best move using the minimax algorithm
template <typename T>
std::pair<int, int> pyramid_MinMax_Player<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};
    T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';

    // First, check if we can win in the next move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0); // Undo move
                    return {i, j}; // Winning move found
                }
                this->boardPtr->update_board(i, j, 0); // Undo move
            }
        }
    }

    // Second, check if the opponent can win in their next move and block them
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, opponentSymbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0); // Undo move
                    return {i, j}; // Block opponent's winning move
                }
                this->boardPtr->update_board(i, j, 0); // Undo move
            }
        }
    }

    // If no immediate win or block, use MinMax to find the best move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(this->symbol, false);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }

    return bestMove;
}

#endif //_MINMAXPLAYER_H

