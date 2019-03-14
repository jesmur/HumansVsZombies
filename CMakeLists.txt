cmake_minimum_required(VERSION 3.10)
project(HumansVsZombies)

set(CMAKE_CXX_STANDARD 11)
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(HumansVsZombies main.cpp Human.cpp Human.h Zombie.cpp Zombie.h Organism.cpp Organism.h City.cpp City.h Simulation.cpp Simulation.h)