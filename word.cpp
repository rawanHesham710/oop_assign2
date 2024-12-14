#include "word.h"
#include <bits/stdc++.h>
using namespace std;

template <typename T>
WordBoard<T>::WordBoard() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    load_dic();
}

template <typename T>
void WordBoard<T>::load_dic() {
    ifstream file("dic.txt");
    string word;
    while (file >> word) {
        if (word.length() == 3) {
            valid_words.insert(word);
        }
    }
}

template <typename T>
bool WordBoard<T>::check_word(string word) {
    for (const string& valid_word : valid_words) {
        if (valid_word == word) {
            return true;
        }
    }
    return false;
}

template <typename T>
bool WordBoard<T>::update_board(int x, int y, T letter) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->n_moves++;
        this->board[x][y] = toupper(letter);
        return true;
    }
    return false;
}

template <typename T>
void WordBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n -------- -------- -------- ";
    }
    cout << endl;
}

template <typename T>
bool WordBoard<T>::is_win() {
    string word;

    // Check rows
    for (int i = 0; i < this->rows; i++) {
        word = "";
        for (int j = 0; j < this->columns; j++) {
            word += this->board[i][j];
        }
        if (check_word(word) || check_word(string(word.rbegin(), word.rend())))
            return true;
    }

    // Check columns
    for (int j = 0; j < this->columns; j++) {
        word = "";
        for (int i = 0; i < this->rows; i++) {
            word += this->board[i][j];
        }
        if (check_word(word) || check_word(string(word.rbegin(), word.rend())))
            return true;
    }

    // Check diagonals
    word = "";
    for (int i = 0; i < this->rows; i++) {
        word += this->board[i][i];
    }
    if (check_word(word) || check_word(string(word.rbegin(), word.rend())))
        return true;

    word = "";
    for (int i = 0; i < this->rows; i++) {
        word += this->board[i][this->columns - i - 1];
    }
    if (check_word(word) || check_word(string(word.rbegin(), word.rend())))
        return true;

    return false;
}

template <typename T>
bool WordBoard<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}

template <typename T>
bool WordBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

// WordPlayer Implementation
template <typename T>
WordPlayer<T>::WordPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void WordPlayer<T>::getmove(int& x, int& y) {
    while (true) {
        cout << this->getname() << ", enter your move (row and column): ";
        cin >> x >> y;

        if (cin.fail() || x < 0 || x >= 3 || y < 0 || y >= 3) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Row and column must be between 0 and 2.\n";
        } else {
            break;
        }
    }

    // Get the letter to place
    T pending_letter;
    while (true) {
        cout << this->getname() << ", enter the letter to place: ";
        cin >> pending_letter;

        if (isalpha(pending_letter)) {
            pending_letter = toupper(pending_letter);
            this->symbol = pending_letter;
            break;
        }
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid letter. Please enter an alphabetical character.\n";
        }
    }
}

// RandomWordPlayer Implementation
template <typename T>
RandomWordPlayer<T>::RandomWordPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void RandomWordPlayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    char random_letter = static_cast<char>('A' + rand() % 26);
    this->symbol = random_letter;
}
