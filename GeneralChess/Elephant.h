#pragma once
#include "ChessPiece.h"
class Elephant : public ChessPiece
{
public:
	Elephant(string color) : ChessPiece("Elephant", color) {}
    bool isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* dest, vector<vector<ChessPiece*>> _board) const override
    {
        // Check if the move X two steps
        if (abs(startRow - endRow) != 2 || abs(startCol - endCol) != 2) {
            return false;
        }

        // Elephant cannot cross the river
        if ((_color == "red" && endRow < 5) || (_color == "black" && endRow > 4)) {
            return false;
        }

        if (dest != nullptr && !isOpponent(dest)) {
            return false;
        }

        // Check if there is a piece in the way
        int rowStep = (endRow > startRow) ? 1 : -1;
        int colStep = (endCol > startCol) ? 1 : -1;
        int row = startRow + rowStep;
        int col = startCol + colStep;
        ChessPiece* piece = _board[row][col];
        if (piece != nullptr) {
            return false;
        }

        return true; // Valid move
    }
};

