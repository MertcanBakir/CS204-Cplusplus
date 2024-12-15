//
// Created by Mertcan Bakır on 1.05.2024.
//

#ifndef CS204_HW5_BOARD_H
#define CS204_HW5_BOARD_H

using namespace std;

class Board{
public:
Board(int boardsize, int n): size(boardsize), N(n){  // Constructor of the Board class, initializes the game board with the given size and winning condition.
    matrix = new char*[size]; // create the board
    for(int i = 0; i < size; i++){
        matrix[i] = new char [size];
    }
    for(int i = 0; i < size; i++){ // fill the column with '-'
        for(int j = 0; j < size; j++){
            matrix[i][j] = '-';
        }
    }
}

~Board(); // destructor

void print_board(); // print the board

bool put_piece(char cha, int no); // Function used to put a piece into a specific column.

void turn_board_clockwise(); // rotates the board 90 degrees clockwise

char get_game_status(); // Function to get the current status of the game


private:
    char** matrix;
    int N; // Winning condition
    int size; // Size of the game board
};

#endif //CS204_HW5_BOARD_H
