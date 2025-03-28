
#include "Game.hpp"
#include "Renderer.hpp"
#include "InputHandler.hpp"
#include "Board.hpp"
#include "raylib.h"
#include <bitset>
#include <iostream>
#include "PreCompMoveData.hpp"


void Game::run(){
    InitAudioDevice();
    Renderer::LoadTextures(); // Load the textures for the pieces
    std::string startfen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    Board board(startfen); // Initialize the board with the starting FEN
    
    // Coord coordFromIdx = Board::getCoordFromIndex(0);
    // std::cout << "Rank: " << coordFromIdx.rank << " File: " << coordFromIdx.file << std::endl;
    // int rectX = coordFromIdx.file * SQUARE_SIZE + BOARD_X;
    // int rectY = (BOARD_SIZE - 1 - coordFromIdx.rank) * SQUARE_SIZE + BOARD_Y;

    //print the bitboards
    // for (int i = 0; i < 12; i++){
    //     std::cout << "Piece: " << i << std::endl;
    //     Board::printBoard(board.bitboardState[i]);
    // }
   
    
    while (!WindowShouldClose()) { // Main game loop
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        
        // DrawText("Raylib is working!", 250, 280, 20, DARKBLUE); // Test to check raylib compilation is working and cmake
        Renderer::drawBoard(); // Draw the chess board
        Renderer::drawCoords(); // Draw the coordinates for the chess board
        
        PreCompMoveData::Initialize(); // Initialize the precomputed move data

        InputHandler::HandleInput(board); // Handle the input for the game
        InputHandler::HighlightSquare(); // Highlight the square when the mouse is over it
        Renderer::drawPieces(board); // Draw the pieces on the chess board
        //DrawRectangle(rectX, rectY, 100, 100, RED);
        //board.genMovesForSquare(8);
        if (IsKeyPressed(KEY_R)){
            Board::loadFen(board, startfen);
    
        }

        if (IsKeyPressed(KEY_Q)){
            break;
        }

        EndDrawing();
    }

    Renderer::UnloadTextures(); // Unload the textures for the pieces
    CloseWindow(); // Close window
}