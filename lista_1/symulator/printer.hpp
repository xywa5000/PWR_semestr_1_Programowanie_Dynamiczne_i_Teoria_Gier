#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "model.hpp"

class Visualizer {
public:
    // Komunikaty o błędach i statusie
    static void printError(const std::string& msg) {
        std::cerr << "[BLAD] " << msg << std::endl;
    }

    static void printInfo(const std::string& msg) {
        std::cout << "[INFO] " << msg << std::endl;
    }

    static void printSimulationStart(int trials, bool verbose) {
        if (verbose) {
            std::cout << "Uruchamianie pojedynczej sciezki (Tryb Verbose)..." << std::endl;
        } else {
            std::cout << "Rozpoczynanie symulacji Monte Carlo (" << trials << " prob)..." << std::endl;
        }
    }

    // Tryb Verbose (Tabela)
    static void printHeader() {
        std::cout << std::string(110, '-') << std::endl;
        std::cout << std::left 
                  << std::setw(6)  << "Krok" 
                  << std::setw(15) << "Stan Pocz." 
                  << std::setw(20) << "Akcja" 
                  << std::setw(12) << "K. Akcji" 
                  << std::setw(15) << "Stan Konc."
                  << std::setw(10) << "K. Stanu" 
                  << std::setw(15) << "K. Zdysk."
                  << "Suma" << std::endl;
        std::cout << std::string(110, '-') << std::endl;
    }

    static void printStep(int t, const std::string& startS, const std::string& act, 
                         double aC, const std::string& endS, double sC, 
                         double discStep, double total) {
        std::cout << std::left 
                  << std::setw(6)  << t 
                  << std::setw(15) << startS 
                  << std::setw(20) << act 
                  << std::setw(12) << std::fixed << std::setprecision(2) << aC 
                  << std::setw(15) << endS
                  << std::setw(10) << sC 
                  << std::setw(15) << discStep 
                  << std::fixed << std::setprecision(4) << total << std::endl;
    }

    // Tryb Monte Carlo (Pasek postępu)
    static void printProgressBar(int current, int total, int width = 50) {
        float progress = (float)current / total;
        int pos = width * progress;

        std::cout << "\rProgress: [";
        for (int i = 0; i < width; ++i) {
            if (i < pos) std::cout << "#";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << " %" << std::flush;
        
        if (current == total) std::cout << std::endl;
    }

    // Wynik końcowy
    static void printFinalResult(double avgCost) {
        std::cout << "\n" << std::string(40, '=') << std::endl;
        std::cout << "SREDNI KOSZT OCZEKIWANY: " << std::fixed << std::setprecision(6) << avgCost << std::endl;
        std::cout << std::string(40, '=') << std::endl;
    }

    // Wyświetlanie optymalnej strategii
    static void printOptimalStrategy(const OptimalStrategy& opt, const MDPModel& model) {
        std::cout << "\n=== WYZNACZONA OPTYMALNA STRATEGIA (T=" << model.T << ") ===\n";
        std::cout << std::left << std::setw(10) << "Krok";
        for(const auto& name : model.stateNames) std::cout << std::setw(20) << "Stan: " + name;
        std::cout << "\n" << std::string(10 + 20 * model.numStates, '-') << "\n";

        for (int t = 0; t < model.T; ++t) {
            std::cout << std::left << std::setw(10) << t + 1;
            for (int i = 0; i < model.numStates; ++i) {
                int actionIdx = opt.strategyTable[t][i];
                std::cout << std::setw(20) << model.actionNames[actionIdx];
            }
            std::cout << "\n";
        }
        std::cout << "\nOczekiwany koszt calkowity: " << std::fixed << std::setprecision(4) 
                  << opt.valueTable[0][model.initialState] << "\n";
    }
};