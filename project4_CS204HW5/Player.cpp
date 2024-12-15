//
// Created by Mertcan Bakır on 1.05.2024.
//

#include "Player.h"

Player::Player(Board& gameBoard, char playerSymbol) : board(gameBoard), symbol(playerSymbol){}

bool Player::put(int col) {
    if(board.put_piece(symbol, col)) { // if it is not already filled, return false
        return true;
    } else {
        return false;
    }
}


void Player::turn_board() { // rotates the board 90 degrees clockwise
    board.turn_board_clockwise();
}



bool Player::is_winner() { //Checks if there is a winner on the board
    if(board.get_game_status() == symbol){
        return true;
    }else{
        return false;
    }
}

char Player::get_symbol() { // Returns symbol for who will play
    return symbol;
}