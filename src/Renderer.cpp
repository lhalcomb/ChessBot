#include "Renderer.hpp"
#include <iostream>
#include "raylib.h"
#include "Game.hpp"
#include "Board.hpp"




const int OFFSET_TEXT = 20;

const Color lightBrown = {196, 164, 132, 255};
const Color darkBrown = {101, 67, 33, 255};

Sound Renderer::moveSound;
Wave Renderer::moveWave;
std::vector<SoundSnippet> Renderer::gameSounds; 


Texture2D Renderer::chessPieces;
std::unordered_map<char, Rectangle> Renderer::pieceRects;
Font garamondFont;
Vector2 position;

void Renderer::LoadTextures(){
    chessPieces = LoadTexture("assets/chessPieces.png");
    garamondFont = LoadFont("assets/garamond.ttf");
    moveWave = LoadWave("audio/chessSounds_fixed.wav");

    if (chessPieces.id == 0){
        std::cerr << "Error loading chess pieces texture" << std::endl;
    }else{
        std::cout << "Chess pieces texture loaded successfully" << std::endl;
    }
    if (moveWave.frameCount == 0){
        std::cerr << "Error loading move wave" << std::endl;
    }else{
        std::cout << "Move wave loaded successfully" << std::endl;
        moveSound = LoadSoundFromWave(moveWave);
    }


    float pieceWidth = chessPieces.width / 6;
    float pieceHeight = chessPieces.height / 2;

    //map chess pieces to fen notation
    pieceRects = {
        {'K', {0 * pieceWidth, 0, pieceWidth, pieceHeight}}, // White King
        {'Q', {1 * pieceWidth, 0, pieceWidth, pieceHeight}}, // White Queen
        {'B', {2 * pieceWidth, 0, pieceWidth, pieceHeight}}, // White Rook
        {'N', {3 * pieceWidth, 0, pieceWidth, pieceHeight}}, // White Bishop
        {'R', {4 * pieceWidth, 0, pieceWidth, pieceHeight}}, // White Knight
        {'P', {5 * pieceWidth, 0, pieceWidth, pieceHeight}}, // White Pawn
        {'k', {0 * pieceWidth, pieceHeight, pieceWidth, pieceHeight}}, // Black King
        {'q', {1 * pieceWidth, pieceHeight, pieceWidth, pieceHeight}}, // Black Queen
        {'b', {2 * pieceWidth, pieceHeight, pieceWidth, pieceHeight}}, // Black Rook
        {'n', {3 * pieceWidth, pieceHeight, pieceWidth, pieceHeight}}, // Black Bishop
        {'r', {4 * pieceWidth, pieceHeight, pieceWidth, pieceHeight}}, // Black Knight
        {'p', {5 * pieceWidth, pieceHeight, pieceWidth, pieceHeight}}  // Black Pawn
    };

    gameSounds = {
        {0.0f, 1.0f}, //Start
        {1.0f, 1.5f}, //Move
        {3.0f, 4.0f}, //Capture
        {4.0f, 5.0f}, //Castle
        {5.0f, 7.0f}, //StaleMate 
        {7.0f, 8.0f}, //Check 
        {9.0f, 10.0f}, //Checkmate
        {10.0f, 11.0f} //Gameover
    };

}

void Renderer::UnloadTextures(){
    UnloadTexture(chessPieces);
    UnloadFont(garamondFont);
    UnloadSound(moveSound);
    UnloadWave(moveWave);
}

void Renderer::PlayGameSound(int soundIndex){
    if (soundIndex < 0 || soundIndex >= gameSounds.size()) {
        std::cerr << "Invalid sound index" << std::endl;
        return;
    }

    SoundSnippet snippet = gameSounds[soundIndex];

    int startFrame = snippet.startTime * moveWave.sampleRate;
    int endFrame = startFrame + (snippet.duration * moveWave.sampleRate);

   
    // Ensure the end frame does not exceed the total frame count
    if (endFrame > moveWave.frameCount) {
        endFrame = moveWave.frameCount;
    }

    // Crop the wave to the desired snippet
    Wave snippetWave = WaveCopy(moveWave);
    WaveCrop(&snippetWave, startFrame, endFrame);

    // Load the sound from the cropped wave
    Sound snippetSound = LoadSoundFromWave(snippetWave);

   PlaySound(snippetSound);

    
}

void Renderer::drawBoard(){
    DrawRectangle(BOARD_X - 50, 
                  BOARD_Y - 50,
                  BOARD_SIZE * SQUARE_SIZE + 100, 
                  BOARD_SIZE * SQUARE_SIZE + 100, 
                  DARKBROWN);
    for (int rank = 0; rank < BOARD_SIZE; rank++){
        for (int file = 0; file < BOARD_SIZE; file++){
            Color squareColor = ((rank + file) % 2 == 0) ? darkBrown : lightBrown;
            DrawRectangle(
                BOARD_X + file * SQUARE_SIZE, 
                BOARD_Y + rank * SQUARE_SIZE, 
                SQUARE_SIZE, SQUARE_SIZE, squareColor);
        } 
    }
}

void Renderer::drawCoords(){
    const char* files = "ABCDEFGH";
    const char* ranks = "12345678";

    int fontSize = 28.0f;
    int spacing = 2.0f;

    for (int i = 0; i < BOARD_SIZE; i++){
        // Center the file labels horizontally
        position = {BOARD_X + i * SQUARE_SIZE + SQUARE_SIZE / 2 - MeasureTextEx(garamondFont, "A", fontSize, spacing).x / 2,
            BOARD_Y + BOARD_SIZE * SQUARE_SIZE + OFFSET_TEXT};
        DrawTextEx(garamondFont, TextFormat("%c", files[i]), position, fontSize, spacing, BLACK);

// Center the rank labels vertically
        position = {BOARD_X - OFFSET_TEXT - MeasureTextEx(garamondFont, "8", fontSize, spacing).x,
            BOARD_Y + i * static_cast<float>(SQUARE_SIZE) + static_cast<float>(SQUARE_SIZE) / 2 - fontSize / 2};
        DrawTextEx(garamondFont, TextFormat("%c", ranks[BOARD_SIZE - i - 1]), position, fontSize, spacing, BLACK);
    }
}

void Renderer::drawPieces(){
    // Draw the pieces on the board
    
    int rank = 0; int file = 0;
    int squareSize = SQUARE_SIZE;

    for (int rank = 0; rank < BOARD_SIZE; rank++){
        for (int file = 0; file < BOARD_SIZE; file++){
            char piece = Board::board[rank][file];
            if (piece != '.'){
                if (pieceRects.find(piece) != pieceRects.end()){
                    Rectangle pieceRect = pieceRects[piece];
    
                    // Define the destination rectangle where the piece will be drawn
                    Rectangle destRect = {
                        BOARD_X + file * squareSize, 
                        BOARD_Y + rank * squareSize, 
                        static_cast<float>(squareSize), // Scale width to fit square
                        static_cast<float>(squareSize)  // Scale height to fit square
                    };

                    Vector2 origin = { 0, 0 }; // No rotation, so origin stays at (0,0)
                    
                    DrawTexturePro(chessPieces, pieceRect, destRect, origin, 0.0f, WHITE);
                }
            }
            
        }
    }

};