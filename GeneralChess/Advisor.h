#pragma once
#include "ChessPiece.h"
class Advisor : public ChessPiece
{
public:
	Advisor(string color) : ChessPiece("Advisor", color) {}
    bool isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* dest, vector<vector<ChessPiece*>> _board) const override
    {
        // Define the palace
        int palaceStartRow = (_color == "red") ? 7 : 0;
        int palaceEndRow = (_color == "red") ? 9 : 2;
        int palaceStartCol = 3;
        int palaceEndCol = 5;

        // Check if the move in palace
        if (endRow < palaceStartRow || endRow > palaceEndRow || endCol < palaceStartCol || endCol > palaceEndCol) {
            return false;
        }

        // Advisor can only move one step X
        if (abs(startRow - endRow) != 1 || abs(startCol - endCol) != 1) {
            return false; 
        }

        // Check if the destination
        if (dest != nullptr && !isOpponent(dest)) {
            return false;
        }

        return true; // Valid move
    }
};

