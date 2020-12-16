/**
 * @file   simulation.h
 * @author Zhimin Sun
 * @date   2020-10-22
 * @course 2020FA VE280
 */
#ifndef SIMULATION_H
#define SIMULATION_H

#include "world_type.h"
#include <string>

using namespace std;

void initWorld(world_t &world, const string &speciesFile,
               const string &creaturesFile);
// MODIFIES: world
//
// EFFECTS: Initialize "world" given the species summary file
// "speciesFile" and the world description file
// "creaturesFile". This initializes all the components of
// "world". Throw an int value if initialization fails.

void simulateCreature(creature_t &creature, grid_t &grid, bool verbose);
// REQUIRES: creature is inside the grid.
//
// MODIFIES: creature, grid, cout.
//
// EFFECTS: Simulate one turn of "creature" and update the creature,
// the infected creature, and the grid if necessary.
// The creature programID is always updated. The function
// also prints to the stdout the procedure. If verbose is
// true, it prints more information.

void printGrid(const grid_t &grid);
// MODIFIES: cout.
//
// EFFECTS: print a grid representation of the creature world.

#endif // SIMULATION_H
