//<Source.cpp> -- Battleship game using 2D arrays
//CSIS 111-<D01>
//<Sources if necessary>

//Include statements
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

//Global declarations: Constants and type definitions only -- no variables
const int ROWS = 10;
const int COLUMNS = 10;

//Function prototypes
void fire(std::vector<std::vector<int>>, std::vector<std::vector<int>>, std::pair<int, int>);
bool fleetSunk(std::vector<std::vector<int>>);
void printBoard(std::vector<std::vector<int>>);
int charToInt(char choice);

int main()
{
    //In cout statement below SUBSTITUTE  your name and lab number
    std::cout << "Noah Lopez -- Lab 8" << std::endl << std::endl;
    //Variable declarations
    std::vector<std::vector<char>> gameBoard, consoleBoard;
    //char gameBoard[ROWS][COLUMNS], consoleBoard[ROWS][COLUMNS];
    //double hitPercentage[2] = {0, 0};
    std::pair <int, int> hitPercentage;

    bool allShipsSunk = false;
    //std::ifstream inFile;
    //inFile.open("Board.txt");

    //Program logic
    //If file did not open, print out error
   //if (!inFile) {
        std::cout << "File did not open!" << std::endl;
    }

    //Initialize the characters for the board from text file
    //Also initializes the console board to blank water
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            char boardPiece;
            inFile >> boardPiece;
            gameBoard[i][j] = boardPiece;
            consoleBoard[i][j] = '~';
        }
    }

    //play until all the ships are sunk
    do {
        printBoard(consoleBoard);
        fire(gameBoard, consoleBoard, hitPercentage);
        allShipsSunk = fleetSunk(gameBoard);
    } while (!allShipsSunk);

    double accuracy = 100 * hitPercentage.first / (hitPercentage.first + hitPercentage.second);
    std::cout << "The fleet was destroyed!" << std::endl;
    printBoard(consoleBoard);
    std::cout << "Your accuracy was: " << std::setprecision(4) << accuracy << "!"<< std::endl;

    //Closing program statements
    system("pause");
    return 0;
}

//Function definitions

