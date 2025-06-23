#ifndef MCTS_H
#define MCTS_H

#include "Agent.h"
#include <vector>

class MCTSNode {
public:
    UltimateBoard state;
    int boardRow, boardCol, cellRow, cellCol;
    MCTSNode* parent;
    std::vector<MCTSNode*> children;
    int wins, visits;
    bool isFullyExpanded;

    MCTSNode(UltimateBoard state, int boardRow, int boardCol, int cellRow, int cellCol, MCTSNode* parent = nullptr);
    ~MCTSNode();
    bool isTerminal() const;
    MCTSNode* bestChild() const;
    void expand();
    // void update(double result);
};


class MCTS : public Agent {
    public:
        int iterations;
        MCTS(int i) {
            iterations = i;
        }
        MCTS() : MCTS(50000) {}
        void analyze(UltimateBoard &game, MCTSNode* root);
        double getMove(UltimateBoard &game, int &boardRow, int &boardCol, int &cellRow, int &cellCol) override;
    private:
        MCTSNode* treeTraversal(MCTSNode* root);
        double rollout(MCTSNode* node, Player agentSign);
        void backpropagation(MCTSNode* node, double simulationResult);
};

#endif // MCTS_H
