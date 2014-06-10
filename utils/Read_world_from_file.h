#ifndef READ_WORLD_H
#define READ_WORLD_H

#include "include/Constants.h"
#include "include/Commons.h"
#include <iostream>
#include <fstream>
#include "include/World.h"
#include <string>

extern "C" world* read_world_from_file(std::string filename);
#endif
