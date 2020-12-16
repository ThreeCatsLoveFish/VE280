/**
 * @file   simulation.cpp
 * @author Zhimin Sun
 * @date   2020-10-22
 * @course 2020FA VE280
 */
#include "simulation.h"
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

/*******************************************************************************
 *                             CONST PARAMETERS                                *
 ******************************************************************************/
const unsigned int MAXDIRECTIONS  = 4; // Max number of directions
const unsigned int MAXOPERATIONS  = 9; // Max number of operations
const unsigned int PUREOPERATIONS = 4; // Number of simple operations

/*******************************************************************************
 *                          QUERY HELPER FUNCTIONS                             *
 ******************************************************************************/
static void querySpecies(const string &type, world_t &world,
                         species_t *&species)
// MODIFIES: species.
//
// EFFECTS: Search the species and write the pointer into creature. If species
// is not found, throw 1.
{
    for (size_t i = 0; i < world.numSpecies; i++) {
        if (type == world.species[i].name) {
            species = &world.species[i];
            return;
        }
    }
    cout << "Error: Species " << type << " not found!\n";
    throw 1;
}

static void queryDirection(const string &data, direction_t &direction)
// MODIFIES: direction.
//
// EFFECTS: Search the direction and write into direction. If direction is not
// recognized, throw 1.
{
    for (size_t i = 0; i < MAXDIRECTIONS; i++) {
        if (data == directName[i]) {
            direction = static_cast<direction_t>(i);
            return;
        }
    }
    cout << "Error: Direction " << data << " is not recognized!\n";
    throw 1;
}

/*******************************************************************************
 *                          PARSE HELPER FUNCTIONS                             *
 ******************************************************************************/
static void parseInstruction(const string & instructionString,
                             instruction_t &instruction)
// MODIFIES: instruction.
//
// EFFECTS: Parse the instruction string and write into instruction. If
// instruction is not recognized, throw 1.
{
    int           address;
    istringstream info(instructionString);
    string        operation;

    info >> operation;
    for (size_t i = 0; i < PUREOPERATIONS; i++) {
        if (operation == opName[i]) {
            instruction.op = static_cast<opcode_t>(i);
            return;
        }
    }
    info >> address;
    for (size_t i = PUREOPERATIONS; i < MAXOPERATIONS; i++) {
        if (operation == opName[i]) {
            instruction.op      = static_cast<opcode_t>(i);
            instruction.address = address - 1;
            return;
        }
    }
    cout << "Error: Instruction " << operation << " is not recognized!\n";
    throw 1;
}

/*******************************************************************************
 *                         OBJECT HELPER FUNCTIONS                             *
 ******************************************************************************/
static void speciesProgram(const string &pathToSpecies, species_t &species)
// MODIFIES: species.
//
// EFFECTS: Open the certain species file and create a species. If file cannot
// be opened, throw 1. If there are too many instructions for species, throw 2.
{
    ifstream speciesFile;

    species.programSize = 0;
    speciesFile.open(pathToSpecies);
    if (!speciesFile) {
        cout << "Error: Cannot open file " << pathToSpecies << "!\n";
        throw 1;
    }
    for (string instruction; getline(speciesFile, instruction);) {
        if (instruction.length() == 0) {
            if (species.programSize == 0) {
                cout << "Error: Cannot open file " << pathToSpecies << "!\n";
                throw 1;
            }
            break;
        }
        if (species.programSize >= MAXPROGRAM) {
            cout << "Error: Too many instructions for species ";
            cout << species.name << "!\n";
            cout << "Maximal number of instructions is " << MAXPROGRAM << ".\n";
            throw 2;
        }
        parseInstruction(instruction, species.program[species.programSize++]);
    }
    speciesFile.close();
}

static void creatureProgram(const string &data, world_t &world,
                            creature_t &creature)
// MODIFIES: creature, world.
//
// EFFECTS: Create a creature. If creature is out of bound, throw 1. If one
// species overlaps another creature, throw 2.
{
    istringstream createStream(data);
    size_t        column;
    size_t        row;
    string        direction;
    string        species;

    createStream >> species >> direction >> row >> column;
    querySpecies(species, world, creature.species);
    queryDirection(direction, creature.direction);
    creature.location.c = column;
    creature.location.r = row;
    creature.programID  = 0;
    if (column < 0 || column >= world.grid.width || row < 0 ||
        row >= world.grid.height) {
        cout << "Error: Creature (";
        cout << species << " ";
        cout << direction << " ";
        cout << row << " ";
        cout << column << ") is out of bound!\n";
        cout << "The grid size is " << world.grid.height;
        cout << "-by-" << world.grid.width << ".\n";
        throw 1;
    }
    if (world.grid.squares[row][column]) {
        creature_t *under;

        under = world.grid.squares[row][column];
        cout << "Error: Creature (";
        cout << species << " ";
        cout << direction << " ";
        cout << row << " ";
        cout << column << ") overlaps with creature (";
        cout << under->species->name << " ";
        cout << directName[under->direction] << " ";
        cout << under->location.r << " ";
        cout << under->location.c << ")!\n";
        throw 2;
    } else {
        world.grid.squares[row][column] = &creature;
    }
}

