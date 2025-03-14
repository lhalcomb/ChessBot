
#include "Game.hpp"
#include "Renderer.hpp"
#include "InputHandler.hpp"
#include "Board.hpp"
#include "raylib.h"


void Game::run(){
    InitAudioDevice();
    Renderer::LoadTextures(); // Load the textures for the pieces
    std::string startfen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    Board board(startfen); // Initialize the board with the starting FEN
    Board::printBoard();
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