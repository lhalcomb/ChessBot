
#include "Board.hpp"
#include "InputHandler.hpp"
#include <iostream>
#include <cstdint>
#include <bitset>
#include <unordered_map>
#include <Move.hpp>

#define BOARD_SIZE 8
 

Board::Board(const std::string& fen){
    
    loadFen(*this, fen);

}

//Helper Functions
constexpr int Board::rankIndex(int square) { return square >> 3;}
constexpr int Board::fileIndex(int square) { return square & 7;}
constexpr int Board::squareIndex(int rank, int file) { return rank * BOARD_SIZE + file;}

Coord Board::getCoordFromIndex(int squareIndex)
{
    return {rankIndex(squareIndex), fileIndex(squareIndex)};
}

void Board::setPiece(int color, int pieceType, int square){
    int index = color * 6 + pieceType;
    bitboardState[index] |= 1ULL << square;
}

void Board::removePiece(int color, int pieceType, int square){
    int index = color * 6 + pieceType;
    bitboardState[index] &= ~(1ULL << square);
}

bool Board::isSquareOccupied(int color, int pieceType, int square) const {
    int index = color * 6 + pieceType;
    return (bitboardState[index] & (1ULL << square)) != 0;
}

bool Board::isSquareOccupiedbyAnyPiece(Board &board, int square)
{
    for ( int color = 0; color < 2; ++color){
        for (int piece = 0; piece < 6; ++piece){
            if (board.isSquareOccupied(color, piece, square)){
                return true;
            }
        }
    }
    return false;
}

char Board::piecetoChar(int color, int pieceType)
{

    const char pieceChars[2][6] = {
        {'K', 'Q', 'B', 'N', 'R', 'P'},
        {'k', 'q', 'b', 'n', 'r', 'p'}};

    return pieceChars[color][pieceType];
};

//End Helper Functions


void Board::printBoard(u_int64_t bitboard){
    for (int rank = BOARD_SIZE - 1; rank >= 0; rank--){
        for (int file = 0; file < BOARD_SIZE; file++){
            int square = (7 - rank) * BOARD_SIZE + file;
            
            std::cout << ((bitboard & (1ULL << square)) ? "1" : "0") << " ";
            
        }
        std::cout << "Rank: " << rank + 1 << std::endl;
        std::cout << std::endl;
    }
    std::cout << "Bitboard (Hex): " << std::hex << bitboard << std::dec << std::endl;
    std::cout << std::endl;
}


std::string Board::generateFEN(Board &board){
    /* Generates a FEN string from the current bitboardState*/
    std::string fen = ""; //initialize fen string
    for (int rank = 7; rank >= 0; --rank){
        int empty = 0; //empty square counter
        for (int file = 0; file < 8; ++file){
            int square = squareIndex(rank, file); //get the square index
            char pieceChar = '.'; //default empty square
            for (int pieceIndex = 0; pieceIndex < 12; ++pieceIndex){
                if (board.bitboardState[pieceIndex] & (1ULL << square)){ //check all bitboards for a piece at this square
                    int color = pieceIndex / 6;
                    int pieceType = pieceIndex % 6;
                    pieceChar = piecetoChar(color, pieceType); //get the piece character
                    break;
                }
            }
            if (pieceChar == '.'){ //if empty square
                empty++; //increment empty square counter
            }else{
                if (empty > 0){ //if empty square counter is greater than 0
                    fen += std::to_string(empty); //add the empty square counter to the fen string
                    empty = 0; //reset empty square counter
                }
                fen += pieceChar; //add the piece to the fen string
            }
        }
        if (empty > 0){ //if empty square counter is greater than 0
            fen += std::to_string(empty); //add the empty square counter to the fen string
        }
        if (rank > 0){ //if not the last rank
            fen += "/"; //add / to the fen string
        }
    }
    fen += " w KQkq - 0 1"; //add turn, castling rights, en passant, halfmove clock, and fullmove number
    return fen; //return the fen string
}

