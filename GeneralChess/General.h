#pragma once
#include "ChessPiece.h"
class General : public ChessPiece
{
public:
	General(string color) : ChessPiece("General", color) {}
    bool isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* dest, vector<vector<ChessPiece*>> _board) const override
    {
        // Define the palace boundaries for both players
        int palaceStartRow = (_color == "red") ? 7 : 0;
        int palaceEndRow = (_color == "red") ? 9 : 2;
        int palaceStartCol = 3;
        int palaceEndCol = 5;

        // check move in square
        if (endRow < palaceStartRow || endRow > palaceEndRow || endCol < palaceStartCol || endCol > palaceEndCol) {
            return false;
        }

        // General can only move one step <-->
        if (abs(startRow - endRow) + abs(startCol - endCol) != 1) {
            return false;
        }

        
        if (dest != nullptr && !isOpponent(dest)) {
            return false;
        }

        return true; // Valid move
    }
};

