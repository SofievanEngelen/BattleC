//
// Created by Sofie van Engelen on 25/11/2024.
//

#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>
#include <utility>
#include <ctime>
#include <stdexcept>

// Abstract Strategy Class
struct Strategy {
    virtual std::pair<int, int> getNextMove() = 0;
    virtual ~Strategy() {};  // Default virtual destructor
};

// Random Play Strategy
class RandomPlay final : public Strategy {
    std::vector<std::pair<int, int>> availableMoves;

public:
    explicit RandomPlay(const int boardSize) {
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                availableMoves.emplace_back(i, j);
            }
        }
        std::srand(std::time(nullptr));  // Seed random generator
    }

    std::pair<int, int> getNextMove() override;
};

// Hunt Target Strategy
class HuntTarget final : public Strategy {
    int boardSize;
    std::vector<std::pair<int, int>> availableMoves;
    std::vector<std::pair<int, int>> targetQueue;
    bool targetMode;

    bool isValidMove(const int x, const int y) const {
        return x >= 0 && x < boardSize && y >= 0 && y < boardSize;
    }

    void addAdjacentTargets(int x, int y) {
        if (isValidMove(x + 1, y)) targetQueue.emplace_back(x + 1, y);
        if (isValidMove(x - 1, y)) targetQueue.emplace_back(x - 1, y);
        if (isValidMove(x, y + 1)) targetQueue.emplace_back(x, y + 1);
        if (isValidMove(x, y - 1)) targetQueue.emplace_back(x, y - 1);
    }

public:
    explicit HuntTarget(const int size) : targetMode(false), boardSize(size) {
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                availableMoves.emplace_back(i, j);
            }
        }
    }

    std::pair<int, int> getNextMove() override;

    void processHit(const int x, const int y) {
        targetMode = true;
        addAdjacentTargets(x, y);
    }
};

// Parity Strategy
class Parity final : public Strategy {
    std::vector<std::pair<int, int>> parityMoves;
    int boardSize;

public:
    explicit Parity(const int size) : boardSize(size) {
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                if ((i + j) % 2 == 0) {
                    parityMoves.emplace_back(i, j);
                }
            }
        }
    }

    std::pair<int, int> getNextMove() override;
};

#endif // STRATEGY_H
