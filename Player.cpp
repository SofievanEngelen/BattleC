//
// Created by Sofie van Engelen on 15/11/2024.
//

#include "Player.h"
#include "global.h"

void displayBoards(const Board& defenceBoard, const Board &offenceBoard) {
    std::cout << "Defence board:\t\t\t\t\t\t\t\t\t\t\tOffence board:" << std::endl;
    std::cout << "\tA\tB\tC\tD\tE\tF\tG\tH\tI\tJ\t\t\t\t\tA\tB\tC\tD\tE\tF\tG\tH\tI\tJ" << std::endl;
    for (int row{0}; row < defenceBoard.getSize().first; row++) {
        std::cout << row+1 << '\t' << defenceBoard.getRow(row, true) << "\t\t\t" << row+1 << '\t' << offenceBoard.getRow(row, false) << std::endl;
    }
}

std::tuple<int, int> pickNextMove(const std::pair<int, int> &boardSize, const attackStrategies strategy) {
    static std::vector<std::pair<int, int>> targetQueue; // Queue for Hunt Target strategy
    static std::vector probabilityMap(boardSize.first, std::vector(boardSize.second, 0));

    switch (strategy) {
        case 1: { // Random Strategy
            return {randomInt(0, boardSize.first - 1), randomInt(0, boardSize.second - 1)};
        }
        case 2: { // Hunt Target Strategy
            if (!targetQueue.empty()) {
                // Pick the next target from the queue
                auto nextTarget = targetQueue.back();
                targetQueue.pop_back();
                return nextTarget;
            }
            // Fallback to random if the queue is empty
            return {randomInt(0, boardSize.first - 1), randomInt(0, boardSize.second - 1)};
        }
        case 3: { // Parity Strategy
            int row, col;
            do {
                row = randomInt(0, boardSize.first - 1);
                col = randomInt(0, boardSize.second - 1);
            } while ((row + col) % 2 != 0); // Ensure checkerboard pattern
            return {row, col};
        }
        case 4: { // Probability Density Strategy
            // Calculate the maximum value in the probability map
            int maxProb = 0;
            std::vector<std::pair<int, int>> candidates;
            for (int i = 0; i < boardSize.first; ++i) {
                for (int j = 0; j < boardSize.second; ++j) {
                    if (probabilityMap[i][j] > maxProb) {
                        maxProb = probabilityMap[i][j];
                        candidates.clear();
                        candidates.emplace_back(i, j);
                    } else if (probabilityMap[i][j] == maxProb) {
                        candidates.emplace_back(i, j);
                    }
                }
            }
            // Pick a random candidate from the top-probability cells
            if (!candidates.empty()) {
                const auto& choice = candidates[randomInt(0, candidates.size() - 1)];
                return choice;
            }
            // Fallback to random if no candidates (shouldn't happen)
            return {randomInt(0, boardSize.first - 1), randomInt(0, boardSize.second - 1)};
        }
        default:
            throw std::runtime_error("Unknown strategy");
    }
}

void Player::takeTurn(Player &opponent) const {
    while (true) {
        std::cout << this->name << ", please enter your target coordinates (e.g. 'A5'): " << '\n';
        std::cout << "Moves: " << moves << std::endl;
        if (const auto [row, col] {getPositionInput()}; !opponent.board.shoot(row, col)) {
            displayBoards(this->board, opponent.board);
            continue;
        }
        break;
    }
    displayBoards(this->board, opponent.getBoard());
}

void AIPlayer::takeTurn(Player &opponent) const {
    static std::vector<std::pair<int, int>> targetQueue;

    while (true) {
        auto [row, col] = pickNextMove(this->board.getSize(), this->attackStrategy);

        std::cout << "The AI chose to hit " << static_cast<char>('A' + col) << row + 1 << "!" << std::endl;
        if (opponent.getBoard().shoot(row, col)) {
            // If the attack hits, add adjacent cells to the target queue (for Hunt Target)
            if (this->attackStrategy == HuntTarget) {
                for (const auto& [dx, dy] : std::vector<std::pair<int, int>>{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}) {
                    int newRow = row + dx;
                    int newCol = col + dy;
                    if (newRow >= 0 && newRow < board.getSize().first &&
                        newCol >= 0 && newCol < board.getSize().second &&
                        !opponent.getBoard().getGrid()[newRow][newCol].hit) {
                        targetQueue.emplace_back(newRow, newCol);
                        }
                }
            }
            break;
        }
    }
    displayBoards(this->board, opponent.getBoard());
}

void AIPlayer::setupShips() {
    board.setup(placementStrategy, defenceHeatmap);

    if (placementStrategy == ProbabilityDensityPlacement) {
        for (int i = 0; i < board.getSize().first; ++i) {
            for (int j = 0; j < board.getSize().second; ++j) {
                // Example initialization: Center positions have higher probabilities
                defenceHeatmap->at(i)[j] = std::min({i, j, board.getSize().first - 1 - i, board.getSize().second - 1 - j});
            }
        }
    }
}

