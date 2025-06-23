#include "RandomAgent.h"

double RandomAgent::getMove(UltimateBoard &game, int &boardRow, int &boardCol, int &cellRow, int &cellCol) {
    std::vector<Move> validMoves = game.getValidMoves();
    if (!validMoves.empty()) {
        int randomIndex = std::rand() % validMoves.size();
        Move randomMove = validMoves[randomIndex];
        boardRow = randomMove.boardRow;
        boardCol = randomMove.boardCol;
        cellRow = randomMove.cellRow;
        cellCol = randomMove.cellCol;
    }
    return 0;
}
