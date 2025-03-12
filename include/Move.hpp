#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>


class Move {
    public: 
        static std::string movePiece(int fromRank, int fromFile, int toRank, int toFile);
};

#endif // MOVE_HPP