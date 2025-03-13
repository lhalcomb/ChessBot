#include "Move.hpp"
#include "Board.hpp"


char (&board)[8][8] = Board::board;



std::string Move::movePiece(int fromRank, int fromFile, int toRank, int toFile){
    if (fromRank == toRank && fromFile == toFile){
        return Board::generateFEN();
    }

    if ((board[fromRank][fromFile] == '.')){
        return Board::generateFEN();

    }

    board[toRank][toFile] = board[fromRank][fromFile];
    board[fromRank][fromFile] = '.';
    

    return Board::generateFEN();
};

