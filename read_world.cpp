#include <iostream>
#include "include/Constants.h"
#include "include/Commons.h"
#include "include/Being.h"
#include "include/Chromo.h"
#include "include/Food.h"
#include "include/DNA.h"
#include "include/World.h"
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
