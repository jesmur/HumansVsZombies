//
// Created by W0273960 on 11/21/2018.
//

#include "City.h"
#include <ctime>
#include <stdio.h>
#include <stdlib.h>

// Constructor
City::City() = default;

// Destructor
City::~City() = default;

// ------------ ACCESSORS AND MUTATORS --------------
Organism *City::getOrganism(int x, int y) const{
    return grid[x][y];
}

void City::setOrganism(Organism *organism, int x, int y) {
    grid[x][y] = organism;
}
// ---------------------------------------------------

// Overridden output stream for display grid
ostream& operator<<(ostream &output, City &city) {

    output << "\n";

    for (auto &row : city.grid) {
        for (auto &col : row) {

            // If there are no organisms in grid coordinates
            if(col == nullptr) {
                output << "[" << SPACE_CH << "]";
            }
            // If there is an organism in grid coordinates
            else{
                if(col->getSpecies() == HUMAN){
                    city.humanCount++;
                }
                else if(col->getSpecies() == ZOMBIE) {
                    city.zombieCount++;
                }
                output << col;
            }
        }
        output << "\n";
    }

    output << "\t\t HUMANS: "<< city.humanCount <<"    ZOMBIES: "<< city.zombieCount << "\n" << endl;

    // Return boolean flag if there is an extinction event
    if (city.humanCount == 0){
        city.humanExtinction = true;
    }
    else if(city.zombieCount == 0) {
        city.zombieExtinction = true;
    }

    city.humanCount = 0;
    city.zombieCount = 0;

    return output;
}

// Set initial random grid population
void City::populate() {

    int humanCount = 0;
    int zombieCount = 0;

    // Random seed
    // Random ref:
    // http://www.math.uaa.alaska.edu/~afkjm/csce211/fall2018/handouts/RandomFunctions.pdf
    srand(time(NULL));

    // Iterate over grid to populate with starting count of humans
    do{
        int row = random(GRIDSIZE);
        int col = random(GRIDSIZE);

        if(grid[row][col] == nullptr) {
            this->setOrganism(new Human(this, row, col), row, col);
            humanCount++;
        }

    }while(humanCount < HUMAN_STARTCOUNT);

    // Iterate over grid to populate with starting count of zombies
    do{
        int row = random(GRIDSIZE);
        int col = random(GRIDSIZE);

        if(grid[row][col] == nullptr) {
            this->setOrganism(new Zombie(this, row, col), row, col);
            zombieCount++;
        }

    }while(zombieCount < ZOMBIE_STARTCOUNT);
}

// Random ref:
// http://www.math.uaa.alaska.edu/~afkjm/csce211/fall2018/handouts/RandomFunctions.pdf
int City::random(int num) const{
    return rand() % num;
}

// Method for each "step" or iteration
// Prints out grid, moves organisms, spawns organisms and resets bool values
void City::step(){
    //cout << *this;
    moveOrganisms();
    spawnOrganisms();
    resetStatus();
}

// Move polymorphic routine to move organisms
void City::moveOrganisms(){
    for (auto &row : grid) {
        for (auto &col : row) {
            if (col != nullptr && !col->hasMoved()) {
                col->move();
            }
        }
    }
}

// Polymorphic routine to spawn organisms
void City::spawnOrganisms(){
    for (auto &row : grid) {
        for (auto &col : row) {
            if ((col != nullptr) && (!col->getHasSpawned())){
                if((col->getSpecies() == HUMAN) && col->getCurrentSteps() % HUMAN_BREED == 0){
                    col->spawn();
                }
                else if(col->getSpecies() == ZOMBIE && col->getCurrentSteps() % ZOMBIE_BREED == 0) {
                    col->spawn();
                }
            }
        }
    }
}

// Reset organisms moved and spawned statuses
void City::resetStatus(){
    for (auto &row : grid) {
        for (auto &col : row) {
            if (col != nullptr) {
                col->setMoved(false);
                col->setHasSpawned(false);
            }
        }
    }
}