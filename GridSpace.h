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
    bool markHit() {
        if (hit) {
            std::cout << "You already hit that spot, try again!\n\n";
            return false;
        }
        hit = true; // print hit
        moves++;

        if (ship) {
            displayValue = 'X';
            return ship->markHit();
        }

        std::cout << "Miss!\n";
        displayValue = 'O';
        return true;
    }
};

#endif //GRIDSPACE_H
