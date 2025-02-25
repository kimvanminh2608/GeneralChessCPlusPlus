#pragma once
#include "ChessPiece.h"
class Soldier : public ChessPiece
{
public:
	Soldier(string color) : ChessPiece("Soldier", color) {}
    bool isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* dest, vector<vector<ChessPiece*>> _board) const override
    {
        // Check if the destination is occupied by an ally piece
        if (dest != nullptr && !isOpponent(dest)) {
            return false; // Destination is occupied by an ally piece
        }

        // Define the river row based on the color of the Soldier
        int riverRow = (_color == "red") ? 4 : 5;

        // Check if the Soldier is moving forward
        if (_color == "red") {
            if (startRow <= riverRow) {
                // Before crossing the river, can only move forward
                if (endRow == startRow - 1 && endCol == startCol) {
                    return true;
                }
            }
            else {
                // After crossing the river, can move forward or sideways
                if ((endRow == startRow - 1 && endCol == startCol) || (endRow == startRow && abs(endCol - startCol) == 1)) {
                    return true;
                }
            }
        }
        else {
            if (startRow >= riverRow) {
                // Before crossing the river, can only move forward
                if (endRow == startRow + 1 && endCol == startCol) {
                    return true;
                }
            }
            else {
                // After crossing the river, can move forward or sideways
                if ((endRow == startRow + 1 && endCol == startCol) || (endRow == startRow && abs(endCol - startCol) == 1)) {
                    return true;
                }
            }
        }

        return false; // Invalid move
    }
};

