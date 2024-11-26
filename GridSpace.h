//
// Created by Sofie van Engelen on 18/11/2024.
//

#ifndef GRIDSPACE_H
#define GRIDSPACE_H
#include "global.h"
#include "Ship.h"

struct GridSpace {
    bool hit{false};
    Ship *ship{nullptr};
    char displayValue{'.'};

    // Return boolean -> end of turn?
    bool markHit(const bool feedback) {
        if (hit) {
            if (feedback) {std::cout << "You already hit that spot, try again!" << std::endl;}
            return false;
        }
        hit = true; // print hit
        moves++;

        if (ship) {
            displayValue = 'X';
            return ship->markHit();
        }

        std::cout << "Miss!" << std::endl;
        displayValue = 'O';
        return true;
    }
};

#endif //GRIDSPACE_H
