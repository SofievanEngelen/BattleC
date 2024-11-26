#include <iostream>
#include <sstream>

#include "Player.h"

void printResults(const Player& P1, const Player& P2) {
    if (P1.hasLost() & P2.hasLost()) {std::cout << "It's a tie!\n";}
    else if (P1.hasLost()) {std::cout << "Player 2 wins!\n";}
    else if (P2.hasLost()) {std::cout << "Player 1 wins!\n";}
}

int main() {
    seedRandom(); // Ensure randomness is seeded globally

    constexpr std::pair boardSize{10, 10};

    const auto Board1 {Board(boardSize)};
    const auto Board2 {Board(boardSize)};

    auto Player1 {Player("Player 1", Board1)};
    auto Player2 {AIPlayer("Player 2", Board2, RandomPlacement, HuntTarget)};

    Player1.setupShips();
    Player2.setupShips();

    while (not Player1.hasLost() and not Player2.hasLost()) {
        Player1.takeTurn(Player2);
        Player2.takeTurn(Player1);
    }

    printResults(Player1, Player2);
}

