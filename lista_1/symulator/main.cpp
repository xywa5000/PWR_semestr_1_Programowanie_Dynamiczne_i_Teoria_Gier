#include "parser.hpp"
#include "simulator.hpp"
#include "printer.hpp"
#include "optimizer.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        Visualizer::printError("Uzycie: ./mdp_sim <file.json> [-v | -o]");
        return 1;
    }

    std::string configPath = argv[1];
    std::string mode = (argc > 2) ? argv[2] : "";

    MDPModel model;
    if (!Parser::load(configPath, model)) {
        Visualizer::printError("Blad wczytywania modelu.");
        return 1;
    }

    if (mode == "-o") {
        // TRYB OPTYMALIZACJI
        OptimalStrategy opt = Optimizer::solve(model);
        Visualizer::printOptimalStrategy(opt, model);
    } else {
        // TRYB SYMULACJI (Verbose lub Monte Carlo)
        bool verbose = (mode == "-v");
        Simulator sim(model);
        Visualizer::printSimulationStart(model.numTrials, verbose);
        
        if (verbose) {
            sim.run(true);
        } else {
            double grandTotal = 0.0;
            for (int i = 0; i < model.numTrials; ++i) {
                grandTotal += sim.run(false);
                if ((i+1) % (model.numTrials / 100) == 0) {
                    Visualizer::printProgressBar(i+1, model.numTrials);
                }
            }
            Visualizer::printFinalResult(grandTotal / model.numTrials);
        }
    }

    return 0;
}