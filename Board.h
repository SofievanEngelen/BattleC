//
// Created by Sofie van Engelen on 15/11/2024.
//

#ifndef BOARD_H
#define BOARD_H
#include <vector>

#include "GridSpace.h"
#include "Ship.h"

class Board {
    std::vector< std::vector< GridSpace > > grid {}; //array??
    const std::pair<int, int> size {};
    Ship ships[5] {Ship(5, "Carrier"),
                    Ship(4, "Battleship"),
                    Ship(3, "Cruiser"),
                    Ship(3, "Submarine"),
                    Ship(2, "Destroyer")};

    // Ship ships[2] {
    //     Ship(2, "Destroyer"),
    //     Ship(3, "test")
    // };

public:
    explicit Board(const std::pair<int, int> &size) : size(size), grid(size.first, std::vector(size.second, GridSpace())) {}

    void setup(const std::string& strategy, std::vector<std::vector<int>> *heatmap);
    bool placeShip(Ship& ship, int row, int col, char orientation);
    // bool takeShot(const std::string& playerName, std::string strategy);
    bool shoot(int row, int col);
    auto& getShips() {return ships;}
    [[nodiscard]] auto getSize() const {return size;}
    [[nodiscard]] bool allShipsSunk() const {return std::all_of(std::begin(ships),std::end(ships),[] (const Ship &ship){ return ship.sunk;});}
    void display(bool ownership) const;
    [[nodiscard]] std::string getRow(int rowNum, bool ownership) const;
    std::vector< std::vector< GridSpace > > getGrid() {return grid;}
};


#endif //BOARD_H
