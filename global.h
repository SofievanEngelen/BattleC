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
inline std::unordered_map<std::string, int> patterns{{"checkerboard", 1}, {"edge-heavy", 2},{"cross", 3}};
inline std::unordered_map<std::string, int> placementStrategies{{"input", 1},{"random", 2},{"prob-density", 3},{"hidden-pattern", 4}};
inline std::unordered_map<std::string, int> attackStrategies{{"random", 1},{"prob-density", 2},{"hidden-pattern", 3}};


#endif //GLOBAL_H
