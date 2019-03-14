#ifndef HUMANSVSZOMBIES_ORGANISM_H
#define HUMANSVSZOMBIES_ORGANISM_H

#include <iostream>
#include "GameSpecs.h"


using namespace std;

class City;

enum species {HUMAN, ZOMBIE};

struct coord {
    int x;
    int y;

    coord(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

class Organism {

protected:
    int xPosition, yPosition, currentSteps;
    bool moved, hasSpawned;
    City *city;

public:
    Organism();
    Organism( City *city, int xPosition, int yPosition);
    virtual ~Organism();

    virtual void move() = 0;
    virtual void spawn() = 0;
    virtual species getSpecies() = 0; //this could also be coded concrete here
    void setPosition(int x, int y);

    bool hasMoved() const;
    void setMoved(bool moved);

    bool getHasSpawned() const;
    void setHasSpawned(bool spawned);

    int getCurrentSteps();
    void setCurrentSteps(int steps);

    bool isValidMove(int x, int y);

    friend ostream& operator<<( ostream &output, Organism *organism );
};


#endif //HUMANSVSZOMBIES_ORGANISM_H
