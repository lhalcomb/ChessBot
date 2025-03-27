#pragma once

#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>
#include "Board.hpp"
#include <vector>


class Move {
    public: 
        static std::string movePiece(Board &board, int fromRank, int fromFile, int toRank, int toFile);

        static std::vector<int> genLegalMoves(Board &board, int square);
        static std::vector<int> genPsuedoLegalMoves(Board &board, int square);

        //get the all of the moves for each piece
        static std::vector<int> genPawnMoves(Board &board, int square, int color);
        static std::vector<int> genKnightMoves(int square);
        static std::vector<int> genBishopMoves(Board &board, int square);
        static std::vector<int> genRookMoves(Board &board, int square);
        static std::vector<int> genQueenMoves(Board &board, int square);
        static std::vector<int> genKingMoves(int square);

        static bool isMoveLegal(const Board &board, int fromSquare, int toSquare);
        


        
};

#endif // MOVE_HPP