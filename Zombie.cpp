//
// Created by W0273960 on 11/21/2018.
//

#include <vector>
#include <random>
#include <algorithm>
#include "Zombie.h"
#include "GameSpecs.h"
#include "City.h"

// Default constructor
Zombie::Zombie() = default;

// Constructor with args
Zombie::Zombie(City *city, int xPosition, int yPosition) : Organism(city, xPosition, yPosition) {
    this->yPosition = yPosition;
    this->xPosition = xPosition;
    this->city = city;
    this->currentSteps = 0;
    this->stepsStarved = 0;
    this->hasSpawned = true;
}

// Destructor
Zombie::~Zombie() = default;

// Return species ENUM
species Zombie::getSpecies() {
    return ZOMBIE;
}

void Zombie::move() {
    // Flag for continuing into non-feeding movement
    bool hasFed = false;

    // Vector of coordinates to check for humans
    vector<coord> searchForHumanCoords;
    searchForHumanCoords.emplace_back(coord(0, 1));
    searchForHumanCoords.emplace_back(coord(0, -1));
    searchForHumanCoords.emplace_back(coord(-1, 0));
    searchForHumanCoords.emplace_back(coord(1, 0));
    searchForHumanCoords.emplace_back(coord(1, 1));
    searchForHumanCoords.emplace_back(coord(-1, 1));
    searchForHumanCoords.emplace_back(coord(1, -1));
    searchForHumanCoords.emplace_back(coord(-1, -1));

    // Vector of coordinates to move to if no humans are found
    vector<coord> moves;
    moves.emplace_back(coord(-1, 0));
    moves.emplace_back(coord(0, -1));
    moves.emplace_back(coord(0, 1));
    moves.emplace_back(coord(1, 0));

    // Randomize vectors to ensure unbiased movement
    // Shuffle ref:
    // https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
    shuffle(searchForHumanCoords.begin(), searchForHumanCoords.end(), mt19937(random_device()()));
    shuffle(moves.begin(), moves.end(), mt19937(random_device()()));

    for (auto &searchForHumanCoord : searchForHumanCoords) {

        int newX = xPosition + searchForHumanCoord.x;
        int newY = yPosition + searchForHumanCoord.y;

        // If the potential move is within bounds
        if(isValidMove(newX, newY)) {

            // If there is a human in the potential spot
            if (city->getOrganism(newX, newY) != nullptr &&
                city->getOrganism(newX, newY)->getSpecies() == HUMAN) {

                // Increment current steps and reset starvation counter
                this->currentSteps++;
                this->stepsStarved = 0;

                // Remove human and move zombie into spot
                city->setOrganism(nullptr, newX, newY);
                city->setOrganism(this, newX, newY);
                city->getOrganism(newX, newY)->setMoved(true);
                city->setOrganism(nullptr, xPosition, yPosition);

                this->setPosition(newX, newY);

                hasFed = true;
                break;
            }
        }
    }

    // If the zombie hasn't found a human to feed on
    if(!hasFed) {
        for (auto &move : moves) {

            int newX = xPosition + move.x;
            int newY = yPosition + move.y;

            // If the move is within bounds and there isn't an occupant
            if(isValidMove(newX, newY)) {
                // If the potential spot does not contain another organism
                if(city->getOrganism(newX, newY) == nullptr){
                    // Increment steps
                    this->currentSteps++;
                    this->stepsStarved++;

                    // Turn zombie into a human if it hasn't eaten in 3 turns
                    if(this->stepsStarved >= ZOMBIE_STARVE){
                        city->setOrganism(new Human(city, xPosition, yPosition), xPosition, yPosition);
                        break;
                    }
                    // Else it moves to new location
                    else {
                        city->setOrganism(this, newX, newY);
                        city->getOrganism(newX, newY)->setMoved(true);
                        city->setOrganism(nullptr, xPosition, yPosition);

                        this->setPosition(newX, newY);

                        break;
                    }
                }
            }
        }
    }
}

void Zombie::spawn(){

    // Vector of coordinates to check for humans
    vector<coord> searchForHumanCoords;
    searchForHumanCoords.emplace_back(coord(0, 1));
    searchForHumanCoords.emplace_back(coord(0, -1));
    searchForHumanCoords.emplace_back(coord(-1, 0));
    searchForHumanCoords.emplace_back(coord(1, 0));
    searchForHumanCoords.emplace_back(coord(1, 1));
    searchForHumanCoords.emplace_back(coord(-1, 1));
    searchForHumanCoords.emplace_back(coord(1, -1));
    searchForHumanCoords.emplace_back(coord(-1, -1));

    // Randomize vector to ensure unbiased movement
    shuffle(searchForHumanCoords.begin(), searchForHumanCoords.end(), mt19937(random_device()()));

    for (auto &searchForHumanCoord : searchForHumanCoords) {

        int newX = xPosition + searchForHumanCoord.x;
        int newY = yPosition + searchForHumanCoord.y;

        // If the move is within bounds
        if (isValidMove(newX, newY)) {
            // If the space contains a human
            if (city->getOrganism(newX, newY) != nullptr && city->getOrganism(newX, newY)->getSpecies() == HUMAN){
                // Set previous human to null and create a new zombie where human was
                city->setOrganism(nullptr, newX, newY);
                city->setOrganism(new Zombie(city, newX, newY), newX, newY);
                city->getOrganism(xPosition, yPosition)->setHasSpawned(true);

                break;
            }
        }
    }
    // If zombie cannot convert a human, retain its steps to try again next turn
    if(!city->getOrganism(xPosition, yPosition)->getHasSpawned()) {
        city->getOrganism(xPosition, yPosition)->setCurrentSteps(ZOMBIE_BREED);
    }
}
