#ifndef AGENT_H
#define AGENT_H

#include "../UltimateBoard.h"
#include <iostream>

class Agent {
    public:
        virtual ~Agent() {}
        virtual double getMove(UltimateBoard &game, int &boardRow, int &boardCol, int &cellRow, int &cellCol) = 0;
};

#endif // AGENT_H
