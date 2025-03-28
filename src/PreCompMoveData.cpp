#include "PreCompMoveData.hpp"
#include "Board.hpp"
#include <algorithm>
#include <iostream>

// Static member definitions

// Precomputed move lists (square -> possible destinations)
std::array<std::array<int, 8>, 64> PreCompMoveData::numSquaresToEdge;
std::array<PreCompMoveData::MoveList, 64> PreCompMoveData::knightMoves; //Knights have max 8 moves
std::array<PreCompMoveData::MoveList, 64> PreCompMoveData::kingMoves; //Kings have max 8 moves

//Precomputed Attack data
std::array<std::array<uint8_t, 2>, 64> PreCompMoveData::pawnAttackDirections = {{
    {4, 6}, {7, 5}
}};

std::array<std::vector<int>, 64> PreCompMoveData::pawnAttacksWhite;
std::array<std::vector<int>, 64> PreCompMoveData::pawnAttacksBlack;

PreCompMoveData::AttackBitBoards PreCompMoveData::kingAttacks;
PreCompMoveData::AttackBitBoards PreCompMoveData::knightAttacks;
std::array<PreCompMoveData::AttackBitBoards, 2> PreCompMoveData::pawnAttacks;

PreCompMoveData::SlidingPieces PreCompMoveData::rookMoves;
PreCompMoveData::SlidingPieces PreCompMoveData::bishopMoves;
PreCompMoveData::SlidingPieces PreCompMoveData::queenMoves;


int PreCompMoveData::directionLookup[127];
int PreCompMoveData::orthogonalDistance[64][64];
int PreCompMoveData::kingDistance[64][64];
int PreCompMoveData::centreManhattanDistance[64];

void PreCompMoveData::Initialize() {
    for (int squareIndex = 0; squareIndex < 64; ++squareIndex){
        int file = squareIndex % 8;
        int rank = squareIndex / 8;

        // Initialize the numSquaresToEdge array
        int north = 7 - rank; int south = rank;
        int west = file; int east = 7 - file;
        numSquaresToEdge[squareIndex] = {north, south, west, east,
                                         std::min(north, west), std::min(south, east),
                                         std::min(north, east), std::min(south, west)};
    

    // === Initialize the Knight Moves array & Knight Attacks ===

    std::vector<uint8_t> legalKnightMoves;
    uint64_t knightBitboard = 0;
    for (int delta: {15, 17, -17, -15, 10, -6, 6, -10}) {
        int jumpSquare = squareIndex + delta;
        if (jumpSquare >= 0 && jumpSquare < 64) {
            int jumpRank = jumpSquare / 8;int jumpFile = jumpSquare % 8;
            if (std::max(std::abs(rank - jumpRank), std::abs(file - jumpFile)) <= 2) {
                legalKnightMoves.push_back(jumpSquare);
                knightBitboard |= 1ULL << jumpSquare;
                }

            }
        }

    knightMoves[squareIndex] = legalKnightMoves;
    knightAttacks[squareIndex] = knightBitboard;

    // === Initialize the King Moves array & King Attacks ===
    std::vector<uint8_t> legalKingMoves;
    uint64_t kingBitboard = 0;
    for (int delta: directionOffsets){
        int targetSquare = squareIndex + delta;
        if (targetSquare >= 0 && targetSquare < 64){
            int targetRank = targetSquare / 8; int targetFile = targetSquare % 8;
            if (std::max(std::abs(rank - targetRank), std::abs(file - targetFile)) <= 1){
                legalKingMoves.push_back(targetSquare);
                kingBitboard |= 1ULL << targetSquare;
            }
        }
    }
    kingMoves[squareIndex] = legalKingMoves;
    kingAttacks[squareIndex] = kingBitboard; 

    // === Compute the Pawn Attacks ===
    std::vector<int> whitePawnAttacks, blackPawnAttacks;
    pawnAttacks[squareIndex] = {0, 0};

    if (file > 0){
        if (rank < 7) whitePawnAttacks.push_back(squareIndex + 7), pawnAttacks[squareIndex][0] |= 1ULL << (squareIndex + 7);
        if (rank > 0) blackPawnAttacks.push_back(squareIndex - 9), pawnAttacks[squareIndex][1] |= 1ULL << (squareIndex - 9); 
    }
    if (file < 7){
        if (rank < 7) whitePawnAttacks.push_back(squareIndex + 9), pawnAttacks[squareIndex][0] |= 1ULL << (squareIndex + 9);
        if (rank > 0) blackPawnAttacks.push_back(squareIndex - 7), pawnAttacks[squareIndex][1] |= 1ULL << (squareIndex - 7);
    }
    pawnAttacksWhite[squareIndex] = whitePawnAttacks;
    pawnAttacksBlack[squareIndex] = blackPawnAttacks;

    // === Intialize the Sliding Piece Moves (Rook, Queen & Bishop) ===
    rookMoves[squareIndex] = 0;
    bishopMoves[squareIndex] = 0;
    queenMoves[squareIndex] = 0; 


    for (int directionInd = 0; directionInd < 4; ++directionInd){
        int currentDirOffset = directionOffsets[directionInd];
        //std::cout << "Direction Offset: " << currentDirOffset << std::endl;

        for (int n = 0; n < numSquaresToEdge[squareIndex][directionInd]; n++) {
            int targetSquare = squareIndex + currentDirOffset * (n + 1);
            rookMoves[squareIndex] |= 1ULL << targetSquare;
        }
    }
    for (int directionInd = 4; directionInd < 8; ++directionInd){
        int currentDirOffset = directionOffsets[directionInd];
        //std::cout << "Direction Offset: " << currentDirOffset << std::endl;

        for (int n = 0; n < numSquaresToEdge[squareIndex][directionInd]; n++) {
            int targetSquare = squareIndex + currentDirOffset * (n + 1);
            bishopMoves[squareIndex] |= 1ULL << targetSquare;
            }
        }
    queenMoves[squareIndex] = rookMoves[squareIndex] | bishopMoves[squareIndex];

    }

    // === Initialize the move direction lookup ===

    // Direction lookup initialization
    for (int i = 0; i < 127; i++) {
        int offset = i - 63;
        int absOffset = std::abs(offset);
        int absDir = 1;

        if (absOffset % 9 == 0) {
            absDir = 9;
        } else if (absOffset % 8 == 0) {
            absDir = 8;
        } else if (absOffset % 7 == 0) {
            absDir = 7;
        }

        directionLookup[i] = absDir * (offset < 0 ? -1 : 1);
    }

    // === initialize distnace lookup tables ===
    for (int squareA; squareA < 64; squareA++){
        Coord cordA = Board::getCoordFromIndex(squareA);
        
        int fileDistFromCentre = std::max(3 - cordA.file, cordA.file - 4);
        int rankDistFromCentre = std::max(3 - cordA.rank, cordA.rank - 4);

        centreManhattanDistance[squareA] = fileDistFromCentre + rankDistFromCentre;

        for (int squareB = 0; squareB < 64; squareB++) {
            Coord cordB = Board::getCoordFromIndex(squareB);

            int rankDistance = std::abs(cordA.rank - cordB.rank);
            int fileDistance = std::abs(cordA.file - cordB.file);
            
            orthogonalDistance[squareA][squareB] = fileDistance + rankDistance;
            kingDistance[squareA][squareB] = std::max(fileDistance, rankDistance);
        }
    }
}



