#include <iostream>
#include "Constants.h"
#include "Commons.h"
#include "Being.h"
#include "Chromo.h"
#include "Food.h"
#include "DNA.h"
#include "World.h"
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

extern "C" {

   world* read_world_from_file(std::string filename) {

   world* ptr = new world(10000,10000);
   
   std::ifstream ifs2(filename);
   boost::archive::text_iarchive ia(ifs2);
   ia >> *(ptr);

   return ptr;

}

};
