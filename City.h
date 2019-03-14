//
// Created by W0273960 on 11/21/2018.
//

#ifndef HUMANSVSZOMBIES_CITY_H
#define HUMANSVSZOMBIES_CITY_H

#include <iostream>
#include "GameSpecs.h"
#include "Organism.h"
#include "Zombie.h"
#include "Human.h"

using namespace std;

class Organism;

class City {

protected:
    Organism *grid[GRIDSIZE][GRIDSIZE];

public:
    City();
    virtual ~City();

    int random(int) const;
    void populate();

    void step();
    void resetStatus();
    void moveOrganisms();
    void spawnOrganisms();

    Organism *getOrganism(int x, int y) const;
    void setOrganism(Organism *organism, int x, int y);

    friend ostream& operator<<(ostream &output, City &city);
    int humanCount;
    int zombieCount;
    bool humanExtinction = false;
    bool zombieExtinction = false;

};


#endif //HUMANSVSZOMBIES_CITY_H
