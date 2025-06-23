#include "MCTS.h"
#include <cstdio>
#include <vector>
#include <limits>
#include <cmath>
#include <ctime>

MCTSNode::MCTSNode(UltimateBoard state, int boardRow, int boardCol, int cellRow, int cellCol, MCTSNode* parent)
    : state(state), boardRow(boardRow), boardCol(boardCol), cellRow(cellRow), cellCol(cellCol), parent(parent), wins(0), visits(0), isFullyExpanded(false) {}

MCTSNode::~MCTSNode() {
    for (MCTSNode* child : children)
        delete child;
}

bool MCTSNode::isTerminal() const {
    return state.gameOver;
}

void MCTSNode::expand() {
    std::vector<Move> moves = state.getValidMoves();
    for (Move move : moves) {
        UltimateBoard newState = state;
        newState.makeMove(move);
        children.push_back(new MCTSNode(newState, move.boardRow, move.boardCol, move.cellRow, move.cellCol, this));
    }
    isFullyExpanded = true;
}

MCTSNode* MCTSNode::bestChild() const {
    MCTSNode* best = nullptr;
    const double explorationWeight = 2.0;
    double bestValue = -std::numeric_limits<double>::infinity();
    for (MCTSNode* child : children) {
        double ucb1 = (double)child->wins / (child->visits + 1) +
                      explorationWeight * std::sqrt(2 * std::log(visits + 1) / (child->visits + 1));
        if (ucb1 > bestValue) {
            bestValue = ucb1;
            best = child;
        }
    }
    return best;
}


void MCTS::analyze(UltimateBoard &game, MCTSNode* root) {
    Player agentSign = game.currentPlayer;
    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            for (int i = 0; i < iterations; ++i) {
                MCTSNode* node = treeTraversal(root);
                #pragma omp task firstprivate(node)
                {
                    double simulationResult = rollout(node, agentSign);
                    backpropagation(node, simulationResult);
                }
            }
        }
    }
}

double MCTS::getMove(UltimateBoard &game, int &boardRow, int &boardCol, int &cellRow, int &cellCol) {
    MCTSNode root(game, -1, -1, -1, -1, nullptr);

    std::srand(10);

    analyze(game, &root);

    MCTSNode* best = root.bestChild();
    boardRow = best->boardRow;
    boardCol = best->boardCol;
    cellRow = best->cellRow;
    cellCol = best->cellCol;
    return (double)root.wins / (double)(root.visits + 1);

}

MCTSNode* MCTS::treeTraversal(MCTSNode* node) {
    while (!node->isTerminal()) {
        if (!node->isFullyExpanded){
            node->expand();
            node->visits++;
            node->children[0]->visits++;
            return node->children[0];
        }
        else {
            node->visits++;
            node = node->bestChild();
            node->visits++;
        }
    }
    return node;
}

double MCTS::rollout(MCTSNode* node, Player agentSign) {
    UltimateBoard state = node->state;
    while (!state.gameOver) {
        std::vector<Move> moves = state.getValidMoves();
        Move randomMove = moves[std::rand() % moves.size()];
        state.makeMove(randomMove);
    }
    if(state.winner == agentSign)
        return 1.0;
    else if (state.winner == NONE)
        return 0.0;
    else
        return -1.0;
}

void MCTS::backpropagation(MCTSNode* node, double simulationResult) {
    while (node != nullptr) {
        #pragma omp critical
        {
            node->wins += simulationResult;
        }
        node = node->parent;
    }
}
