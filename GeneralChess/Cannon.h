#pragma once
#include "ChessPiece.h"
class Cannon : public ChessPiece
{
public:
	Cannon(string color) : ChessPiece("Cannon", color) {}
	bool isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* dest, vector<vector<ChessPiece*>> _board) const override
	{
        // Cannon move <-->
        if (startRow != endRow && startCol != endCol) {
            return false; 
        }

		// Check ally piece
        if (dest != nullptr && !isOpponent(dest)) {
            return false;
        }

        // Count the number of pieces between the start and end positions
        int pieceCount = 0;
        if (startRow == endRow) {
            // Horizontal move
            int colStep = (endCol > startCol) ? 1 : -1;
            for (int col = startCol + colStep; col != endCol; col += colStep) {
                if (_board[startRow][col] != nullptr) {
                    pieceCount++;
                }
            }
        }
        else {
            // Vertical move
            int rowStep = (endRow > startRow) ? 1 : -1;
            for (int row = startRow + rowStep; row != endRow; row += rowStep) {
                if (_board[row][startCol] != nullptr) {
                    pieceCount++;
                }
            }
        }

        // If the destination is empty, there should be no pieces in the way
        if (dest == nullptr) {
            return pieceCount == 0;
        }

        // If the destination is occupied by an opponent's piece, there should be exactly one piece in the way
        return pieceCount == 1;
	}
};

