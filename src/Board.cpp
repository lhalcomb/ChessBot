
#include "Board.hpp"
#include "InputHandler.hpp"
#include <iostream>
#include <cstdint>

#define BOARD_SIZE 8
 


uint64_t Board::bitboard[2][6] = {0};  // Initialize all bitboards to 0
char Board::board[8][8] = {}; 

Board::Board(const std::string& fen){
    loadFromFEN(fen);
}


char Board::getPiece(int rank, int file){
    if (rank >= 0 && rank < 8 && file >= 0 && file < 8){
        return board[rank][file];
    }else{
        return '.';
    }

};

char Board::piecetoChar(int color, int pieceType){
    
   const char pieceChars[2][6] = {
        {'K', 'Q', 'B', 'N', 'R', 'P'},
        {'k', 'q', 'b', 'n', 'r', 'p'}
    };

    return pieceChars[color][pieceType];
};

void Board::printBoard() {
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int f = 0; f < BOARD_SIZE; f++) {
            std::cout << board[r][f] << " ";
        }
        std::cout << std::endl;
    }
    
    //make for bitboards


}

void Board::loadFromFEN(const std::string &fenString) //
{   
    for (int r = 0; r < BOARD_SIZE; r++){
        for (int f = 0; f < BOARD_SIZE; f++){
            board[r][f] = '.';
        }
    }
    
    std::string fen = fenString; // copy the fen string
    int rank = 0; int file = 0; //init rank and file

    for (char c: fen){ //iterate through the fen string
        if (c == '/') { // if / that means new rank, increment rank and reset file
            rank++;
            file = 0;
        }
        else if (isdigit(c)){ // if digit, that means empty squares, move to next file in ABCDEFH
            file += c - '0'; // convert char to int
        }
        else if (isalpha(c)){ // if alphabet, that means piece
            board[rank][file] = c; // set the piece on the board
            file++; // move to next file
        }else{
            break; //accounts for castling rights in fen string
        }
    }
    printBoard();

      // make for bitboards
}

std::string Board::generateFEN()
{
    /*
    Generates a FEN string from the current board state
    */
    std::string fen = ""; //initialize fen string
    for (int r = 0; r < BOARD_SIZE; r++){
        int empty = 0; //empty square counter
        for (int f = 0; f < BOARD_SIZE; f++){
            char piece = board[r][f]; //get the piece on the board
            if (piece == '.'){ //if empty square
                empty++; //increment empty square counter
            }else{
                if (empty > 0){ //if empty square counter is greater than 0
                    fen += std::to_string(empty); //add the empty square counter to the fen string
                    empty = 0; //reset empty square counter
                }
                fen += piece; //add the piece to the fen string
            }
        }
        if (empty > 0){ //if empty square counter is greater than 0
            fen += std::to_string(empty); //add the empty square counter to the fen string
        }
        if (r < BOARD_SIZE - 1){ //if not the last rank
            fen += "/"; //add / to the fen string
        }
    }
    return fen; //return the fen string
   
    //make for bitboards

    
};


