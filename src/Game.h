#ifndef GAME_H
#define GAME_H

#include "UltimateBoard.h"
#include "agents/Agent.h"
#include <stdio.h>

class Game {
    public:
        Game(Agent* playerX, Agent* playerO);
        void play();
        void analyze(std::string filePath);
    private:
        Agent* agentX;
        Agent* agentO;
        Agent* currentAgent;
};

#endif // GAME_H
