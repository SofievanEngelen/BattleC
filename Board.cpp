//
// Created by Sofie van Engelen on 15/11/2024.
//

#include "Board.h"
#include "global.h"

#include <iostream>
#include <ostream>
#include <random>


std::tuple<int, int, char> randomPlacement(const std::pair<int, int> &boardSize) {
    return {
        randomInt(0, boardSize.first - 1),
        randomInt(0, boardSize.second - 1),
        randomInt(0, 1) == 0 ? 'H' : 'V'
    };
}


std::vector<std::vector<bool>> generatePattern(const std::pair<int, int>& size, const patterns patternType) {

    std::vector pattern(size.first, std::vector(size.second, false));

    switch (patternType) {
        case Checkerboard:
            for (int row = 0; row < size.first; ++row) {
                for (int col = 0; col < size.second; ++col) {
                    pattern[row][col] = (row + col) % 2 == 0;
                }
            } break;

        case EdgeHeavy:
            for (int row = 0; row < size.first; ++row) {
                for (int col = 0; col < size.second; ++col) {
                    pattern[row][col] = (row == 0 || row == size.first - 1 || col == 0 || col == size.second - 1);
                }
            } break;

        case Cross: {
            const int midRow = size.first / 2;
            const int midCol = size.second / 2;
            for (int row = 0; row < size.first; ++row) {
                for (int col = 0; col < size.second; ++col) {
                    pattern[row][col] = (row == midRow || col == midCol);
                }
            } break;
        }

        default:
            std::cerr << "Unknown pattern type: " << patternType << std::endl;
    }
    return pattern;
}


bool Board::placeShip(Ship &ship, const int row, const int col, const char orientation, const bool feedback) {
    switch (orientation) {
        case 'V':
            for (int i{0}; i < ship.ship_length; i++) {
                if (0 > row+i || row+i > this->size.first-1 || 0 > col || col > this->size.second-1) {
                    if (feedback) {std::cout << "Ship goes out of bounds, try again." << std::endl;}
                    return false;
                }
                if (grid[row+i][col].ship) {
                    if (feedback) {std::cout << "There is already a ship there, try again." << std::endl;}
                    return false;
                }
            }

            for (int i{0}; i < ship.ship_length; i++) {
                grid[row+i][col].ship = &ship;}
        return true;

        case 'H':
            for (int i{0}; i < ship.ship_length; i++) {
                if (0 > row || row > this->size.first-1 || 0 > col+i || col+i > this->size.second-1) {
                    if (feedback) {std::cout << "Ship goes out of bounds, try again." << std::endl;}
                    return false;
                }
                if (grid[row][col+i].ship) {
                    if (feedback) {std::cout << "There is already a ship there, try again." << std::endl;}
                    return false;
                }

            }

        for (int i{0}; i < ship.ship_length; i++) {
            grid[row][col+i].ship = &ship;}
        return true;

        default:
            std::cout << orientation << '\n';
        return false;
    }
}

void Board::setup(const placementStrategies strategy, std::vector<std::vector<int>> *heatmap) {

    switch (strategy) {
        case ManualInput: // Manual placement
            std::cout << "The format of ship positions should be: start_coordinates orientation'\n "
                         "e.g. 'A1 H' will place the far end of the ship on A1 and continue down row 1.\n";
            for (auto &ship : ships) {
                while (true) {
                    std::cout << "Where would you like to place your " << ship.ship_type << " (" << ship.ship_length << ")?\n";

                    if (const auto [row, col, orient] {getPositionInputOrientation()}; !placeShip(ship, row, col, orient, true)) {continue;}
                    break;
                }
                this->display(true);
            } break;

        case RandomPlacement: // Random placement
            for (Ship& ship : ships) {
                bool placed = false;
                while (!placed) {
                    const auto [row, col, orient] = randomPlacement(this->size);
                    placed = this->placeShip(ship, row, col, orient, false);
                }
            } break;

        case ProbabilityDensityPlacement: // Probability Density
            for (Ship& ship : ships) {
                bool placed = false;
                int attempts = 0;
                constexpr int maxAttempts = MAXATTEMPTS;

                while (!placed && attempts++ < maxAttempts) {
                    const auto [row, col, orient] = randomPlacement(this->size);
                    if ((*heatmap)[row][col] <= 2 && this->placeShip(ship, row, col, orient, false)) {
                        placed = true;

                        // Update heatmap around placed ship
                        for (int i = -1; i <= 1; ++i) {
                            for (int j = -1; j <= 1; ++j) {
                                if (row + i >= 0 && row + i < size.first &&
                                    col + j >= 0 && col + j < size.second) {
                                    (*heatmap)[row + i][col + j]++;
                                    }
                            }
                        }
                    }
                }
            } break;

        case HiddenPattern: {
            // Hidden Pattern
            std::cout << "Using Hidden Pattern placement." << std::endl;

            // Select a predefined pattern, e.g., checkerboard
            auto pattern = generatePattern(this->size, Cross);

            for (Ship& ship : ships) {
                bool placed = false;

                // Iterate through the pattern grid
                for (int row = 0; row < size.first && !placed; ++row) {
                    for (int col = 0; col < size.second && !placed; ++col) {
                        if (pattern[row][col]) { // Place the ship on valid cells in the pattern
                            if (placeShip(ship, row, col, 'H', false) || placeShip(ship, row, col, 'V', false)) {
                                placed = true;
                                std::cout << "Placed " << ship.ship_type << " at (" << row << ", " << col << ")." << std::endl;

                                // Optionally clear the used pattern cells
                                pattern[row][col] = false;
                            }
                        }
                    }
                }

                if (!placed) {
                    std::cerr << "Failed to place " << ship.ship_type << " using hidden pattern!" << std::endl;
                }
            } break;
        }

        case Automatic:
            default:
            for (int i{0}; i<std::size(ships); i++) {
                placeShip(ships[i], 0, i, 'V', false);
            }
    }
}

bool Board::shoot(const int row, const int col) {
    return grid[row][col].markHit();
}

std::string Board::getRow(const int rowNum, const bool ownership) const {
    std::string returnString;

    for (int col{0}; col < size.second; col++) {
        if (const Ship* ship{grid[rowNum][col].ship}; ship != nullptr && (ownership || ship->sunk)) {
            returnString += shipIDs[ship->ship_type];
        } else {returnString += grid[rowNum][col].displayValue;}
        returnString += '\t';
    }
    return returnString;
}

void Board::display(const bool ownership) const {
    std::cout << "Defence board:" << std::endl;
    std::cout << "\tA  B  C  D  E  F  G  H  I  J" << std::endl;
    for (int row{0}; row < size.first; row++) {
        std::cout << row+1 << ".\t";

        for (int col{0}; col < size.second; col++) {
            if (ownership && grid[row][col].ship != nullptr) {
                std::cout << shipIDs[grid[row][col].ship->ship_type] << "  ";
            } else {std::cout << grid[row][col].displayValue << "  ";}
        }
        std::cout << std::endl;
    }
}

