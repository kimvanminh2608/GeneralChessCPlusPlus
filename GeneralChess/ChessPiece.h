#pragma once
#include <iostream>
#include <vector>
using namespace std;
class ChessPiece
{
public:
	string _name;
	string _color;

	ChessPiece(string name, string color) {
		_name = name;
		_color = color;
	}

	virtual bool isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* dest, vector<vector<ChessPiece*>> _board) const = 0;
	bool isOpponent(const ChessPiece* other) const
	{
		return other != nullptr && other->_color != _color;
	}

	string toString() const
	{
		if (_color == "Black") {
			return "\033[31m" + _color.substr(0, 1) + _name.substr(0, 1) /*+ "\033[0m"*/; // Red for black pieces
		}
		else {
			return _color.substr(0, 1) + _name.substr(0, 1);
		}
	}
};