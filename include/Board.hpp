#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <cstdint>

#include "raylib.h"

/*
enum class PieceType {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};
class Piece{
    int None = 0;
    int King = 1;
    int Pawn = 2;
    int Knight = 3;
    int Bishop = 4;
    int Rook = 5;
    int Queen = 6;

    int White = 0;
    int Black = 1;

};
 5 bit format for each piece. 01 - color white, 100 - piece type king
*/

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

        static u_int64_t boardState;

        static constexpr int White = 0;
        static constexpr int Black = 1;

        static constexpr int King = 1;
        static constexpr int Queen = 2;
        static constexpr int Bishop = 3;
        static constexpr int Knight = 4;
        static constexpr int Rook = 5;
        static constexpr int Pawn = 6; 

        static u_int64_t bitboard[2][6];
        static char piecetoChar(int color, int pieceType);





    private:
        
        ;
        
};

#endif // BOARD_HPP

