
#include "Board.hpp"
#include "InputHandler.hpp"
#include <iostream>
#include <cstdint>
#include <bitset>
#include <unordered_map>

#define BOARD_SIZE 8
 


u_int64_t Board::bitboard[2][6] = {0};  // Initialize all bitboards to 0
char Board::board[8][8] = {}; 

void Board::InitializeBitBoards(){

    // Pawns
    bitboard[White][Pawn]  = 0x000000000000FF00ULL;  // Rank 2
    bitboard[Black][Pawn]  = 0x00FF000000000000ULL;  // Rank 7

    std::bitset<64> WhitePawnBit(bitboard[White][Pawn]);
    std::bitset<64> BlackPawnBit(bitboard[Black][Pawn]);
    std::bitset<64> pawnPlacement(BlackPawnBit | WhitePawnBit);

    std::cout << "White Pawn Bitboard:" << WhitePawnBit << std::endl;
    std::cout << "Black Pawn Bitboard:" << BlackPawnBit << std::endl;
    std::cout << "Pawn Placement:" << pawnPlacement << std::endl;

    // Knights
    bitboard[White][Knight] = 0x0000000000000042ULL; // b1, g1
    bitboard[Black][Knight] = 0x4200000000000000ULL; // b8, g8

    // Bishops
    bitboard[White][Bishop] = 0x0000000000000024ULL; // c1, f1
    bitboard[Black][Bishop] = 0x2400000000000000ULL; // c8, f8

    // Rooks
    bitboard[White][Rook]   = 0x0000000000000081ULL; // a1, h1
    bitboard[Black][Rook]   = 0x8100000000000000ULL; // a8, h8

    // Queens
    bitboard[White][Queen]  = 0x0000000000000008ULL; // d1
    bitboard[Black][Queen]  = 0x0800000000000000ULL; // d8

    // Kings
    bitboard[White][King]   = 0x0000000000000010ULL; // e1
    bitboard[Black][King]   = 0x1000000000000000ULL; // e8

}



Board::Board(const std::string& fen){
    InitializeBitBoards();
    loadFromFEN(fen);

}


char Board::getPiece(int rank, int file){
    if (rank >= 0 && rank < 8 && file >= 0 && file < 8){
        return board[rank][file];
    }else{
        return '.';
    }

};


//Helper Functions
constexpr int Board::rankIndex(int square) { return square >> 3;}
constexpr int Board::fileIndex(int square) { return square & 7;}
constexpr int Board::squareIndex(int rank, int file) { return rank * BOARD_SIZE + file;}
constexpr int Board::IndexFromCoord(int file, int rank) { return rank * BOARD_SIZE + file; }

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
    return bitboardState[index] & (1ULL << square) != 0;
}

char Board::piecetoChar(int color, int pieceType)
{

    const char pieceChars[2][6] = {
        {'K', 'Q', 'B', 'N', 'R', 'P'},
        {'k', 'q', 'b', 'n', 'r', 'p'}};

    return pieceChars[color][pieceType];
};

//End Helper Functions

void Board::printBoard() {
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int f = 0; f < BOARD_SIZE; f++) {
            std::cout << board[r][f] << " ";
        }
        std::cout << std::endl;
    }
    
    //make for bitboards
}

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

void Board::loadFromFEN(const std::string &fenString) //
{   
    for (int r = 0; r < BOARD_SIZE; r++){
        for (int f = 0; f < BOARD_SIZE; f++){
            board[r][f] = '.';
        }
    }
    
    std::string fen = fenString; // copy the fen string
    int rank = 0; int file = 0; //init rank and file

    for (char c: fen){ //iterate through the fen string
        if (c == '/') { // if / that means new rank, increment rank and reset file
            rank++;
            file = 0;
        }
        else if (isdigit(c)){ // if digit, that means empty squares, move to next file in ABCDEFH
            file += c - '0'; // convert char to int
        }
        else if (isalpha(c)){ // if alphabet, that means piece
            board[rank][file] = c; // set the piece on the board
            file++; // move to next file
        }else{
            break; //accounts for castling rights in fen string
        }
    }
    printBoard();

      // make for bitboards
}

std::string Board::generateFEN()
{
    /*
    Generates a FEN string from the current board state
    */
    std::string fen = ""; //initialize fen string
    for (int r = 0; r < BOARD_SIZE; r++){
        int empty = 0; //empty square counter
        for (int f = 0; f < BOARD_SIZE; f++){
            char piece = board[r][f]; //get the piece on the board
            if (piece == '.'){ //if empty square
                empty++; //increment empty square counter
            }else{
                if (empty > 0){ //if empty square counter is greater than 0
                    fen += std::to_string(empty); //add the empty square counter to the fen string
                    empty = 0; //reset empty square counter
                }
                fen += piece; //add the piece to the fen string
            }
        }
        if (empty > 0){ //if empty square counter is greater than 0
            fen += std::to_string(empty); //add the empty square counter to the fen string
        }
        if (r < BOARD_SIZE - 1){ //if not the last rank
            fen += "/"; //add / to the fen string
        }
    }
    return fen; //return the fen string
   
    //make for bitboards

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
            int square = IndexFromCoord(file, rank);
            char pieceChar = '.'; // Default empty square

            // Check all bitboards for a piece at this square
            for (int pieceIndex = 0; pieceIndex < 12; ++pieceIndex) {
                if (board.bitboardState[pieceIndex] & (1ULL << square)) {
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
