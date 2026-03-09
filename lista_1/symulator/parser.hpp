#pragma once
#include <fstream>
#include <nlohmann/json.hpp>
#include "model.hpp"

class Parser {
public:
    static bool load(const std::string& filename, MDPModel& model) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;
        nlohmann::json j; file >> j;

        model.T = j["simulation"]["T"];
        model.alpha = j["simulation"]["alpha"];
        model.numTrials = j["simulation"]["num_trials"];

        model.stateNames = j["states"]["names"].get<std::vector<std::string>>();
        model.terminalCosts = j["states"]["terminal_costs"].get<std::vector<double>>();
        model.strategy = j["states"]["strategy"].get<std::vector<int>>();
        model.initialState = j["states"]["initial_index"].get<int>();
        model.numStates = (int)model.stateNames.size();

        int nActions = j["actions"].size();
        model.numActions = nActions;
        model.actionNames.resize(nActions);
        model.actionCosts.resize(nActions);
        model.transitions.resize(nActions);

        for (int a = 0; a < nActions; ++a) {
            model.actionNames[a] = j["actions"][a]["name"];
            model.actionCosts[a] = j["actions"][a]["costs_per_state"].get<std::vector<double>>();
            model.transitions[a] = j["actions"][a]["transitions"].get<std::vector<std::vector<double>>>();
        }
        return true;
    }
};
