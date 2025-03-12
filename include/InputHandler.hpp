#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <raylib.h>

class InputHandler {
    public: 
        static void HandleInput();
        static void getBoardPosition(Vector2 mousePos, int& rank, int& file);
    private:
        static bool isPieceSelected;
        static int selectedRank; static int selectedFile; // Rank and file of the selected piece
};

#endif //INPUTHANDLER_HPP