Darwin
======



## Synopsis

Darwin is a genetic simulation software.
It simulates a 2D world populated by beings that move, eat, reproduce and die according to laws of life.

Low of life are defined in the darwin.cfg file.

Each being is composed by N chromosomes - each of which is composed by M DNA segments represented by sequences of binary numbers. Chromo.h and DNA.h defines the chromosomes of the beings.

Each being has an age, an energy, a position, be dead or alive, can be inhibited for reproduction. Beings.h define its characteristics and the actions that a being can do.

The world is also populated by energy sources for a being or food point. When a being encounter a food point it can eat and increase its energy. When the being moves its energy is decreased. When the energy reach zero the poor being dies. Food.h define characteristics of food points.

When too beings encounter they have a certain probability to reproduce mixing their chromosomes according to the law of life.

The simulation should select generation of better beings given the law of lives and the characteristics of the world.

## Installation

To run a simulation, configure the world with darwing.cfg, make clean, make all, ./darwin.out

Output is very verbose by default, to have a better output:
./darwin.out | grep -A 10 "World Stats:"

Utils directory contains utilities to inspect the output files and visualize the world.

To enable output file writing dump_to_file should be set to true:
include/World.h:   void advance_one_generation(bool dump_to_file = false);


The following environment works:
SL6
gcc 4.9.1
boost-1.56


## License

Apache 2.0
