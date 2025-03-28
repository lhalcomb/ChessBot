#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <raylib.h>
#include "Board.hpp"


class InputHandler {
    public: 
        
        static void HandleInput(Board &board);
        static void getBoardPosition(Vector2 mousePos, int& rank, int& file);
        
        static void HighlightSelectedSquare(Vector2 mousePos, int& rank, int& file);
        static void HighlightSquare();
    private:
        static bool isPieceSelected;
        static int selectedRank; static int selectedFile; // Rank and file of the selected piece
        static bool isSquareHighlighted;
        static int highlightRank; static int highlightFile; // Rank and file of the highlighted square
        Board &board;
        
};

#endif //INPUTHANDLER_HPP