#include "Board.h"

Board::Board() : winner(NONE) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            grid[i][j] = NONE;
}

bool Board::isFull() const {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (grid[i][j] == NONE)
                return false;
    return true;
}

bool Board::isWinner(Player player) const {
    for (int i = 0; i < SIZE; ++i)
        if (grid[i][0] == player && grid[i][1] == player && grid[i][2] == player)
            return true;

    for (int j = 0; j < SIZE; ++j)
        if (grid[0][j] == player && grid[1][j] == player && grid[2][j] == player)
            return true;

    if (grid[0][0] == player && grid[1][1] == player && grid[2][2] == player)
        return true;

    if (grid[0][2] == player && grid[1][1] == player && grid[2][0] == player)
        return true;

    return false;
}

void Board::print() const {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << grid[i][j];
            if (j < SIZE - 1)
                std::cout << "|";
        }
        std::cout << std::endl;
        if (i < SIZE - 1)
            std::cout << "-----" << std::endl;
    }
}