/*******************************************************************************
 *                       SIMULATION HELPER FUNCTIONS                           *
 ******************************************************************************/
static point_t adjacentPoint(const point_t &pt, const direction_t &dir)
// EFFECTS: Return a point that results from moving one square
// in the direction "dir" from the point "pt".
{
    switch (dir) {
    case EAST:
        return {pt.r, pt.c + 1};
    case SOUTH:
        return {pt.r + 1, pt.c};
    case WEST:
        return {pt.r, pt.c - 1};
    case NORTH:
        return {pt.r - 1, pt.c};
    default:
        assert(false);
    }
}

static direction_t leftFrom(const direction_t &dir)
// EFFECTS: Return the direction that results from turning
// left from the given direction "dir".
{
    switch (dir) {
    case EAST:
        return NORTH;
    case SOUTH:
        return EAST;
    case WEST:
        return SOUTH;
    case NORTH:
        return WEST;
    default:
        assert(false);
    }
}

static direction_t rightFrom(const direction_t &dir)
// EFFECTS: Return the direction that results from turning
// right from the given direction "dir".
{
    switch (dir) {
    case EAST:
        return SOUTH;
    case SOUTH:
        return WEST;
    case WEST:
        return NORTH;
    case NORTH:
        return EAST;
    default:
        assert(false);
    }
}

static instruction_t &getInstruction(const creature_t &creature)
// REQUIRES: creature is already initialized.
//
// EFFECTS: Return the current instruction of "creature".
{
    return creature.species->program[creature.programID];
}

static creature_t *getCreature(const grid_t &grid, const point_t &location)
// REQUIRES: location is inside the grid.
//
// EFFECTS: Return a pointer to the creature at "location" in "grid".
{
    return grid.squares[location.r][location.c];
}

/*******************************************************************************
 *                             JUDGE FUNCTIONS                                 *
 ******************************************************************************/
static bool ifWall(const creature_t &creature, const grid_t &grid)
// EFFECT: Determine whether it's a wall before creature.
{
    point_t front;

    front = adjacentPoint(creature.location, creature.direction);
    return (front.c >= static_cast<int>(grid.width)) || (front.c < 0) ||
           (front.r >= static_cast<int>(grid.height)) || (front.r < 0);
}

static bool ifEmpty(const creature_t &creature, const grid_t &grid)
// EFFECT: Determine whether it's empty before creature.
{
    creature_t *front;

    if (ifWall(creature, grid)) {
        return false;
    }
    front =
        getCreature(grid, adjacentPoint(creature.location, creature.direction));
    return front == nullptr;
}

static bool ifEnemy(const creature_t &creature, const grid_t &grid)
// EFFECT: Determine whether it's an enemy before creature.
{
    creature_t *front;

    if (ifWall(creature, grid)) {
        return false;
    }
    front =
        getCreature(grid, adjacentPoint(creature.location, creature.direction));
    return front != nullptr && front->species != creature.species;
}

static bool ifSame(const creature_t &creature, const grid_t &grid)
// EFFECT: Determine whether it's same species before creature.
{
    creature_t *front;

    if (ifWall(creature, grid)) {
        return false;
    }
    front =
        getCreature(grid, adjacentPoint(creature.location, creature.direction));
    return front != nullptr && front->species == creature.species;
}

static void hopCreature(creature_t &creature, grid_t &grid)
// MODIFIES: creature, grid
//
// EFFECTS: Hop the creature.
{
    if (!ifEmpty(creature, grid)) {
        return;
    }
    grid.squares[creature.location.r][creature.location.c] = nullptr;
    creature.location = adjacentPoint(creature.location, creature.direction);
    grid.squares[creature.location.r][creature.location.c] = &creature;
}

static void infectCreature(const creature_t &creature, const grid_t &grid)
// MODIFIES: creature pointed by grid.
//
// EFFECTS: Infect the creature.
{
    creature_t *front;

    if (!ifEnemy(creature, grid)) {
        return;
    }
    front =
        getCreature(grid, adjacentPoint(creature.location, creature.direction));
    front->programID = 0;
    front->species   = creature.species;
}

/*******************************************************************************
 *                       SIMULATION HELPER FUNCTIONS                           *
 ******************************************************************************/
static void printCreature(const creature_t &creature, bool verbose)
// MODIFIES: cout
//
// EFFECTS: Print the creature.
{
    cout << "Creature (" << creature.species->name << " ";
    cout << directName[creature.direction] << " ";
    cout << creature.location.r << " ";
    cout << creature.location.c << ") takes action:";
    if (verbose) {
        cout << "\n";
    }
}

static void printCreatureGrid(const creature_t *creature)
// MODIFIES: cout
//
// EFFECTS: Print the creature on grid.
{
    if (creature == nullptr) {
        cout << "____";
    } else {
        cout << creature->species->name.substr(0, 2) << "_";
        cout << directShortName[creature->direction];
    }
    cout << " ";
}

