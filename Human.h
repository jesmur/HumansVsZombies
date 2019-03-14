//
// Created by W0273960 on 11/21/2018.
//

#ifndef HUMANSVSZOMBIES_HUMAN_H
#define HUMANSVSZOMBIES_HUMAN_H

#include "Organism.h"

class Human : public Organism
{
public:
    Human();
    Human(City *city, int x, int y);
    virtual ~Human();

    virtual void move();
    virtual void spawn();
    virtual species getSpecies();


};

#endif //HUMANSVSZOMBIES_HUMAN_H
