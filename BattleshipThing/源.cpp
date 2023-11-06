#include <iostream>
#include <fstream>
using namespace std;

const int BOARD_SIZE = 25;

// Function to display the game board without altering the board itself
void displayBoard(char gameBoard[BOARD_SIZE][BOARD_SIZE]) {
    char tempBoard[BOARD_SIZE][BOARD_SIZE];

    // Create a temporary board with '#' characters replaced by '~'
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (gameBoard[i][j] == '#') {
                tempBoard[i][j] = '~';
            }
            else {
                tempBoard[i][j] = gameBoard[i][j];
            }
        }
    }

    // Display the temporary board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << tempBoard[i][j];
        }
        cout << endl;
    }
}

void fire(int x, int y, char gameBoard[BOARD_SIZE][BOARD_SIZE]) {
    if (gameBoard[x][y] == 'H') {
        cout << "HIT AGAIN" << endl;
    }
    else if (gameBoard[x][y] == '#') {
        cout << "HIT" << endl;
        gameBoard[x][y] = 'H';
    }
    else {
        cout << "MISS" << endl;
    }
}

bool fleetSunk(char gameBoard[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (gameBoard[i][j] == '#') {
                return false;
            }
        }
    }
    return true;
}

int main() {
    char gameBoard[BOARD_SIZE][BOARD_SIZE];

    // Initialize the game board
    ifstream boardFile("board.txt");
    if (!boardFile.is_open()) {
        cerr << "Error: Could not open the game board file." << endl;
        return 1;
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            boardFile >> gameBoard[i][j];
        }
    }

    boardFile.close();

    // Main game loop
    do {
        int x, y;
        cout << "Enter coordinates (x and y): ";
        cin >> x >> y;

        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
            cout << "Invalid coordinates. Please try again." << endl;
            continue;
        }

        fire(x, y, gameBoard);
        displayBoard(gameBoard);
    } while (!fleetSunk(gameBoard));

    cout << "The fleet was destroyed!" << endl;
    displayBoard(gameBoard);

    return 0;
}
