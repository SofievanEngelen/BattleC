//
// Created by Sofie van Engelen on 15/11/2024.
//

#ifndef SHIP_H
#define SHIP_H
#include <iostream>
#include <string>

class Ship {

    const int ship_length;
    const std::string ship_type;
    int hits{0};
    bool sunk{false};

public:
    Ship(const int length, std::string type) : ship_length(length), ship_type(std::move(type)) {}

    [[nodiscard]] bool isSunk() const { return sunk; }
    [[nodiscard]] bool getLength() const { return ship_length; }
    [[nodiscard]] std::string getType() const { return ship_type; }

    // Return if the ship sank
    bool markHit() {
        hits++;
        if (hits >= ship_length) {
            std::cout << "You sank your opponent's " << ship_type << "!\n\n";
            sunk = true;
            return true;
        }
        std::cout << "Hit!\n\n";
        return false;
    }
};

#endif //SHIP_H