/*  Parameters: char[25][25] for the game's board
*   Takes in one (x,y) coordinate and checks to see if the player hit anything
*   Doesn't return anything, but should change the char in the grid, depending on the input
*/
void fire(char board[ROWS][COLUMNS], char consoleBoard[ROWS][COLUMNS], double percent[2]) {
    int inRow = 0, inCol = 0;
    char charCol;
    bool validInt = false, validChar = false;
    std::cout << "Enter an (x,y) coordinate from 'a'/'A'  to 'y'/'Y'(inclusive), 1 to 25 (inclusive)" << std::endl;
    std::cout << "Enter it in the format: (A 12) or (a 12). Letter(uppercase or lowercase), then whole number" << std::endl;

    std::cout << "Enter your column" << std::endl;
    //validates column input(char)
    do {
        validChar = true;
        std::cin >> charCol;
        //65 : 'A', 89: 'Y', 97: 'a', 121: 'y'
        if (!std::cin || charCol < 65 || (89 < charCol && charCol < 97) || charCol > 121) {
            validChar = false;
            std::cin.clear();
            std::cin.ignore(200, '\n');
        }
        if (!validChar) {
            std::cout << "Invalid row input. Please try again." << std::endl;
        }
    } while (!validChar);
    std::cout << "You entered(column): " << charCol << std::endl;
    std::cin.clear();
    std::cin.ignore(200, '\n');

    std::cout << "Enter your row" << std::endl;
    //validates row input(int)
    do {
        validInt = true;
        std::cin >> inRow;
        if (!std::cin || inRow < 1 || inRow > 25) {
            validInt = false;
            std::cin.clear();
            std::cin.ignore(200, '\n');
        }
        if (!validInt) {
            std::cout << "Invalid column input. Please try again" << std::endl;
        }
    } while (!validInt);

    std::cout << "You entered: " << inRow << std::endl;
    std::cin.clear();
    std::cin.ignore(200, '\n');

    inCol = charToInt(charCol);     //converts char to int
    inRow--;    //decrease so that it doesn't go out of bounds within the array
    
    //     ?
    //   ? # ?      Check grid around # to see if ship has been hit already or not
    //     ?
    if (board[inRow][inCol] == '#') {
        //Check to make sure that inRow or inCol are not 24,
        //because +1 on either of those would exceed the bounds of the array
        if (inRow == 0) {
            //top right
            if (inCol == 24) {
                if (board[inRow][inCol - 1] == 'H' || board[inRow + 1][inCol] == 'H') {
                    std::cout << "HIT AGAIN!" << std::endl;
                }
            }
            //top left
            else if (inCol == 0) {
                if (board[inRow + 1][inCol] == 'H' || board[inRow][inCol + 1] == 'H') {
                    std::cout << "HIT AGAIN!" << std::endl;
                }
            }
            //Mids
            else {
                if (board[inRow - 1][inCol] == 'H' || board[inRow][inCol + 1] == 'H' || board[inRow + 1][inCol] == 'H') {
                    std::cout << "HIT AGAIN!" << std::endl;
                }
            }
        }
        else if (inRow == 24) {
            //bottom right
            if (inCol == 24) {
                if (board[inRow][inCol - 1] == 'H' || board[inRow - 1][inCol] == 'H') {
                    std::cout << "HIT AGAIN!" << std::endl;
                }
            }
            //bottom left
            else if (inCol == 0) {
                if (board[inRow - 1][inCol] == 'H' || board[inRow][inCol + 1] == 'H') {
                    std::cout << "HIT AGAIN!" << std::endl;
                }
            }
            //Mids
            else {
                if (board[inRow + 1][inCol] == 'H' || board[inRow][inCol + 1] == 'H' || board[inRow][inCol - 1] == 'H') {
                    std::cout << "HIT AGAIN!" << std::endl;
                }
            }
        }
        //Actual middles that have 4 spots adjacent
        else {
            if (board[inRow + 1][inCol] == 'H' || board[inRow][inCol - 1] == 'H' || board[inRow][inCol + 1] == 'H' || board[inRow - 1][inCol] == 'H') {
                std::cout << "HIT AGAIN!" << std::endl;
            }
        }
        board[inRow][inCol] = 'H';
        consoleBoard[inRow][inCol] = 'H';
        percent[0]++;
    }
    // Check to see if it was a miss
    else if (board[inRow][inCol] == '~') {
        std::cout << "MISS" << std::endl;
        consoleBoard[inRow][inCol] = 'M';
        percent[1]++;
    }
    // Should reach here only on 'H' or 'M'
    else{
        std::cout << "You've already hit this spot!" << std::endl;
    }
}

/*  Parameters: char[25][25] for the game's board
*   Checks to see if any of the chars in the 2-D array are '#'
*   returns true, if 'the '#'s no longer exist. false if there is a single 'H' remaining.
*/
bool fleetSunk(char board[ROWS][COLUMNS]) {
    //Loop through rows and columns of board
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            //If a single char == '#', then return false
            if (board[i][j] == '#') {
                return false;
            }
        }
    }
    //returns true only if no char '#' remains
    return true;
}

// Prints out the board given
// Prints out a header with letters, and a sidebar with values
// This allows for easier coordinate choices
void printBoard(char consoleBoard[ROWS][COLUMNS]) {
    std::cout << "Current board:" << std::endl;
    std::cout << "   A B C D E F G H I J" << std::endl;
    for (int i = 0; i < ROWS; i++) {
        std::cout << std::setw(2) << (i+1);
        for (int j = 0; j < COLUMNS; j++) {
            std::cout << " " << consoleBoard[i][j];
        }
        std::cout << std::endl;
    }
}


// Converts a char to an int
// Checks to see if the char is a letter(uppercase or lowercase)
int charToInt(char choice) {
    //uppercase
    if (65 <= choice && choice <= 90) {
        return (int)choice - 65;
    }
    //lowercase
    else if(97 <= choice && choice <= 122){
        return (int)choice - 97;
    }
}