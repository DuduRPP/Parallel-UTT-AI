#include "Game.h"
#include <omp.h>
#include <cstdio>
#include <iostream>
#include <fstream>

Game::Game(Agent* agentX, Agent* agentO) : agentX(agentX), agentO(agentO), currentAgent(agentX) {}

void Game::play() {
    UltimateBoard board;
    int boardRow, boardCol, cellRow, cellCol;

    while (!board.gameOver) {
        board.printBoard();
        currentAgent->getMove(board, boardRow, boardCol, cellRow, cellCol);
        Move promptedMove{boardRow, boardCol, cellRow, cellCol};

        if (!board.makeMove(promptedMove)) {
            std::cout << "Invalid move. Try again." << std::endl;
            continue;
        }

        std::cout << "==========================\n";

        currentAgent = (currentAgent == agentX) ? agentO : agentX;
    }

    board.printBoard();
    std::cout << "Player " << (char)board.currentPlayer << " wins!" << std::endl;
}

void Game::analyze(std::string filePath){
    UltimateBoard board;
    int boardRow, boardCol, cellRow, cellCol;
    double t, score;

    std::ifstream inputFile(filePath);
    if (!inputFile) {
        std::cerr << "Unable to open file " << filePath << std::endl;
        return;
    }

    int numberOfMoves;
    inputFile >> numberOfMoves;
    for(int i = 0; i < numberOfMoves; i++){
        inputFile >> boardRow >> boardCol >> cellRow >> cellCol;
        Move move{boardRow,boardCol,cellRow,cellCol};
        board.makeMove(move);
        currentAgent = (currentAgent == agentX) ? agentO : agentX;
    }
    
    inputFile.close();
    
    t = omp_get_wtime();
    score = currentAgent->getMove(board, boardRow, boardCol, cellRow, cellCol);
    t = omp_get_wtime() - t;
    Move move{boardRow,boardCol,cellRow,cellCol};
    board.makeMove(move);
    std::cout << score << std::endl;
    std::cerr << t << std::endl;

}
