#ifndef PRECOMP_MOVE_DATA_HPP
#define PRECOMP_MOVE_DATA_HPP

#include <array>
#include <vector>
#include <cstdint>



class PreCompMoveData {
public:
    // Move direction offsets (N, S, W, E, NW, SE, NE, SW)
    static constexpr std::array<int, 8> directionOffsets = {1, -1, 8, -8, 7, -7, 9, -9};

    // Edge distances (squares to edge of board in each direction)
    static std::array<std::array<int, 8>, 64> numSquaresToEdge;

    // Precomputed move lists (square -> possible destinations)
    using MoveList = std::vector<uint8_t>;
    static std::array<MoveList, 64> knightMoves; // Knights have max 8 moves
    static std::array<MoveList, 64> kingMoves;   // Kings have max 8 moves
    static std::array<std::vector<int>, 64> rookMovesList;
    static std::array<std::vector<int>, 64> bishopMovesList;
    static std::array<std::vector<int>, 64> queenMovesList;

    // Precomputed attack data
    using PawnAttackDir = std::array<uint8_t, 2>;
    static std::array<PawnAttackDir, 64> pawnAttackDirections; 
    static std::array<std::vector<int>, 64> pawnAttacksWhite;
    static std::array<std::vector<int>, 64> pawnAttacksBlack;

    // Attack bitboards (square -> bitboard of attackable squares)
    using AttackBitBoards = std::array<uint64_t, 64>;
    static AttackBitBoards knightAttacks;
    static AttackBitBoards kingAttacks;
    static std::array<AttackBitBoards, 2> pawnAttacks; // [0] for white, [1] for black

    // Sliding piece move bitboards (square -> bitboard of legal moves)
    using SlidingPieces = std::array<uint64_t, 64>;
    static SlidingPieces rookMoves;
    static SlidingPieces bishopMoves;
    static SlidingPieces queenMoves;


    // Lookup table for move directions
    static int directionLookup[127];

    //Distance variables for evaluation
    static int orthogonalDistance[64][64];
    static int kingDistance[64][64];
    static int centreManhattanDistance[64];

    static void Initialize(); // Function to populate the tables

private:
    PreCompMoveData() = default; // Prevent instantiation
};


#endif // PRECOMP_MOVE_DATA_HPP
