//
// Created by Sofie van Engelen on 15/11/2024.
//

#include "Player.h"
#include "global.h"

void displayBoards(const Board& defenceBoard, const Board &offenceBoard) {
    std::cout << "Your defence board: \n";
    defenceBoard.display(true);

    std::cout << "\nYour offence board: \n";
    offenceBoard.display(false);
}

std::tuple<int, int> pickNextMove(const std::pair<int, int> &boardSize, const std::string &strategy) {
    switch (attackStrategies[strategy]) {
        case 1:
        default:
            return {randomInt(0, boardSize.first - 1), randomInt(0, boardSize.second - 1)};
        // case 2:
        //
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
    displayBoards(this->board, opponent.board);
}

void AIPlayer::takeTurn(Player &opponent) const {
    while (true) {
        if (const auto [row, col] {pickNextMove(this->board.getSize(), this->attackStrategy)}; !opponent.getBoard().shoot(row, col)) {
            displayBoards(this->board, opponent.getBoard());
            continue;
        }
        break;
    }
    displayBoards(this->board, opponent.getBoard());
}


