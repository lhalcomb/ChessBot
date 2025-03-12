#ifndef MOVEECXECUTION_HPP
#define MOVEEXECUTION_HPP

#include <string>


class Move {
    public: 
        static std::string movePiece(int fromRank, int fromFile, int toRank, int toFile);
};

#endif // MOVEEXECUTION_HPP