//
// Created by Sofie van Engelen on 15/11/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"
#include <string>
#include <utility>


class Player {
    std::string name;

protected:
    Board board;

public:
    virtual ~Player() = default;

    Player(std::string playerName, Board board) : name(std::move(playerName)), board(std::move(board)) {}

    virtual void setupShips() {board.setup("default", nullptr);}
    virtual void takeTurn(Player &opponent) const;
    [[nodiscard]] bool hasLost() const {return board.allShipsSunk(); }
    Board& getBoard() {return board;}
};

class AIPlayer final : public Player {
    std::vector<std::vector<int>> *heatmap{new std::vector(board.getSize().first, std::vector(board.getSize().second, 1))};
    std::string placementStrategy;
    std::string attackStrategy;

public:
    AIPlayer(const std::string& playerName, const Board& board, std::string defStrat, std::string attStrat):
        Player(playerName, board),
        placementStrategy(std::move(defStrat)),
        attackStrategy(std::move(attStrat)){}

    void setupShips() override {board.setup(placementStrategy, heatmap);}
    void takeTurn(Player &opponent) const override;
};



#endif //PLAYER_H
