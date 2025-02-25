#pragma once
#include "ChessPiece.h"
class Horse : public ChessPiece
{
public:
	Horse(string color) : ChessPiece("Horse", color) {}
	bool isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* dest, vector<vector<ChessPiece*>> _board) const override
	{
		return ((abs(startRow - endRow) == 2 && abs(startCol - endCol) == 1) ||
			(abs(startRow - endRow) == 1 && abs(startCol - endCol) == 2))
			&& (dest == nullptr || isOpponent(dest));
	}
};

