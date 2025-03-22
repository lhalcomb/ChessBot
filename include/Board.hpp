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

        static char getPiece(int rank, int file);
        static void printBoard(u_int64_t bitboard);

        
        static std::string generateFEN(Board &board);
        static void loadFen(Board &board, const std::string &fenString);
        

        
        static constexpr int White = 0; //0
        static constexpr int Black = 1; //1

        static constexpr int King = 0; //001
        static constexpr int Queen = 1; //010
        static constexpr int Bishop = 2; //011
        static constexpr int Knight = 3; //100
        static constexpr int Rook = 4; //101
        static constexpr int Pawn = 5; //111



        std::array<u_int64_t, 12> bitboardState;
        static constexpr int rankIndex(int square);
        static constexpr int fileIndex(int square);
        static constexpr int squareIndex(int rank, int file);
        void setPiece(int color, int pieceType, int square);
        void removePiece(int color, int pieceType, int square);
        bool isSquareOccupied(int color, int pieceType, int square) const;
        static bool isSquareOccupiedbyAnyPiece(Board &board, int square);
        static void printBitBoard(Board &board);


        bool getPieceAtSquare(int selectedSquare, int& color, int& pieceType);
        int getPieceType(int square);
        int getPieceColor(int square);

        static char piecetoChar(int color, int pieceType);


    private:
        
        ;
        
};

#endif // BOARD_HPP

