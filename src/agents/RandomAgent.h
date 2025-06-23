#ifndef RANDOMAGENT_H
#define RANDOMAGENT_H

#include "Agent.h"
#include "../UltimateBoard.h"
#include <cstdlib>
#include <ctime>

class RandomAgent : public Agent {
public:
    RandomAgent() { std::srand(std::time(0)); } // Seed the random number generator
    double getMove(UltimateBoard &game, int &boardRow, int &boardCol, int &cellRow, int &cellCol) override;
};

#endif // RANDOMAGENT_H
