//
// Created by W0273960 on 11/21/2018.
//

#ifndef HUMANSVSZOMBIES_ZOMBIE_H
#define HUMANSVSZOMBIES_ZOMBIE_H

#include "Organism.h"


class Zombie : public Organism {
protected:
    int stepsStarved;
public:
    Zombie();
    Zombie(City *city, int xPosition, int yPosition);
    virtual ~Zombie();

    virtual void move();
    virtual void spawn();
    virtual species getSpecies();
};



#endif //HUMANSVSZOMBIES_ZOMBIE_H
