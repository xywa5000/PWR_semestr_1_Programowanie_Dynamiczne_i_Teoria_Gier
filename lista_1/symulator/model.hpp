#pragma once
#include <vector>
#include <string>

struct OptimalStrategy {
    std::vector<std::vector<int>> strategyTable;
    std::vector<std::vector<double>> valueTable;
};

struct MDPModel {
    int numStates;
    int numActions;
    int T;
    double alpha;
    int numTrials;
    int initialState; 

    std::vector<std::string> stateNames;
    std::vector<std::string> actionNames;
    std::vector<double> terminalCosts;    
    std::vector<std::vector<double>> actionCosts;
    std::vector<int> strategy;
    std::vector<std::vector<std::vector<double>>> transitions;
};