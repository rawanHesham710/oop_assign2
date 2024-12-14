#ifndef PYRAMID_TICTACTOE_H
#define PYRAMID_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;

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

// PyramidRandomPlayer Class
template <typename T>
class PyramidRandomPlayer : public PyramidPlayer<T> {
public:
    PyramidRandomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};

#endif
