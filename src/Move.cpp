#include "Move.hpp"
#include "Board.hpp"
#include <iostream>
#include <bitset>
#include <algorithm>
#include "PreCompMoveData.hpp"


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

std::vector<int> Move::genLegalMoves(Board &board, int square)
{
    std::vector<int> pseudoLegalMoves = genPsuedoLegalMoves(board, square);
    std::vector<int> legalMoves;
    for (int move: pseudoLegalMoves)
    {
        if (isMoveLegal(board, square, move))
        {
            legalMoves.push_back(move);
        }
    }
    return legalMoves;
}

std::vector<int> Move::genPsuedoLegalMoves(Board &board, int square)
{
    std::vector<int> moves;
    int color, pieceType; 
    if (!board.getPieceAtSquare(square, color, pieceType)) return moves;

    uint64_t moveBitboard = 0;
    switch (pieceType)
    {
        case Board::King: // King
            moveBitboard = genKingMoves(square);
            break;
        case Board::Queen: // Queen
            moveBitboard = genQueenMoves(board, square);
            break;
        case Board::Bishop: // Bishop
            moveBitboard = genBishopMoves(board, square);
            break;
        case Board::Knight: // Knight
            moveBitboard = genKnightMoves(square);
            break;
        case Board::Rook: // Rook
            moveBitboard = genRookMoves(board, square);
            break;
        case Board::Pawn: // Pawn
            moveBitboard = genPawnMoves(board, square, color);
            break;
    }

    for (int i = 0; i < 64; i++)
    {
        if (moveBitboard & (1ULL << i))
        {
            moves.push_back(i);
        }
    }

    return  moves;
}

uint64_t Move::genPawnMoves(Board &board, int square, int color)
{   
    uint64_t moves = 0;
    int direction = (color == Board::White) ? 8 : -8;

    //move forward a square
    int forwardSquare = square + direction;
    if (!board.isSquareOccupiedbyAnyPiece(board, forwardSquare))
    {
        moves |= (1ULL << forwardSquare);
    }

    //Double move forward (only on starting rank)
    if ((color == Board::White && square >= 8 && square <= 15) || 
        (color == Board::Black && square >= 48 && square <= 55))
    {
        int doubleForwardSquare = square + 2 * direction;
        if (!board.isSquareOccupiedbyAnyPiece(board, doubleForwardSquare))
        {
            moves |= (1ULL << doubleForwardSquare);
        }
    }

    //Captures (left and right diagonal)
    uint64_t enemyPieces = (color == Board::White) ? board.bitboardState[1] : board.bitboardState[0];
    bool notOnLeftEdge = square % 8 != 0;
    bool notOnRightEdge = square % 8 != 7;
    if ((notOnLeftEdge && (enemyPieces & (1ULL << (forwardSquare - 1))))) //left diagonal
    {
        moves |= (1ULL << (forwardSquare - 1));
    }

    if ((notOnRightEdge && (enemyPieces & (1ULL << (forwardSquare + 1))))) //right diagonal
    {
        moves |= (1ULL << (forwardSquare + 1));
    }

    //en passant rules
    //TODO

    return  moves;
}

uint64_t Move::genKnightMoves(int square)
{   
    // uint64_t moves = 0;
    // for (uint8_t targetSquare: PreCompMoveData::knightMoves[square]) {
    //     moves |= (1ULL << targetSquare);
    // }
    // return moves;

    return PreCompMoveData::knightAttacks[square];
}

uint64_t Move::genBishopMoves(Board &board, int square)
{
    std::cout << "Bishop Moves for square " << square << ": " << std::bitset<64>(PreCompMoveData::bishopMoves[square]) << std::endl;

    return PreCompMoveData::bishopMoves[square];
}

uint64_t Move::genRookMoves(Board &board, int square)
{
    std::cout << "Rook Moves for square " << square << ": " << std::bitset<64>(PreCompMoveData::rookMoves[square]) << std::endl;
    return PreCompMoveData::rookMoves[square];
}

uint64_t Move::genQueenMoves(Board &board, int square)
{
    std::cout << "Queen Moves for square " << square << ": " << std::bitset<64>(PreCompMoveData::queenMoves[square]) << std::endl;
    std::cout << "Queen Moves for square 3: " 
          << std::bitset<64>(PreCompMoveData::queenMoves[3]) << std::endl;


    return PreCompMoveData::queenMoves[square];
}

uint64_t Move::genKingMoves(int square)
{   
    return PreCompMoveData::kingAttacks[square];
}
//Check if there isn't a king in check, meaning it is a legal move
bool Move::isMoveLegal(const Board &board, int fromSquare, int toSquare)
{
    //temporarily make the move on the board
    Board tempBoard = board;
    int color, pieceType;
    tempBoard.getPieceAtSquare(fromSquare, color, pieceType);
    tempBoard.removePiece(color, pieceType, fromSquare);
    tempBoard.setPiece(color, pieceType, toSquare);

    //check if the king is in check
    int kingSquare = -1;
    for (int i = 0; i < 64; i++)
    {
        int c, p;
        if (tempBoard.getPieceAtSquare(i, c, p) && c == color && p == Board::King)
        {
            kingSquare = i;
            break;
        }
    }

    //If the king is under attack,then the move is illegal
    for (int i = 0; i < 64; i++)
    {
        if (tempBoard.isSquareOccupied(1 - color, Board::Pawn, i) ||
            tempBoard.isSquareOccupied(1 - color, Board::Knight, i) ||
            tempBoard.isSquareOccupied(1 - color, Board::Bishop, i) ||
            tempBoard.isSquareOccupied(1 - color, Board::Rook, i) ||
            tempBoard.isSquareOccupied(1 - color, Board::Queen, i) || 
            tempBoard.isSquareOccupied(1 - color, Board::King, i))
        {
            std::vector<int> enemyMoves = genPsuedoLegalMoves(tempBoard, i);

            if (std::find(enemyMoves.begin(), enemyMoves.end(), kingSquare) != enemyMoves.end())
            {
                return false;
            }
        }
    }
    return true;
}


