//
// Created by Sofie van Engelen on 19/11/2024.
//

#ifndef GLOBAL_H
#define GLOBAL_H
#include <utility>
#include <locale>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

inline void seedRandom() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed with current time
        seeded = true;
    }
}


inline std::pair<int, int> convertPosition(const std::string &pos) {
    char column;
    int row;

    std::istringstream iss(pos);
    iss >> column >> row;
    return std::make_pair(row-1, std::toupper(column) - 65);
}

inline int randomInt(const int min, const int max) {
    return min + rand() % (max - min + 1);
}


inline std::pair<int, int> getPositionInput() {
    std::string position;
    std::cin >> position;
    const auto [fst, snd] = convertPosition(position);
    return std::pair<int, int>({fst, snd});
}

inline std::tuple<int, int, char> getPositionInputOrientation() {
    auto [fst, snd] {getPositionInput()};
    char orientation;
    std::cin >> orientation;
    const char orient = static_cast<char>(std::toupper(orientation));
    return std::tuple<int, int, char>({fst, snd, orient});
}

inline int moves {0};
inline constexpr int MAXATTEMPTS {1000};

inline std::unordered_map<std::string, char> shipIDs{{"Carrier", '1'}, {"Battleship", '2'}, {"Cruiser", '3'}, {"Submarine", '4'}, {"Destroyer", '5'}};

inline void updateHeatmap(std::vector<std::vector<int>>& heatmap, const int row, const int col) {
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            const int newRow = row + i;
            if (const int newCol = col + j; newRow >= 0 && newRow < heatmap.size() &&
                                            newCol >= 0 && newCol < heatmap[0].size()) {
                heatmap[newRow][newCol]++;
                }
        }
    }
}

enum class patterns {
    Checkerboard,
    EdgeHeavy,
    Cross
};

enum class placementStrategies {
    Automatic,
    ManualInput,
    RandomPlacement,
    ProbabilityDensityPlacement,
    HiddenPattern
};

enum class attackStrategies {
    RandomAttack,
    HuntTarget,
    Parity,
    ProbabilityDensityAttack
};

#endif //GLOBAL_H
