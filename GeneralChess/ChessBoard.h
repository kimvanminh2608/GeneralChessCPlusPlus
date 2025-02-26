#pragma once
#include "ChessPiece.h"
#include "Chariot.h"
#include "Horse.h"
#include "Cannon.h"
#include "Soldier.h"
#include "General.h"
#include "Elephant.h"
#include "Advisor.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
class ChessBoard
{
private:
	//Array vector 2D
	vector<vector<ChessPiece*>> _board;
public:
	ChessBoard()
	{
		_board.resize(10, vector<ChessPiece*>(9, nullptr));
		initializeBoard();
	}

	~ChessBoard()
	{
		for (auto& row : _board)
		{
			for (auto& piece : row)
			{
				delete piece;
			}
		}
	}

	//Create ChessPiece 8x8
	//0 1 2 3 4 5 6 7 8 9
	//1 x m t s g s t m x
	//2
	//3   p           p
	//4 t   t   t   t   t
	//5
	//6
	//7 t   t   t   t   t
	//8   p		      p
	//9
	//10 X M T S G S T M X
	void initializeBoard()
	{
		// Initialize the board with nullptr
		for (int row = 0; row < 10; ++row) {
			for (int col = 0; col < 9; ++col) {
				_board[row][col] = nullptr;
			}
		}

		// Place the pieces for Black
		_board[0] = { new Chariot("Black"), new Horse("Black"), new Elephant("Black"), new Advisor("Black"),
					  new General("Black"), new Advisor("Black"), new Elephant("Black"), new Horse("Black"), new Chariot("Black") };
		_board[2][1] = new Cannon("Black");
		_board[2][7] = new Cannon("Black");
		_board[3][0] = new Soldier("Black");
		_board[3][2] = new Soldier("Black");
		_board[3][4] = new Soldier("Black");
		_board[3][6] = new Soldier("Black");
		_board[3][8] = new Soldier("Black");

		// Place the pieces for Red
		_board[9] = { new Chariot("Red"), new Horse("Red"), new Elephant("Red"), new Advisor("Red"),
					  new General("Red"), new Advisor("Red"), new Elephant("Red"), new Horse("Red"), new Chariot("Red") };
		_board[7][1] = new Cannon("Red");
		_board[7][7] = new Cannon("Red");
		_board[6][0] = new Soldier("Red");
		_board[6][2] = new Soldier("Red");
		_board[6][4] = new Soldier("Red");
		_board[6][6] = new Soldier("Red");
		_board[6][8] = new Soldier("Red");

	}

	//Print ChessBoard
	void printBoard()
	{
		for (int row = 0; row < 10; ++row)
		{
			for (int subRow = 0; subRow < 3; subRow++) // Each cell is 3 rows high
			{
				if (subRow == 1) {
					cout << (9 - row) << " "; // Print row numbers on the middle sub-row
				}
				else {
					cout << "  "; // Indent for non-middle sub-rows
				}
				for (int col = 0; col < 9; ++col)
				{
					string bgColor = "\033[103m"; // yellow background
					if (_board[row][col] != nullptr && subRow == 1)
					{
						cout << bgColor << " " << _board[row][col]->toString() << "   \033[0m";
					}
					else {
						cout << bgColor << " " << "  " << "   \033[0m";
					}
				}
				cout << endl;
			}
		}
		cout << "    a     b     c     d     e     f     g     h     i" << endl;
	}

	// Check if any piece can attack the king
	bool isKingInCheck(string color) 
	{
		int kingRow, kingCol;
		// Find the king's position
		for (int row = 0; row < 10; ++row)
		{
			for (int col = 0; col < 9; ++col)
			{
				if (_board[row][col] != nullptr && _board[row][col]->_name == "General" && _board[row][col]->_color == color)
				{
					kingRow = row;
					kingCol = col;
					break;
				}
			}
		}
		// Check if any opponent piece can attack the king
		for (int row = 0; row < 10; ++row)
		{
			for (int col = 0; col < 9; ++col)
			{
				ChessPiece* piece = _board[row][col];
				if (piece != nullptr && piece->_color != color)
				{
					if (piece->isValidMove(row, col, kingRow, kingCol, _board[kingRow][kingCol], _board)) {
						return true;
					}
				}
			}
		}
		return false;
	}

	// Simulate a move to check if it results in check
	bool simulateMoveAndCheck(string start, string end, string color)
	{
		int startRow = 9 - (start[1] - '0');
		int startCol = start[0] - 'a';
		int endRow = 9 - (end[1] - '0');
		int endCol = end[0] - 'a';

		ChessPiece* piece = _board[startRow][startCol];
		ChessPiece* dest = _board[endRow][endCol];

		// Simulate the move
		_board[endRow][endCol] = piece;
		_board[startRow][startCol] = nullptr;

		bool kingInCheck = isKingInCheck(color);

		// Undo the move
		_board[startRow][startCol] = piece;
		_board[endRow][endCol] = dest;

		return kingInCheck;
	}

	void movePiece(string start, string end)
	{
		int startRow = 9 - (start[1] - '0');
		int startCol = start[0] - 'a';
		int endRow = 9 - (end[1] - '0');
		int endCol = end[0] - 'a';

		ChessPiece* piece = _board[startRow][startCol];
		ChessPiece* dest = _board[endRow][endCol];
		cout << "Moving " << piece->_name << endl;

		if (piece != nullptr && piece->isValidMove(startRow, startCol, endRow, endCol, dest, _board))
		{
			string playerColor = piece->_color;
			bool test = simulateMoveAndCheck(start, end, playerColor);
			if (!test)
			{
				_board[endRow][endCol] = piece;
				_board[startRow][startCol] = nullptr;

				if (isKingInCheck(piece->_color == "Red" ? "Black" : "Red"))
				{
					cout << "Check!" << endl;
				}
			}
			else
			{
				cout << "Invalid move! Your King would be in check." << endl;
			}
		}
		else
		{
			cout << "Invalid move!" << endl;
		}
	}
};