void Board::loadFen(Board &board, const std::string &fenString) {
    board.bitboardState.fill(0);

    std::string fen = fenString;

    std::unordered_map<char, std::pair<int, int>> fenToPiece = {
        {'K', {Board::White, Board::King}}, {'Q', {Board::White, Board::Queen}}, {'B', {Board::White, Board::Bishop}}, 
        {'N', {Board::White, Board::Knight}}, {'R', {Board::White, Board::Rook}}, {'P', {Board::White, Board::Pawn}},
        {'k', {Board::Black, Board::King}}, {'q', {Board::Black, Board::Queen}}, {'b', {Board::Black, Board::Bishop}}, 
        {'n', {Board::Black, Board::Knight}}, {'r', {Board::Black, Board::Rook}}, {'p', {Board::Black, Board::Pawn}}
    };

    int rank = 7; int file = 0; 
    bool parsingBoard = true; size_t index = 0;
    for (char c: fen){
        if (c == '/'){
            rank--;
            file = 0;
        }else if (isdigit(c)){
            file += c - '0';
        }else if(c == ' '){
            parsingBoard = false;
            index++;
            break;
        }
        else{
            auto [color, pieceType] = fenToPiece[c];
            board.setPiece(color, pieceType, squareIndex(rank, file));
            file++;
            
        }
    }

    
    // if (!parsingBoard) {
    //         // After the board part, process turn (w or b)
    //         char turn = fen[index]; // 'w' or 'b'
    //         board.activeColor = (turn == 'w') ? Board::White : Board::Black;
    
    //         // Parse castling rights (KQkq)
    //         index++;
    //         std::string castlingRights = fen.substr(index, 4); // KQkq
    //         // Handle castling rights here...
    
    //         // Parse en passant (this part is '-' in your example)
    //         index += castlingRights.length() + 1;
    //         std::string enPassant = fen.substr(index, 2); // '-'
    //         // Handle en passant here...
    
    //         // Parse halfmove clock and fullmove number (not needed for loading pieces)
    //         index += enPassant.length() + 1;
    //         std::string halfMove = fen.substr(index, 1); // '0'
    //         std::string fullMove = fen.substr(index + 2, 1); // '1'
    //     }
    std::cout << "FEN: " << fen << std::endl;
    printBitBoard(board);
};

void Board::printBitBoard(Board &board){

    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            int square = squareIndex(rank, file);
            char pieceChar = '.'; // Default empty square

            // Check all bitboards for a piece at this square
            for (int pieceIndex = 0; pieceIndex < 12; ++pieceIndex) {
                //std::cout << "Piece Index: " << pieceIndex << "bitBoard: " << board.bitboardState[pieceIndex] << std::endl;
                if (board.bitboardState[pieceIndex] & (1ULL << square)) { // nice. 1000000100000000000000000000000000000000000000000000000000000000 & 1ULL << 0 = 1 equates to rook on a1
                    int color = pieceIndex / 6;
                    int pieceType = pieceIndex % 6;
                    pieceChar = piecetoChar(color, pieceType);
                    break;
                }
            }

            std::cout << pieceChar << " ";
        }
        std::cout << "\n"; // New line after each rank
    }
}

bool Board::getPieceAtSquare(int selectedSquare, int &color, int &pieceType)
{
    u_int64_t bit = 1ULL << selectedSquare;
    for (int c = 0; c < 2; ++c) {  // Iterate over colors (White, Black)
        for (int p = 0; p < 6; ++p) {  // Iterate over piece types (King, Queen, etc.)
            if (this->bitboardState[c * 6 + p] & bit) {
                color = c;
                pieceType = p;
                return true;
            }
        }
    }
    return false; // No piece found at this square
}

int Board::getPieceType(int square)
{
    uint64_t bit = 1ULL << square;
    for (int pieceType = 0; pieceType < 6; ++pieceType) {
        if (this->bitboardState[White * 6 + pieceType] & bit){ return pieceType;}
        if (this->bitboardState[Black * 6 + pieceType] & bit){ return pieceType;}
    }
    return -1;  // No piece found
}

int Board::getPieceColor(int square)
{
    uint64_t bit = 1ULL << square;
    for (int color = 0; color < 2; ++color) {
        for (int pieceType = 0; pieceType < 6; ++pieceType) {
            if (this->bitboardState[color * 6 + pieceType] & bit) {
                
                return color;
            }
            
        }
    }
    
    return -1;  // No piece found
}

void Board::genMovesForSquare(int square)
{
    std::vector<int> moves = Move::genLegalMoves(*this, square);
    for (int move: moves){
        std::cout << move << "-> " << square << std::endl;
    }

}
