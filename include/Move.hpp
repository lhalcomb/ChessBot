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
        static uint64_t genPawnMoves(Board &board, int square, int color);
        static uint64_t genKnightMoves(int square);
        static uint64_t genSlidingMoves(Board &board, int square, const int deltas[], int numDeltas);
        static uint64_t genBishopMoves(Board &board, int square);
        static uint64_t genRookMoves(Board &board, int square);
        static uint64_t genQueenMoves(Board &board, int square);
        static uint64_t genKingMoves(int square);

        static bool isMoveLegal(const Board &board, int fromSquare, int toSquare);
        


        
};

#endif // MOVE_HPP