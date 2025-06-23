#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Agent.h"

class HumanPlayer : public Agent {
    public:
        double getMove(UltimateBoard &game, int &boardRow, int &boardCol, int &cellRow, int &cellCol) override;
};

#endif // HUMANPLAYER_H
