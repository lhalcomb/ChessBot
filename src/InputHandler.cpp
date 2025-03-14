#include "InputHandler.hpp"
#include "Game.hpp"
#include <iostream>
#include "Renderer.hpp"
#include "Board.hpp"
#include "Move.hpp"
#include <vector>




bool InputHandler::isPieceSelected = false;
int InputHandler::selectedRank = -1;
int InputHandler::selectedFile = -1;
int InputHandler::highlightRank = -1;
int InputHandler::highlightFile = -1;
bool InputHandler::isSquareHighlighted = false;



void InputHandler::HighlightSelectedSquare(Vector2 mousePos, int& rank, int& file){
    // Highlight selected square when handling input

    //std::cout << "Highlighting square..." << std::endl;
    getBoardPosition(mousePos, rank, file);
    bool Bounded = (rank >= 0 && rank < BOARD_SIZE && file >= 0 && file < BOARD_SIZE);
    if ((Bounded)){
        //DrawRectangle(BOARD_X + file * SQUARE_SIZE, BOARD_Y + rank * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, RED);
        highlightRank = rank;
        highlightFile = file;
        isSquareHighlighted = true;
    }


}
void InputHandler::HandleInput()
{
    /*

    Lot going on here, so let's break it down:
        1. Check if the left mouse button is pressed
        2. Get the mouse position
        3. Convert the mouse position to board position
        4. Check if the board position is within bounds
        5. If the piece is not selected, select the piece
        6. If the piece is selected, move the piece

    */
    //std::cout << "Handling input..." << std::endl;
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        
        Vector2 mousePos = GetMousePosition();
    
        int rank, file;
        getBoardPosition(mousePos, rank, file);
       

        bool Bounded = (rank >= 0 && rank < BOARD_SIZE && file >= 0 && file < BOARD_SIZE);
        if (Bounded) {
            if (!isPieceSelected) {
                if (Board::getPiece(rank, file) != '.') {
                    isPieceSelected = true;
                    selectedRank = rank;
                    selectedFile = file;
                    HighlightSelectedSquare(mousePos, rank, file);
                }
            } else {
                char piece = Board::getPiece(selectedRank, selectedFile);
                //HighlightSelectedSquare(mousePos, rank, file, isPieceSelected);

                if (piece != '.') {
                    std::string newFen = Move::movePiece(selectedRank, selectedFile, rank, file);
                    Board::loadFromFEN(newFen);
                    isPieceSelected = false;
                    isSquareHighlighted = false;
                    Renderer::drawPieces(); 

                    Renderer::PlayGameSound(1);

                }
            }
    
    }
}
};

void InputHandler::HighlightSquare(){
    if (isSquareHighlighted){
        DrawRectangle(BOARD_X + highlightFile * SQUARE_SIZE, BOARD_Y + highlightRank * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, RED);
    }
};


void InputHandler::getBoardPosition(Vector2 mousePos, int& rank, int& file){
    // Convert mouse position to board position
    int BoardX = BOARD_X; 
    int BoardY = BOARD_Y;

    file = (mousePos.x - BoardX) / SQUARE_SIZE;
    //rank = BOARD_SIZE - (mousePos.y - BoardY) / SQUARE_SIZE;
    rank = (mousePos.y - BoardY) / SQUARE_SIZE;

    //std::cout << "Rank: " << rank << " File: " << file << std::endl;
    if (file < 0 || file >= BOARD_SIZE || rank < 0 || rank >= BOARD_SIZE){
        rank = -1;
        file = -1;
    }

};