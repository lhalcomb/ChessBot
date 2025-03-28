#ifndef MAGIC_BITBOARDS_HPP
#define MAGIC_BITBOARDS_HPP

#include <cstdint>
#include <array> 


constexpr int BOARD_SIZE = 64;
constexpr int MAX_BISHOP_MASKS = 512; // 2^9 Maximum indices for bishop masks
constexpr int MAX_ROOK_MASKS = 4096; // 2^12 Maximum indices for rook masks

struct Magic{
    uint64_t mask;
    uint64_t magicNum;
    int shift;
    uint64_t* attackTable;
};

extern Magic rookMagics[BOARD_SIZE];
extern Magic bishopMagics[BOARD_SIZE];

extern uint64_t bishopAttacks[BOARD_SIZE][MAX_BISHOP_MASKS];
extern uint64_t rookAttacks[BOARD_SIZE][MAX_ROOK_MASKS];

void initMagicBitboards();
uint64_t getBishopAttacks(int square, uint64_t occupancy);
uint64_t getRookAttacks(int square, uint64_t occupancy);


#endif // MAGIC_BITBOARDS_HPP