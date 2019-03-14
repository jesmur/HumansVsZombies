#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Simulation.h"
#include "City.h"

City city = City();

void Simulation::start() {

    // Random seed
    srand(time(0));

    // Initial population of city
    city.populate();

    // Timer refs
    // http://www.cplusplus.com/forum/beginner/76147/
    // http://www.cplusplus.com/reference/ctime/clock/
    double counter = 0;
    double pauseInterval = PAUSE_SECONDS;
    clock_t startTime = clock();
    clock_t previousTime = startTime;
    int iteration = 1;

    // Run for number of set iterations
    do{
        startTime = clock();
        counter += startTime - previousTime;
        previousTime = startTime;

        if(counter > pauseInterval * CLOCKS_PER_SEC) {
            counter -= pauseInterval * CLOCKS_PER_SEC;

            cout << "-----------------w----- ITERATION " << iteration << " ------------------------";
            iteration++;
            cout << city;
            city.step();
            // Break if there is an extinction event
            if(city.humanExtinction || city.zombieExtinction) {
                break;
            }
        }

    }while (iteration <= ITERATIONS);

    // End of program printout
    if (city.zombieExtinction){
        cout << "-------------------- ZOMBIE EXTINCTION --------------------" << endl;
        cout << "Zombies have been eradicated! Humanity shall continue to ruin the earth!" << endl;
        cout << "------------------------------------------------------------\n";
    }
    else if(city.humanExtinction) {
        cout << "--------------------- HUMAN EXTINCTION ---------------------" << endl;
        cout << "             Zombies have taken over the earth!" << endl;
        cout << "(Although technically they'll turn back to humans eventually...)" << endl;
        cout << "------------------------------------------------------------\n";
    }
    else if (iteration >= ITERATIONS){
        cout << "------------------- NO EXTINCTION EVENTS -------------------" << endl;
        cout << "          Everyone continues to suffer for eternity!" << endl;
        cout << "------------------------------------------------------------\n";
    }


}