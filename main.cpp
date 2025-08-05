#include <iostream>
#include <ctime>
using namespace std;
// Function declarations
void drawBoard(char *spaces);
void playerMove(char *spaces, char player);
void computerMove(char *spaces, char computer);
bool checkWinner(char *spaces, char player, char computer);
bool checkTie(char *spaces);
int main() {
    // Initialize the board with empty spaces
    char spaces[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char player = 'X';     // Player marker
    char computer = 'O';   // Computer marker
    bool running = true;   // Game loop control

    drawBoard(spaces); // Display initial empty board

    while (running) {
        // Player makes a move
        playerMove(spaces, player);
        drawBoard(spaces);

        // Check if the player won
        if (checkWinner(spaces, player, computer)) {
            running = false;
            break;
        }

        // Check for tie after player move
        if (checkTie(spaces)) {
            cout << "It's a tie!\n";
            break;
        }

        // Computer makes a move
        computerMove(spaces, computer);
        drawBoard(spaces);

        // Check if the computer won
        if (checkWinner(spaces, player, computer)) {
            running = false;
            break;
        }

        // Check for tie after computer move
        if (checkTie(spaces)) {
            cout << "It's a tie!\n";
            break;
        }
    }

    return 0;
}

// Draw the current state of the board
void drawBoard(char *spaces) {
    cout << "\n";
    cout << "     |     |     \n";
    cout << "  " << spaces[0] << "  |  " << spaces[1] << "  |  " << spaces[2] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << spaces[3] << "  |  " << spaces[4] << "  |  " << spaces[5] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << spaces[6] << "  |  " << spaces[7] << "  |  " << spaces[8] << "  \n";
    cout << "     |     |     \n";
    cout << "\n";
}

// Handle the player's move input
void playerMove(char *spaces, char player) {
    int number;
    do {
        cout << "Enter a spot to place a marker (1-9): ";
        cin >> number;
        number--; // Convert to 0-based index

        // Check if the move is valid (within bounds and space is empty)
        if (number >= 0 && number < 9 && spaces[number] == ' ') {
            spaces[number] = player;
            break;
        } else {
            cout << "Invalid move! Try again.\n";
        }
    } while (true);
}

// Computer makes a random move
void computerMove(char *spaces, char computer) {
    int number;
    srand(time(0)); // Seed random number generator with current time

    // Find a random empty spot
    while (true) {
        number = rand() % 9;
        if (spaces[number] == ' ') {
            spaces[number] = computer;
            break;
        }
    }
}

// Check if either player or computer has won
bool checkWinner(char *spaces, char player, char computer) {
    // Define all possible win patterns
    int winPatterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };

    // Check each pattern for a win
    for (auto &pattern : winPatterns) {
        if (spaces[pattern[0]] != ' ' &&
            spaces[pattern[0]] == spaces[pattern[1]] &&
            spaces[pattern[1]] == spaces[pattern[2]]) {

            // Announce the winner
            if (spaces[pattern[0]] == player) {
                cout << "You win!!\n";
            } else {
                cout << "You lose!!\n";
            }
            return true;
        }
    }
    return false; // No winner found
}
// Check if the game is a tie
bool checkTie(char *spaces) {
    // If any space is empty, it's not a tie
    for (int i = 0; i < 9; i++) {
        if (spaces[i] == ' ') return false;
    }
    return true; // All spaces filled, it's a tie
}
