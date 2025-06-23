#include "Minimax.h"
#include <cstdio>
#include <vector>
#include <algorithm>

double MinimaxAgent::getMove(UltimateBoard &game, int &boardRow, int &boardCol, int &cellRow, int &cellCol) {
    int bestValue = std::numeric_limits<int>::min();
    Move bestMove{-1, -1, -1, -1};
    std::vector<Move> validMoves = game.getValidMoves();
    player = game.currentPlayer;

    #pragma omp parallel for
    for (int i = 0; i < validMoves.size(); i++) {
        Move move = validMoves[i];
        UltimateBoard newGame = game;
        newGame.makeMove(bestMove);
        int moveValue = minimax(newGame, 1, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

        #pragma omp critical 
        {
            if (moveValue > bestValue) {
                bestValue = moveValue;
                bestMove = move;
            }
        }
    }

    boardRow = bestMove.boardRow;
    boardCol = bestMove.boardCol;
    cellRow = bestMove.cellRow;
    cellCol = bestMove.cellCol;

    return bestValue;
}

int MinimaxAgent::minimax(UltimateBoard &game, int depth, bool isMaximizingPlayer, int alpha, int beta) {
    if (game.gameOver || depth == maxDepth) {
        return evaluate(game);
    }

    std::vector<Move> validMoves = game.getValidMoves();

    if (isMaximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (const Move &move : validMoves) {
            UltimateBoard newGame = game;
            newGame.makeMove(move);
            int eval = minimax(newGame, depth + 1, false, alpha, beta);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, maxEval);
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (const Move &move : validMoves) {
            UltimateBoard newGame = game;
            newGame.makeMove(move);
            int eval = minimax(newGame, depth + 1, true, alpha, beta);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, minEval);
            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }
}

int MinimaxAgent::evaluate(const UltimateBoard &game) {
    // Simple evaluation function: 1000 for win, -1000 for loss, 0 for draw and for undecided we sum 10 for each board won(center +10) and subtract 10 for each board lost
    if (game.checkUltimateWinner()) {
        return (game.currentPlayer == player) ?  1000 : -1000;
    } else if (game.checkUltimateTie()) {
        return 0;
    }
    int score = 0;
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            if(game.boards[i][j].winner == player){
                score += 10;
                if(i == 1 && j == 1){
                    score += 10;
                }
            }
            else if(game.boards[i][j].winner != NONE){
                score += -10;
                if(i == 1 && j == 1){
                    score += -10;
                }
            }
        }
    }
    return score;
}