#ifndef WORD_TIC_TAC_TOE_H
#define WORD_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;

// WordBoard Class
template <typename T>
class WordBoard : public Board<T> {
public:
    WordBoard();
    bool update_board(int x, int y, T letter);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

private:
    set<string> valid_words;
    void load_dic();
    bool check_word(string word);
};

// WordPlayer Class
template <typename T>
class WordPlayer : public Player<T> {
private:
    T pending_letter;

public:
    WordPlayer(string name, T symbol);
    void getmove(int& x, int& y);
    T get_letter();
};

// RandomWordPlayer Class
template <typename T>
class RandomWordPlayer : public RandomPlayer<T> {
public:
    RandomWordPlayer(T symbol);
    void getmove(int& x, int& y);
    T get_letter();
};

#endif // WORD_TIC_TAC_TOE_H
