#include <iostream>
#include "BoardGame_Classes.h"
#include "game_2.h"
#include "BoardGame_Classes.cpp"
#include "game_2.cpp"

using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    WordBoard<char>* B = new WordBoard<char>();
    string player1Name, player2Name;

    cout << "Welcome to Word Tic-Tac-Toe Game! :)\n";

    // Set up Player 1
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new WordPlayer<char>(player1Name, ' ');
            break;
        case 2:
            players[0] = new RandomWordPlayer<char>(' ');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting.\n";
            return 1;
    }

    // Set up Player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new WordPlayer<char>(player2Name, ' ');
            break;
        case 2:
            players[1] = new RandomWordPlayer<char>(' ');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting.\n";
            return 1;
    }

    // Create game manager and run the game
    GameManager<char> word_game(B, players);
    word_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}
