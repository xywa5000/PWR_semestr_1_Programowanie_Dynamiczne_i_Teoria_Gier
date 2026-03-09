#pragma once
#include <vector>
#include <limits>
#include "model.hpp"

class Optimizer {
public:
    static OptimalStrategy solve(const MDPModel& model) {
        int T = model.T;
        int S = model.numStates;
        int A = model.numActions;

        std::vector<std::vector<double>> V(T + 1, std::vector<double>(S, 0.0));
        std::vector<std::vector<int>> pi(T, std::vector<int>(S, 0));

        for (int t = T - 1; t >= 0; --t) {
            for (int i = 0; i < S; ++i) {
                double minExpectedCost = std::numeric_limits<double>::max();
                int bestAction = 0;

                for (int a = 0; a < A; ++a) {
                    double currentActionCost = model.actionCosts[a][i];
                    double expectedFuture = 0.0;

                    for (int j = 0; j < model.numStates; ++j) {
                        double p = model.transitions[a][i][j];
                        expectedFuture += p * (model.terminalCosts[j] + model.alpha * V[t+1][j]);
                    }
                    double total = currentActionCost + expectedFuture;

                    if (total < minExpectedCost) {
                        minExpectedCost = total;
                        bestAction = a;
                    }
                }
                V[t][i] = minExpectedCost;
                pi[t][i] = bestAction;
            }
        }

        return {pi, V};
    }
};