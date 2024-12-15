//
// Created by Mertcan Bakır on 1.05.2024.
//

#ifndef CS204_HW5_PLAYER_H
#define CS204_HW5_PLAYER_H

#include "Board.h"

class Player{

public:

    Player(Board& gameBoard, char chr); // Constructor of the Player class, takes game board object and symbol as parameters.

bool put(int a); // Function used to put a piece into a specific column.

void turn_board(); // rotates the board 90 degrees clockwise

bool is_winner();   // Function that checks if the player is a winner.

char get_symbol(); // Function that returns the player's symbol.

private:

    Board& board; // Reference to the game board object.
    char symbol; // Player's symbol.
};




#endif //CS204_HW5_PLAYER_H
