#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#include "pyramid.h"

using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    PyramidBoard<char>* B = new PyramidBoard<char>();
    string player1Name, player2Name;

    cout << "Welcome to FCAI Pyramid Tic-Tac-Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> player1Name;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new PyramidPlayer<char>(player1Name, 'X');
            break;
        case 2:
            players[0] = new PyramidRandomPlayer<char>('X');
            break;
        case 3:
            players[0] = new pyramid_MinMax_Player<char>('X');  // Assign MinMax player
            players[0]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player O name: ";
    cin >> player2Name;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new PyramidPlayer<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new PyramidRandomPlayer<char>('O');
            break;
        case 3:
            players[1] = new pyramid_MinMax_Player<char>('O');  // Assign MinMax player
            players[1]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> pyramidGame(B, players);
    pyramidGame.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}
