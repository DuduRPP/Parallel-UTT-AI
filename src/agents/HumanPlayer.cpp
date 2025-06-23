#include "HumanPlayer.h"

double HumanPlayer::getMove(UltimateBoard &game, int &boardRow, int &boardCol, int &cellRow, int &cellCol) {
    if (game.nextBoardRow == -1) {
        std::cout << "Player " << (char)game.currentPlayer << ", choose any board (row col): ";
        std::cin >> boardRow >> boardCol;
    } else {
        boardRow = game.nextBoardRow;
        boardCol = game.nextBoardCol;
        std::cout << "Player " << (char)game.currentPlayer << ", you must play on board (" << boardRow << ", " << boardCol << ")" << std::endl;
    }

    std::cout << "Enter cell (row col): ";
    std::cin >> cellRow >> cellCol;

    return 0;
}