static void printInstruction(const creature_t &creature)
// MODIFIES: cout
//
// EFFECTS: Print the instruction.
{
    cout << " " << opName[creature.species->program[creature.programID].op];
    cout << endl;
}

static void printInstructionVerbose(const creature_t &creature)
// MODIFIES: cout
//
// EFFECTS: Print the instruction verbosely.
{
    cout << "Instruction " << creature.programID + 1 << ": ";
    cout << opName[creature.species->program[creature.programID].op];
    if (creature.species->program[creature.programID].op >= PUREOPERATIONS) {
        cout << " ";
        cout << creature.species->program[creature.programID].address + 1;
    }
    cout << endl;
}

/*******************************************************************************
 *                             PUBLIC FUNCTIONS                                *
 ******************************************************************************/
void initWorld(world_t &world, const string &speciesFile,
               const string &creaturesFile) {
    ifstream speciesSummary;
    ifstream worldInfo;
    string   pathToCreatures;

    world.numCreatures = 0;
    world.numSpecies   = 0;

    /* Species programs. */
    speciesSummary.open(speciesFile);
    if (!speciesSummary) {
        cout << "Error: Cannot open file " << speciesFile << "!\n";
        throw 1;
    }
    speciesSummary >> pathToCreatures;
    if (pathToCreatures.length() == 0) {
        cout << "Error: Cannot open file " << speciesFile << "!\n";
        throw 1;
    }
    pathToCreatures += '/';
    speciesSummary.get();
/* FOR LOCAL TEST ONLY. */
#ifdef LOCAL
    pathToCreatures = "test/" + pathToCreatures;
#endif
    for (string name; getline(speciesSummary, name);) {
        if (world.numSpecies >= MAXSPECIES) {
            cout << "Error: Too many species!\n";
            cout << "Maximal number of species is " << MAXSPECIES << ".\n";
            throw 2;
        }
        world.species[world.numSpecies].name = name;
        speciesProgram(pathToCreatures + name,
                       world.species[world.numSpecies++]);
    }
    speciesSummary.close();

    /* Input World settings. */
    worldInfo.open(creaturesFile);
    if (!worldInfo) {
        cout << "Error: Cannot open file " << creaturesFile << "!\n";
        throw 3;
    }
    worldInfo >> world.grid.height >> world.grid.width;
    if (worldInfo.get() != '\n') {
        cout << "Error: Cannot open file " << creaturesFile << "!\n";
        throw 3;
    }
    if (world.grid.height <= 0 || world.grid.height > MAXHEIGHT) {
        cout << "Error: The grid height is illegal!\n";
        throw 4;
    }
    if (world.grid.width <= 0 || world.grid.width > MAXWIDTH) {
        cout << "Error: The grid width is illegal!\n";
        throw 5;
    }
    for (size_t i = 0; i < world.grid.height; i++) {
        for (size_t j = 0; j < world.grid.width; j++) {
            world.grid.squares[i][j] = nullptr;
        }
    }
    for (string creature; getline(worldInfo, creature);) {
        if (world.numCreatures >= MAXCREATURES) {
            cout << "Error: Too many creatures!\n";
            cout << "Maximal number of creatures is " << MAXCREATURES << ".\n";
            throw 6;
        }
        creatureProgram(creature, world, world.creatures[world.numCreatures++]);
    }
    worldInfo.close();

    cout << "Initial state" << endl;
    printGrid(world.grid);
}

void simulateCreature(creature_t &creature, grid_t &grid, bool verbose) {
    instruction_t now;

    printCreature(creature, verbose);
    do {
        now = getInstruction(creature);
        if (verbose) {
            printInstructionVerbose(creature);
        } else if (now.op < PUREOPERATIONS) {
            printInstruction(creature);
        }
        switch (now.op) {
        case HOP:
            hopCreature(creature, grid);
            creature.programID++;
            break;
        case LEFT:
            creature.direction = leftFrom(creature.direction);
            creature.programID++;
            break;
        case RIGHT:
            creature.direction = rightFrom(creature.direction);
            creature.programID++;
            break;
        case INFECT:
            infectCreature(creature, grid);
            creature.programID++;
            break;
        case IFEMPTY:
            if (ifEmpty(creature, grid)) {
                creature.programID = now.address;
            } else {
                creature.programID++;
            }
            break;
        case IFENEMY:
            if (ifEnemy(creature, grid)) {
                creature.programID = now.address;
            } else {
                creature.programID++;
            }
            break;
        case IFSAME:
            if (ifSame(creature, grid)) {
                creature.programID = now.address;
            } else {
                creature.programID++;
            }
            break;
        case IFWALL:
            if (ifWall(creature, grid)) {
                creature.programID = now.address;
            } else {
                creature.programID++;
            }
            break;
        case GO:
            creature.programID = now.address;
            break;
        default:
            assert(false);
        }
    } while (now.op >= PUREOPERATIONS);
    if (verbose) {
        printGrid(grid);
    }
}

void printGrid(const grid_t &grid) {
    for (size_t i = 0; i < grid.height; i++) {
        for (size_t j = 0; j < grid.width; j++) {
            printCreatureGrid(grid.squares[i][j]);
        }
        cout << "\n";
    }
}
