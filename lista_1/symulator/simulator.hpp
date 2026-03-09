#pragma once
#include <random>
#include "model.hpp"
#include "printer.hpp"

class Simulator {
private:
    MDPModel model;
    std::mt19937_64 rng;

public:
    Simulator(const MDPModel& m) : model(m) {
        std::random_device rd;
        rng.seed(rd());
    }

    double run(bool verbose = false) {
        int stateIdx = model.initialState;
        double totalCost = 0.0;
        double discount = 1.0;

        if (verbose) Visualizer::printHeader();

        for (int t = 0; t < model.T; ++t) {
            int actionIdx = model.strategy[stateIdx];
            
            std::discrete_distribution<int> dist(
                model.transitions[actionIdx][stateIdx].begin(),
                model.transitions[actionIdx][stateIdx].end()
            );
            
            int nextStateIdx = dist(rng);
            double aCost = model.actionCosts[actionIdx][stateIdx];
            double tCost = model.terminalCosts[nextStateIdx];
            double stepCost = (aCost + tCost) * discount;
            totalCost += stepCost;

            if (verbose) {
                Visualizer::printStep(t+1, model.stateNames[stateIdx], model.actionNames[actionIdx], 
                                     aCost, model.stateNames[nextStateIdx], tCost, stepCost, totalCost);
            }

            stateIdx = nextStateIdx;
            discount *= model.alpha;
        }
        return totalCost;
    }
};