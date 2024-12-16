#include <iostream>
#include "BoardGame_Classes.h"
#include "SUS.h"

using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    SUS_Board<char>* B = new SUS_Board<char>();
    string player1Name, player2Name;

    cout << "Welcome to Word Tic-Tac-Toe Game! :)\n";
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new SUS_Player<char>(player1Name, 'S');
            break;
        case 2:
            players[0] = new SUS_Random_Player<char>('S');
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
            players[1] = new SUS_Player<char>(player2Name, 'U');
            break;
        case 2:
            players[1] = new SUS_Random_Player<char>('U');
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
