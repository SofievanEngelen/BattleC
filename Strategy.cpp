//
// Created by Sofie van Engelen on 25/11/2024.
//
#include <vector>
#include "Strategy.h"
#include "global.h"

std::pair<int, int> RandomPlay::getNextMove() {
    if (availableMoves.empty()) {
        throw std::runtime_error("No more available moves!");
    }

    // Select a random move from availableMoves.
    const int index = std::rand() % availableMoves.size();
    std::pair<int, int> move = availableMoves[index];

    // Remove the selected move to avoid repeating it.
    availableMoves.erase(availableMoves.begin() + index);

    return move;
}


std::pair<int, int> HuntTarget::getNextMove() {
    // Target Mode: If we have moves queued in the targetQueue, use them first.
    if (!targetQueue.empty()) {
        std::pair<int, int> move = targetQueue.back();
        targetQueue.pop_back(); // Remove the move after selecting it.
        return move;
    }

    // If no targets in queue, fallback to Hunt Mode.
    targetMode = false; // Reset to Hunt Mode.

    if (availableMoves.empty()) {
        throw std::runtime_error("No more available moves!");
    }

    // Select a random move from availableMoves.
    const int index = std::rand() % availableMoves.size();
    std::pair<int, int> move = availableMoves[index];

    // Remove the selected move to avoid repeating it.
    availableMoves.erase(availableMoves.begin() + index);

    return move;
}

std::pair<int, int> Parity::getNextMove() {
    if (parityMoves.empty()) {
        throw std::runtime_error("No more available moves in parity strategy!");
    }

    // Select a random move from parityMoves.
    const int index = std::rand() % parityMoves.size();
    std::pair<int, int> move = parityMoves[index];

    // Remove the selected move to avoid repeating it.
    parityMoves.erase(parityMoves.begin() + index);

    return move;
}

void printHeatmap(const std::vector<std::vector<int>>& heatmap) {
    for (const auto& row : heatmap) {          // Loop over each row
        for (const auto& cell : row) {        // Loop over each cell in the row
            std::cout << cell << " ";         // Print the value of the cell
        }
        std::cout << std::endl;               // Newline after each row
    }
}

void calculateProbability(const std::vector<std::vector<int>> *offenceHeatmap, const std::vector<int>& remainingShips) {

    for (const int shipSize : remainingShips) {
        // Horizontal placements.
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j <= 10 - shipSize; ++j) {
                bool valid = true;
                for (int k = 0; k < shipSize; ++k) {
                    printHeatmap(*offenceHeatmap);
                    // std::cout << printHeatmap(offenceHeatmap) << std::endl;
                    // if (offenceHeatmap[i][j + k] == -1) {  // -1 indicates a miss.
                    //     valid = false;
                    //     break;
                    // }
                }
                // if (valid) {
                //     for (int k = 0; k < shipSize; ++k) {
                //         offenceHeatmap[i][j + k]++;
                //     }
                // }
            }
        }
        //
        // // Vertical placements.
        // for (int i = 0; i <= 10 - shipSize; ++i) {
        //     for (int j = 0; j < 10; ++j) {
        //         bool valid = true;
        //         for (int k = 0; k < shipSize; ++k) {
        //             if (offenceHeatmap[i + k][j] == -1) {
        //                 valid = false;
        //                 break;
        //             }
        //         }
        //         if (valid) {
        //             for (int k = 0; k < shipSize; ++k) {
        //                 offenceHeatmap[i + k][j]++;
        //             }
        //         }
        //     }
        // }
    }
}
