#ifndef MINIMAXAGENT_H
#define MINIMAXAGENT_H

#include "Agent.h"
#include "../UltimateBoard.h"
#include <limits>

class MinimaxAgent : public Agent {
public:
    MinimaxAgent(int d){
        maxDepth = d;
    }
    MinimaxAgent() : MinimaxAgent(6) {}
    double getMove(UltimateBoard &game, int &boardRow, int &boardCol, int &cellRow, int &cellCol) override;
private:
    int maxDepth; // Adjust depth as needed
    Player player;
    int minimax(UltimateBoard &game, int depth, bool isMaximizingPlayer, int alpha, int beta);
    int evaluate(const UltimateBoard &game);
};

#endif // MINIMAXAGENT_H
