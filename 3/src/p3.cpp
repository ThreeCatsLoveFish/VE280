/**
 * @file   p3.cpp
 * @author Zhimin Sun
 * @date   2020-10-22
 * @course 2020FA VE280
 */
#include "simulation.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    bool    verbose = false;
    int     round;
    string  speciesFile;
    string  worldFile;
    world_t world;

    /* Produce the arguments. */
    if (argc < 4) {
        cout << "Error: Missing arguments!\n";
        cout << "Usage: ./p3 <species-summary> <world-file> <rounds> ";
        cout << "[v|verbose]\n";
        return 0;
    }
    round       = atoi(argv[3]);
    speciesFile = argv[1];
    worldFile   = argv[2];
    if (round < 0) {
        cout << "Error: Number of simulation rounds is negative!\n";
        return 0;
    }
    if (argc == 5) {
        string verboseArg;

        verboseArg = argv[4];
        if (verboseArg == "v" || verboseArg == "verbose") {
            verbose = true;
        }
    }

    /* Initialize the world. */
    try {
        initWorld(world, argv[1], argv[2]);
    } catch (int error) {
        return 0;
    }

    /* Simulate the world. */
    for (int r = 1; r <= round; r++) {
        cout << "Round " << r << endl;
        for (size_t i = 0; i < world.numCreatures; i++) {
            simulateCreature(world.creatures[i], world.grid, verbose);
        }
        if (!verbose) {
            printGrid(world.grid);
        }
    }
    return 0;
}
