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
//#include "Read_world_from_file.h"

extern "C" {

   world* read_world_from_file(std::string filename) {

   world* ptr = new world(1000,1000);
   
   std::ifstream ifs2(filename);
   boost::archive::text_iarchive ia(ifs2);
   ia >> *(ptr);

   return ptr;

}

};

/*
int main() {

   std::string filename;

   filename = std::string("./DATA/200.txt");
   
   world* newworld = read_world_from_file();

   newworld->stats();

   return 0;
};   


*/