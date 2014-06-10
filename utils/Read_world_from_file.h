#ifndef READ_WORLD_H
#define READ_WORLD_H

#include "Constants.h"
#include "Commons.h"
#include <iostream>
#include <fstream>
#include "World.h"
#include <string>

extern "C" world* read_world_from_file(std::string filename);
#endif
