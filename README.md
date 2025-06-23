[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/IwHO6ydp)

# Parallel Ultimate Tic Tac Toe AI

[Ultimate Tic Tac Toe](https://en.wikipedia.org/wiki/Ultimate_tic-tac-toe) is a game derived from the traditional tic-tac-toe, where each of the 9 cells of the main board is also a tic-tac-toe board. Players make their moves in the smaller games, and the current move determines where the opponent must make their next move. The idea of this project is to develop, using C++ and OpenMP, two intelligent agents for decision-making in an Ultimate Tic Tac Toe board: one that will execute a parallel version of the minimax algorithm (with alpha-beta pruning) and the other running a parallel version of the Monte Carlo Tree Search algorithm.

## Compiling & Running

First you have to generate the build system using [CMake](https://cmake.org/). Make sure you have it installed! You will also need an OpenMP compatible compiler. If you use Linux, you are good to go. For MacOS users, you can install the OpenMP libraries via [Homebrew](https://brew.sh/) with the following command:

```bash
# Only for MacOS users
brew install libomp
```

Then, run the following commands:

```bash
# Where the build will live
mkdir build && cd build

# Generate the Makefiles
cmake -DCMAKE_BUILD_TYPE=Release ..
```

Having done that, still inside the `build` directory, run `make` to compile everything. Finally, you can execute the serial and parallel versions like so:

```bash
./SerialUltimateTicTacToe
./ParallelUltimateTicTacToe
```

Or, from the root directory of the repo:

```bash
build/SerialUltimateTicTacToe
build/ParallelUltimateTicTacToe
```

If no argument is provided, the game will assume both with X and O are human players. To change one (or both) players to an intelligent agents, pass the `-x <agent>` or `-o <agent>` arguments when running the program. For example:

```bash
# Run the parallel version with X as a MCTS AI and O as a Minimax AI
./ParallelUltimateTicTacToe -x mcts -o minimax
```

Run `./ParallelUltimateTicTacToe --help` to see all available options.

## Evaluation

You can evaluate the performance of our solution by running the script `check.py`. All you have to do is run the following command:

```bash
python3 check.py
```

Alternatively, you can run one of the files in the `tests/` directory. Doing so allows you to manually set the execution parameters i.e. the agent you wish to test, the number of iteration/depth of the search tree and number of threads. The downside is you have to manually run both programs and compare the results. From the root of the repository:

```bash
# Runs test 1 with MCTS agent and 100000 iterations
build/SerialUltimateTicTacToe -a tests/1.in -x mcts -i 100000
build/ParallelUltimateTicTacToe -a tests/1.in -x mcts -i 100000 -t 4
```
"# Parallel-UTT-AI" 
