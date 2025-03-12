#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

#include "raylib.h"

class Board {
    
    public:
        Board(const std::string& fen);
        //static std::string fen;

        static char getPiece(int rank, int file);
        static std::string movePiece(int fromRank, int fromFile, int toRank, int toFile);
        static void printBoard();

        static void loadFromFEN(const std::string& fenString);
        static std::string generateFEN();
        static char board[8][8];

    private:
        
        ;
        
};

#endif // BOARD_HPP

