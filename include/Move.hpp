#pragma once

#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>

/*
enum class MoveType {
    NORMAL,
    CASTLE,
    EN_PASSANT,
    PROMOTION
};
*/

class Move {
    public: 
        static std::string movePiece(int fromRank, int fromFile, int toRank, int toFile);
        static bool isMoveValid(int fromRank, int fromFile, int toRank, int toFile);
        static bool isPathClear(int fromRank, int fromFile, int toRank, int toFile);
        static bool isCapture(int fromRank, int fromFile, int toRank, int toFile);
};

#endif // MOVE_HPP