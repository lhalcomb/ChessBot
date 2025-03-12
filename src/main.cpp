#include <iostream> // Standard input/output stream objects (cin/cout), this will be for debugging purposes
#include <string> // String objects, this will be for debugging purposes


// Raylib library
#include "raylib.h"

// header files for the game objects and functions
#include "Game.hpp"

int main() {
    // Window dimensions
    const int screenWidth = 1490;
    const int screenHeight = 1280;

    // Initialize window
    InitWindow(screenWidth, screenHeight, "ChessBot");

    SetTargetFPS(60); // Limit to 60 FPS
    
    Game game;
    game.run(); // Run the game

    return 0; // Close window and return 0

} 