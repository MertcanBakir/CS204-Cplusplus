//
// Created by Mertcan Bakır on 1.05.2024.
//

#include "Board.h"
#include <iostream>


Board::~Board() {
    for(int i = 0; i < size; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
}


void Board::print_board(){
    cout << endl;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << matrix[i][j]; // Prints elements of the board.
        }
        cout << endl;
    }
    cout << endl;
}


bool Board::put_piece(char cha, int no){
    if(matrix[0][no] != '-'){ // If the column is full, the piece cannot be placed.
        return false;
    }else{
        int count = 0;
        while(count < size && matrix[count][no] == '-'){ // Looks for an empty row.
            count++;
        }
        if(count == size){
            matrix[size - 1][no] = cha; // If the column is not full, place the piece at the bottom row.
            return true;
        }else{
            matrix[count-1][no] = cha; // If the column is not full, place the piece one row above the first occupied row.
            return true;
        }
    }
}


void Board::turn_board_clockwise(){
    char** temp = new char*[size]; // Creates a temporary matrix.
    for(int i = 0; i < size; i++){
        temp[i] = new char[size];
    }
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            temp[i][j] = matrix[size - j - 1][i]; // Rotates the matrix clockwise.
        }
    }

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            matrix[i][j] = temp[i][j]; // Copies the new matrix to the old one.
        }
    }

    for (int j = 0; j < size; j++) {
        for (int i = size - 1; i >= 0; i--) {
            if (matrix[i][j] == '-') { // Fills empty cells with pieces.
                int k = i - 1;
                while (k >= 0 && matrix[k][j] == '-') {
                    k--;
                }
                if (k >= 0) {
                    matrix[i][j] = matrix[k][j];
                    matrix[k][j] = '-';
                }
            }
        }
    }

    for(int i = 0; i < size; i++) {
        delete[] temp[i]; // Deletes the temporary matrix from memory.
    }
    delete[] temp;
}



char Board::get_game_status() {
    int Xcounter = 0; // Counter for X
    int Ocounter = 0; // Counter for O


    bool Xfound = false; // Is X found?
    for (int i = 0; i < size && !Xfound; i++) {
        for (int j = 0; j <= size - N && !Xfound; j++) {
            Xcounter = 0;
            for (int k = 0; k < N; k++) {
                if (matrix[i][j + k] == 'X') { // Horizontal check, count Xs.
                    Xcounter++;
                }
            }
            if(Xcounter >= N){
                Xfound = true;
            }
        }
    }
    bool Ofound = false; // Is O found?
    for (int i = 0; i < size && !Ofound; i++) {
        for (int j = 0; j <= size - N && !Ofound; j++) {
            Ocounter = 0;
            for (int k = 0; k < N; k++) {
                if (matrix[i][j + k] == 'O') { // Horizontal check, count Os.
                    Ocounter++;
                }
            }
            if(Ocounter >= N){
                Ofound = true;
            }
        }
    }


    if (Xcounter >= N && Ocounter >= N) {
        return 'D'; // Draw
    } else if (Xcounter == N) {
        return 'X'; // X wins
    } else if (Ocounter == N) {
        return 'O'; // O wins
    }

    // Vertical check
    Xfound = false;
    Ofound = false;
    for (int j = 0; j < size && !Xfound; j++) {
        for (int i = 0; i <= size - N && !Xfound; i++) {
            Xcounter = 0;
            for (int k = 0; k < N; k++) {
                if (matrix[i + k][j] == 'X') { // Vertical check, count Xs.
                    Xcounter++;
                }
            }
            if (Xcounter >= N) {
                Xfound = true;
            }
        }
    }
    for (int j = 0; j < size && !Ofound; j++) {
        for (int i = 0; i <= size - N && !Ofound; i++) {
            Ocounter = 0;
            for (int k = 0; k < N; k++) {
                if (matrix[i + k][j] == 'O') { // Vertical check, count Os.
                    Ocounter++;
                }
            }
            if (Ocounter >= N) {
                Ofound = true;
            }
        }
    }
    if (Xcounter >= N && Ocounter >= N) {
        return 'D'; // Draw
    } else if (Xcounter == N) {
        return 'X'; // X wins
    } else if (Ocounter == N) {
        return 'O'; // O wins
    }


    // Diagonal check from left to right
    Xfound = false;
    Ofound = false;
    for (int i = 0; i <= size - N && !Xfound; i++) {
        for (int j = N - 1; j < size && !Xfound; j++) {
            Xcounter = 0;
            for (int k = 0; k < N; k++) {
                if (matrix[i + k][j - k] == 'X') { // Diagonal check, count Xs.
                    Xcounter++;
                }
            }
            if (Xcounter >= N) {
                Xfound = true;
            }
        }
    }

    for (int i = 0; i <= size - N && !Ofound; i++) {
        for (int j = N - 1; j < size && !Ofound; j++) {
            Ocounter = 0;
            for (int k = 0; k < N; k++) {
                if (matrix[i + k][j - k] == 'O') { // Diagonal check, count Os.
                    Ocounter++;
                }
            }
            if (Ocounter >= N) {
                Ofound = true;
            }
        }
    }

    if (Xcounter >= N && Ocounter >= N) {
        return 'D'; // Draw
    } else if (Xcounter == N) {
        return 'X'; // X wins
    } else if (Ocounter == N) {
        return 'O'; // O wins
    }

    // Diagonal check from right to left
    Xfound = false;
    Ofound = false;
    for (int i = 0; i <= size - N && !Xfound; i++) {
        for (int j = 0; j <= size - N && !Xfound; j++) {
            Xcounter = 0;
            for (int k = 0; k < N; k++) {
                if (matrix[i + k][j + k] == 'X') { // Diagonal check, count Xs.
                    Xcounter++;
                }
            }
            if (Xcounter >= N) {
                Xfound = true;
            }
        }
    }

    for (int i = 0; i <= size - N && !Ofound; i++) {
        for (int j = 0; j <= size - N && !Ofound; j++) {
            Ocounter = 0;
            for (int k = 0; k < N; k++) {
                if (matrix[i + k][j + k] == 'O') { // Diagonal check, count Os.
                    Ocounter++;
                }
            }
            if (Ocounter >= N) {
                Ofound = true;
            }
        }
    }

    if (Xcounter >= N && Ocounter >= N) {
        return 'D'; // Draw
    } else if (Xcounter == N) {
        return 'X'; // X wins
    } else if (Ocounter == N) {
        return 'O'; // O wins
    }

    // Check if the game is still ongoing
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(matrix[i][j] == '-'){
                return '-'; // Game still ongoing
            }
        }
    }

    return 'D'; // Draw
}
