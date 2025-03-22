#include "Move.hpp"
#include "Board.hpp"
#include <iostream>
#include <bitset>


//char (&board)[8][8] = Board::board;


std::string Move::movePiece(Board &board, int fromRank, int fromFile, int toRank, int toFile) {
    int fromSquare = Board::squareIndex(fromRank, fromFile);
    int toSquare = Board::squareIndex(toRank, toFile);

    if (fromSquare == toSquare) {
        return Board::generateFEN(board);  // Call generateFEN on the Board instance
    }
   

    int pieceType = board.getPieceType(fromSquare);
    int pieceColor = board.getPieceColor(fromSquare);

    if (pieceType == -1) {  // No piece at fromSquare
        return Board::generateFEN(board);
    }

    // Remove piece from old square
    board.bitboardState[pieceColor * 6 + pieceType] &= ~(1ULL << fromSquare);

    // Place piece on new square
    board.bitboardState[pieceColor * 6 + pieceType] |= (1ULL << toSquare);

    return Board::generateFEN(board);  // Call generateFEN on the Board instance
}



