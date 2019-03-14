//
// Created by W0273960 on 11/21/2018.
//

#include "Organism.h"
#include <cstdio>
#include <iostream>
#include <windows.h>

// Default constructor
Organism::Organism() = default;

// Constructor with args
Organism::Organism(City *city, int x, int y) {}

// Destructor
Organism::~Organism() = default;

// Overridden output stream for char and color formatting
ostream& operator<<( ostream &output, Organism *organism ){

    if(organism->getSpecies() == HUMAN) {
        output << "[";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), HUMAN_COLOR);
        output << HUMAN_CH;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        output << "]";
    }
    else if (organism->getSpecies() == ZOMBIE) {
        output << "[";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ZOMBIE_COLOR);
        output << ZOMBIE_CH;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        output << "]";
    }
    return output;
};

// Check to see if x and y coordinates are within grid counts
bool Organism::isValidMove(int x, int y) {
    return ((x >= 0) && (x < GRIDSIZE) && (y >= 0) && (y < GRIDSIZE));
}

// --------- ACCESSORS AND MUTATORS ----------------

void Organism::setPosition(int x, int y){
    this->xPosition = x;
    this->yPosition = y;
}

bool Organism::hasMoved() const {
    return moved;
}

void Organism::setMoved(bool oneStep) {
    this->moved = oneStep;
}

int Organism::getCurrentSteps(){
    return this->currentSteps;
}

void Organism::setCurrentSteps(int steps){
    this->currentSteps = steps;
}

bool Organism::getHasSpawned() const{
    return this->hasSpawned;
}

void Organism::setHasSpawned(bool spawned){
    this->hasSpawned = spawned;
}





