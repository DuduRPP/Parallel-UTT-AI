#include "Game.h"
#include "agents/Agent.h"
#include "agents/HumanPlayer.h"
#include "agents/MCTS.h"
#include "agents/Minimax.h"
#include "agents/RandomAgent.h"
#include "../vendor/cxxopts/cxxopts.hpp"

#include <stdio.h>
#include <omp.h>

Agent* parseAgent(cxxopts::ParseResult result, std::string name) {
    Agent* player;
    std::string type = result[name].as<std::string>();

    if(type == "mcts"){
        if(result.count("iterations"))
            player = new MCTS(result["iterations"].as<int>());
        else
            player = new MCTS();
    }
    else if(type == "minimax"){
        if(result.count("depth"))
            player = new MinimaxAgent(result["depth"].as<int>());
        else
            player = new MinimaxAgent();
    }
    else if(type == "random"){
        player = new RandomAgent();
    }
    else{
        std::cout << "Invalid player " << (char)toupper(name[0]) << ", options are: mcts, minimax or random" << std::endl;
        exit(1);
    }
    return player;
}

int main(int argc, char* argv[]) {

    cxxopts::Options options(argv[0], "");

    options.add_options()
        ("h,help", "Display this help message")
        ("t,threads","Number of threads in parallel implementation",cxxopts::value<int>())
        ("a,analysis","Analyze a position",cxxopts::value<std::string>())
        ("x,xplayer","Define X player AI, can be: mcts, minimax or random. If omitted, human player will be used",cxxopts::value<std::string>())
        ("o,oplayer","Define O player AI, can be: mcts, minimax or random. If omitted, human player will be used",cxxopts::value<std::string>())
        ("i,iterations","Define number of iteractions for MCTS model. Default: 50000",cxxopts::value<int>())
        ("d,depth","Define level of depth for Minimax model. Default: 6",cxxopts::value<int>());

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if(result.count("threads")){
        omp_set_num_threads(result["threads"].as<int>());
    }

    Agent* playerX;
    Agent* playerO;

    if (result.count("xplayer")){
        playerX = parseAgent(result, "xplayer");
    }
    if (result.count("oplayer")){
        playerO = parseAgent(result, "oplayer");
    }


    if (result.count("analysis")){
        if(!result.count("xplayer"))
            playerX = new MCTS();
        if(!result.count("oplayer"))
            playerO = new MCTS();

        Game game(playerX, playerO);
        game.analyze(result["analysis"].as<std::string>());
    } else {
        if(!result.count("xplayer"))
            playerX = new HumanPlayer();
        if(!result.count("oplayer"))
            playerO = new HumanPlayer();

        Game game(playerX, playerO);
        game.play();
    }

    return 0;
}
