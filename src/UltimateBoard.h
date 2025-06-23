#ifndef ULTIMATEBOARD_H
#define ULTIMATEBOARD_H

#include "Board.h"
#include <vector>


struct Move {
    int boardRow;
    int boardCol;
    int cellRow;
    int cellCol;
};

class UltimateBoard {
    public:
        Board boards[SIZE][SIZE];
        Player currentPlayer;
        int nextBoardRow, nextBoardCol;
        bool gameOver;
        Player winner;

        UltimateBoard();
        void switchPlayer();
        bool makeMove(Move move);
        bool validMove(Move move) const;
        std::vector<Move> getValidMoves() const;
        std::vector<Move> getValidMoves(int boardRow, int boardCol) const;
        bool checkUltimateWinner() const;
        bool checkUltimateTie() const;
        void printBoard() const;
};

#endif // ULTIMATEBOARD_H
