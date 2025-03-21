#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <array>
#include <cstdint>

#include "raylib.h"

/*
 5 bit format for each piece. 01 - color white, 100 - piece type Bishop
*/

class Board {
    
    public:
        Board(const std::string& fen);
        //static std::string fen;

        static char getPiece(int rank, int file);
        static std::string movePiece(int fromRank, int fromFile, int toRank, int toFile);
        static void printBoard();
        static void printBoard(u_int64_t bitboard);

        static void loadFromFEN(const std::string& fenString);
        static std::string generateFEN();
        static void loadFen(Board &board, const std::string &fenString);
        static char board[8][8];

        
        static constexpr int White = 0; //0
        static constexpr int Black = 1; //1

        static constexpr int King = 0; //001
        static constexpr int Queen = 1; //010
        static constexpr int Bishop = 2; //011
        static constexpr int Knight = 3; //100
        static constexpr int Rook = 4; //101
        static constexpr int Pawn = 5; //111

        std::array<u_int64_t, 12> bitboardState = {};
        static constexpr int rankIndex(int square);
        static constexpr int fileIndex(int square);
        static constexpr int squareIndex(int rank, int file);
        static constexpr int IndexFromCoord(int file, int rank);
        void setPiece(int color, int pieceType, int square);
        void removePiece(int color, int pieceType, int square);
        bool isSquareOccupied(int color, int pieceType, int square) const;
        static void printBitBoard(Board &board);

        static u_int64_t bitboard[2][6];
        static char piecetoChar(int color, int pieceType);

        static void InitializeBitBoards();

    private:
        
        ;
        
};

#endif // BOARD_HPP

