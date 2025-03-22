#pragma once
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "raylib.h"
#include <string>
#include <unordered_map>
#include <vector> 
#include "Board.hpp"

struct SoundSnippet {
    float startTime;
    float duration;
};

const int BOARD_X = 620;
const int BOARD_Y = 100;

class Renderer {
    public:
        static void drawBoard();
        static void drawPieces(Board &board); // draw the pieces on the board
        static void drawCoords(); // draws coordinate placements for ranks & files
        static void LoadTextures(); // Load the textures for the pieces
        static void UnloadTextures(); // Unload the textures for the pieces
        static void PlayGameSound(int soundIndex); // Play the move sound
        
    
    private:
        static Texture2D chessPieces; // Texture for the pieces
        static std::unordered_map<char, Rectangle> pieceRects; // Map of the piece textures
        static Sound moveSound;
        static Wave moveWave;
        static std::vector<SoundSnippet> gameSounds;
};

extern Font garamondFont; // Font for the ranks and files
extern Vector2 position; // Position of the mouse

#endif // RENDERER_HPP