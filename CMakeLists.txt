cmake_minimum_required(VERSION 3.10)

project(UltimateTicTacToe)

set(CMAKE_CXX_STANDARD 14)

# Enable OpenMP
find_package(OpenMP)
if (OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

include_directories(src)

add_executable(SerialUltimateTicTacToe
    src/main.cpp
    src/Board.h
    src/Board.cpp
    src/UltimateBoard.h
    src/UltimateBoard.cpp
    src/Game.h
    src/Game.cpp
    src/agents/Agent.h
    src/agents/HumanPlayer.h
    src/agents/HumanPlayer.cpp
    src/agents/Minimax.h
    src/agents/MinimaxSerial.cpp
    src/agents/MCTS.h
    src/agents/MCTSSerial.cpp
    src/agents/RandomAgent.h
    src/agents/RandomAgent.cpp
    vendor/cxxopts/cxxopts.hpp
)

add_executable(ParallelUltimateTicTacToe
    src/main.cpp
    src/Board.h
    src/Board.cpp
    src/UltimateBoard.h
    src/UltimateBoard.cpp
    src/Game.h
    src/Game.cpp
    src/agents/Agent.h
    src/agents/HumanPlayer.h
    src/agents/HumanPlayer.cpp
    src/agents/Minimax.h
    src/agents/MinimaxParallel.cpp
    src/agents/MCTS.h
    src/agents/MCTSParallel.cpp
    src/agents/RandomAgent.h
    src/agents/RandomAgent.cpp
    vendor/cxxopts/cxxopts.hpp
)

# Link OpenMP if found
if (OpenMP_CXX_FOUND)
    target_link_libraries(ParallelUltimateTicTacToe PUBLIC OpenMP::OpenMP_CXX)
endif()
