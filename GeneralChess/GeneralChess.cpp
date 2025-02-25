#include <iostream>
#include "ChessBoard.h"
using namespace std;
int main()
{
    ChessBoard board;
    board.printBoard();
    string start, end;

    while (true) {
        cout << "Enter the start position : ";
        cin >> start;
        cout << "Enter the end position : ";
        cin >> end;
        board.movePiece(start, end);
        board.printBoard();
    }
}