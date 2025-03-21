
#include "Game.hpp"
#include "Renderer.hpp"
#include "InputHandler.hpp"
#include "Board.hpp"
#include "raylib.h"
#include <bitset>
#include <iostream>


void Game::run(){
    InitAudioDevice();
    Renderer::LoadTextures(); // Load the textures for the pieces
    std::string startfen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    Board board(startfen); // Initialize the board with the starting FEN
    

    // for (int color = 0; color < 2; color++){
    //     for (int pieceType = 0; pieceType < 6; pieceType++){
    //         Board::printBoard(Board::bitboard[color][pieceType]);
    //     }

    // }
    // std::bitset<64> pawnPlacement(0x000000000000FF00ULL | 0x00FF000000000000ULL);
    // std::bitset<64> BlackPawnBit(Board::bitboard[1][5]);
    // std::cout << BlackPawnBit << std::endl;
    // Board::printBoard(Board::bitboard[0][5]);
    // Board::printBoard(BlackPawnBit.to_ullong());

    Board::loadFen(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    
    while (!WindowShouldClose()) { // Main game loop
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        
        // DrawText("Raylib is working!", 250, 280, 20, DARKBLUE); // Test to check raylib compilation is working and cmake
        Renderer::drawBoard(); // Draw the chess board
        Renderer::drawCoords(); // Draw the coordinates for the chess board
        
        
        InputHandler::HandleInput(); // Handle the input for the game
        InputHandler::HighlightSquare(); // Highlight the square when the mouse is over it
        Renderer::drawPieces(); // Draw the pieces on the chess board
        
        if (IsKeyPressed(KEY_R)){
            Board::loadFromFEN(startfen);
    
        }

        if (IsKeyPressed(KEY_Q)){
            break;
        }

        EndDrawing();
    }

    Renderer::UnloadTextures(); // Unload the textures for the pieces
    CloseWindow(); // Close window
}