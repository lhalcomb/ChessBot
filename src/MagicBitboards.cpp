// #include "MagicBitboards.hpp"
// #include <iostream>


// /* Bitboard, LSB to MSB, a1 through h8:
//  * 56 - - - - - - 63
//  *  - - - - - - - -
//  *  - - - - - - - -
//  *  - - - - - - - -
//  *  - - - - - - - -
//  *  - - - - - - - -
//  *  - - - - - - - -
//  *  0 - - - - - - 7
//  */


// // Magic numbers and attack tables
// Magic rookMagics[BOARD_SIZE];
// Magic bishopMagics[BOARD_SIZE];

// uint64_t bishopAttacks[BOARD_SIZE][MAX_BISHOP_MASKS];
// uint64_t rookAttacks[BOARD_SIZE][MAX_ROOK_MASKS];

// // Precomputed Magic Numbers (Replace these with actual precomputed values)
// constexpr uint64_t precomputedBishopMagics[BOARD_SIZE] = {
//     // Add 64 precomputed magic numbers for bishops

// };

// constexpr uint64_t precomputedRookMagics[BOARD_SIZE] = {
//     // Add 64 precomputed magic numbers for rooks
// };

// // Placeholder for attack mask generation (these should be precomputed)
// uint64_t generateBishopMask(int square) {
//     uint64_t mask = 0;
//     // Compute diagonal attack mask for the given square
//     return mask;
// }

// uint64_t generateRookMask(int square) {
//     uint64_t mask = 0;
//     // Compute orthogonal attack mask for the given square
//     return mask;
// }

// // Function to initialize magic bitboards
// void initMagicBitboards() {
//     for (int square = 0; square < BOARD_SIZE; ++square) {
//         bishopMagics[square].magicNum = precomputedBishopMagics[square];
//         bishopMagics[square].mask = generateBishopMask(square);
//         bishopMagics[square].shift = 64 - __builtin_popcountll(bishopMagics[square].mask);
//         bishopMagics[square].attackTable = bishopAttacks[square];

//         rookMagics[square].magicNum = precomputedRookMagics[square];
//         rookMagics[square].mask = generateRookMask(square);
//         rookMagics[square].shift = 64 - __builtin_popcountll(rookMagics[square].mask);
//         rookMagics[square].attackTable = rookAttacks[square];
//     }
// }

// // Compute bishop moves using magic bitboards
// uint64_t getBishopAttacks(int square, uint64_t occupancy) {
//     occupancy &= bishopMagics[square].mask;
//     occupancy *= bishopMagics[square].magicNum;
//     occupancy >>= bishopMagics[square].shift;
//     return bishopMagics[square].attackTable[occupancy];
// }

// // Compute rook moves using magic bitboards
// uint64_t getRookAttacks(int square, uint64_t occupancy) {
//     occupancy &= rookMagics[square].mask;
//     occupancy *= rookMagics[square].magicNum;
//     occupancy >>= rookMagics[square].shift;
//     return rookMagics[square].attackTable[occupancy];
// }
