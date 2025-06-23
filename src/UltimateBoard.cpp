#include "UltimateBoard.h"

UltimateBoard::UltimateBoard() : currentPlayer(PLAYER_X), nextBoardRow(-1), nextBoardCol(-1), gameOver(false), winner(NONE){}

void UltimateBoard::switchPlayer() {
    currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
}

bool UltimateBoard::validMove(Move move) const {
    int boardRow = move.boardRow;
    int boardCol = move.boardCol;
    int cellRow = move.cellRow;
    int cellCol = move.cellCol;
    return !((nextBoardRow != -1 && (boardRow != nextBoardRow || boardCol != nextBoardCol)) || 
        boards[boardRow][boardCol].grid[cellRow][cellCol] != NONE || 
        boards[boardRow][boardCol].winner != NONE);
}

bool UltimateBoard::makeMove(Move move) {
    
    if (!validMove(move)){
        return false;
    }

    int boardRow = move.boardRow;
    int boardCol = move.boardCol;
    int cellRow = move.cellRow;
    int cellCol = move.cellCol;

    boards[boardRow][boardCol].grid[cellRow][cellCol] = currentPlayer;

    if (boards[boardRow][boardCol].isWinner(currentPlayer))
        boards[boardRow][boardCol].winner = currentPlayer;

    nextBoardRow = cellRow;
    nextBoardCol = cellCol;

    if (boards[nextBoardRow][nextBoardCol].winner != NONE || boards[nextBoardRow][nextBoardCol].isFull()) {	
        nextBoardRow = nextBoardCol = -1; // Allow the next player to choose any board if the target board is full
    }

    if (checkUltimateWinner()) {
        gameOver = true;
        winner = currentPlayer;
    } else if (checkUltimateTie()) {
        gameOver = true;
        winner = NONE;
    } else {
        switchPlayer();
    }

    return true;
}

bool UltimateBoard::checkUltimateWinner() const {
    for (int i = 0; i < SIZE; ++i)
        if (boards[i][0].winner == currentPlayer && boards[i][1].winner == currentPlayer && boards[i][2].winner == currentPlayer)
            return true;

    for (int j = 0; j < SIZE; ++j)
        if (boards[0][j].winner == currentPlayer && boards[1][j].winner == currentPlayer && boards[2][j].winner == currentPlayer)
            return true;

    if (boards[0][0].winner == currentPlayer && boards[1][1].winner == currentPlayer && boards[2][2].winner == currentPlayer)
        return true;

    if (boards[0][2].winner == currentPlayer && boards[1][1].winner == currentPlayer && boards[2][0].winner == currentPlayer)
        return true;

    return false;
}

bool UltimateBoard::checkUltimateTie() const {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (!boards[i][j].isFull() && boards[i][j].winner == NONE)
                return false;
        }
    }
    return true;
}

void UltimateBoard::printBoard() const {
    for (int br = 0; br < SIZE; ++br) {
        for (int cr = 0; cr < SIZE; ++cr) {
            for (int bc = 0; bc < SIZE; ++bc) {
                for (int cc = 0; cc < SIZE; ++cc) {
                    if(boards[br][bc].winner == PLAYER_X)
                        std::cout << "X";
                    else if(boards[br][bc].winner == PLAYER_O)
                        std::cout << "O";
                    else
                        std::cout << boards[br][bc].grid[cr][cc];
                    if (cc < SIZE - 1)
                        std::cout << "|";
                }
                std::cout << "   ";
            }
            std::cout << std::endl;
        }
        if (br < SIZE - 1)
            std::cout << "-----   -----   -----" << std::endl;
    }
}


std::vector<Move> UltimateBoard::getValidMoves() const {
    if (nextBoardRow != -1 && nextBoardCol != -1) {
        // Check moves only in the specified board
        return getValidMoves(nextBoardRow, nextBoardCol);
    }

    // Check moves in all boards
    std::vector<Move> validGlobalMoves;
    std::vector<Move> validBoardMoves;
    for (int boardRow = 0; boardRow < SIZE; ++boardRow) {
        for (int boardCol = 0; boardCol < SIZE; ++boardCol) {
            if (boards[boardRow][boardCol].winner == NONE) {
                validBoardMoves = getValidMoves(boardRow, boardCol);
                validGlobalMoves.insert(validGlobalMoves.end(), validBoardMoves.begin(), validBoardMoves.end());
            }
        }
    }
    return validGlobalMoves;
}

std::vector<Move> UltimateBoard::getValidMoves(int boardRow, int boardCol) const {
    std::vector<Move> validMoves;
    Board board = boards[boardRow][boardCol];

    for (int cellRow = 0; cellRow < SIZE; ++cellRow) {
        for (int cellCol = 0; cellCol < SIZE; ++cellCol) {
            if (board.grid[cellRow][cellCol] == NONE) {
                validMoves.push_back(Move{boardRow, boardCol, cellRow, cellCol});
            }
        }
    }
    return validMoves;
}