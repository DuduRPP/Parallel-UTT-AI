#ifndef BOARD_H
#define BOARD_H

#include <iostream>

const int SIZE = 3;

enum Player { NONE = ' ', PLAYER_X = 'X', PLAYER_O = 'O' };

class Board {
    public:
        char grid[SIZE][SIZE];
        Player winner;

        Board();
        bool isFull() const;
        bool isWinner(Player player) const;
        void print() const;
};

#endif // BOARD_H
