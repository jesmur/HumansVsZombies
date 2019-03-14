#include <vector>
#include <random>
#include <algorithm>
#include <time.h>
#include <ctime>
#include "Human.h"
#include "City.h"

using namespace std;

// Default constructor
Human::Human() = default;

// Constructor with args
Human::Human(City *city, int xPosition, int yPosition) : Organism(city, xPosition, yPosition) {
    this->yPosition = yPosition;
    this->xPosition = xPosition;
    this->city = city;
    this->currentSteps = 0;
    this->hasSpawned = true;
}

// Destructor
Human::~Human() = default;

// Returns species ENUM
species Human::getSpecies() {
    return HUMAN;
}


void Human::move() {

    // Create vector of possible move coordinates
    vector<coord> moves;
    moves.emplace_back(coord(-1, 0));
    moves.emplace_back(coord(0, -1));
    moves.emplace_back(coord(0, 1));
    moves.emplace_back(coord(1, 0));

   // Randomize vector to ensure unbiased movement
    shuffle(moves.begin(), moves.end(), mt19937(random_device()()));

    this->currentSteps++;

    // Iterate through list of coords to search for possible moves
    for (auto &move : moves) {

        int newX = xPosition + move.x;
        int newY = yPosition + move.y;

        // Check if the move is within bounds and there isn't an occupant
        if(isValidMove(newX, newY)) {
            if(city->getOrganism(newX, newY) == nullptr){

                // Set human to new coordinate and set previous coordinate to nullptr
                city->setOrganism(this, newX, newY);
                city->getOrganism(newX, newY)->setMoved(true);
                city->setOrganism(nullptr, xPosition, yPosition);

                this->setPosition(newX, newY);

                break;
            }
        }
    }
}


void Human::spawn(){

    // Create vector of possible move coordinates
    vector<coord> searchForHumanCoords;
    searchForHumanCoords.emplace_back(coord(0, 1));
    searchForHumanCoords.emplace_back(coord(0, -1));
    searchForHumanCoords.emplace_back(coord(-1, 0));
    searchForHumanCoords.emplace_back(coord(1, 0));

    // Randomize vector to eliminate movement bias
    shuffle(searchForHumanCoords.begin(), searchForHumanCoords.end(), mt19937(random_device()()));

    // Iterate through list of coords to search for possible moves
    for (auto &searchForHumanCoord : searchForHumanCoords) {

        int newX = xPosition + searchForHumanCoord.x;
        int newY = yPosition + searchForHumanCoord.y;

        // If the move is within bounds
        if (isValidMove(newX, newY)) {
            // If the space does not contain an organism, recruit a new human
            if (city->getOrganism(newX, newY) == nullptr){
                city->setOrganism(new Human(city, newX, newY), newX, newY);
                city->getOrganism(xPosition, yPosition)->setHasSpawned(true);

                break;
            }
        }
    }
    // If human cannot recruit another, reset its steps so it cannot spawn again next turn
    if(!city->getOrganism(xPosition, yPosition)->getHasSpawned()) {
        city->getOrganism(xPosition, yPosition)->setCurrentSteps(0);
    }
}