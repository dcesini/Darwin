#include <iostream>
#include "Constants.h"
#include "Commons.h"
#include "Being.h"
#include "Chromo.h"
#include "Food.h"
#include "DNA.h"
#include "World.h"
#include "AutoRNG.h"
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "Read_world_from_file.h"
#include <string>
#include <stdlib.h>
#include <sstream>

std::string itostr(int i) {

   std::stringstream out;
   out << i;
   return out.str();

};


int main(int argc, char *argv[]) {
   std::string filename;
   std::string outfilename;
   std::string out_fp_filename;
   std::stringstream out;
   std::string s;
   std::ofstream outstr;
   std::ofstream out_fp_str;
   
   if (argc < 3) { 
      std::cout << "Usage: ./read.out <start_age> <end_age>" << std::endl;
      return 1;
   };
   int start = atoi(argv[1]);
   int end = atoi(argv[2]);
   for (int i = start; i < end + 1; ++i) {
      out << i;
      s = out.str();
      filename = "./DATA/" + s + ".txt";
      out.str( std::string() );
      out.clear();
      outfilename = filename + "_b_pos";
      outstr.open(outfilename);
      out_fp_filename = filename + "_fp_pos";
      out_fp_str.open(out_fp_filename);
    
      std::cout << "Processing age : " << itostr(i) << std::endl;
      world* newworld = read_world_from_file(filename);

//      newworld->stats();
      outstr << "=== Positions ===" << std::endl;
      out_fp_str << "=== Positions ===" << std::endl;
      for(std::vector<being>::iterator b = newworld->beings_begin(); b!=newworld->beings_end(); ++b){

//         std::cout << b->get_x() << " " << b->get_y() << " " << b->get_dim() << std::endl;
         if ( b->is_alive() ) {
            outstr << b->get_x() << " " << b->get_y() << " " << b->get_dim() << std::endl;
         };
      };

      for(std::vector<food_point>::iterator fp = newworld->food_begin(); fp!=newworld->food_end(); ++fp){

//         std::cout << b->get_x() << " " << b->get_y() << " " << b->get_dim() << std::endl;
         out_fp_str << fp->get_pos().get_x() << " " << fp->get_pos().get_y() << " " << fp->get_nutrival() << std::endl;
      }; 
   
      outstr << "=== End of Positions ===" << std::endl;
      out_fp_str << "=== End of Positions ===" << std::endl;
      outstr.close();
      out_fp_str.close();

};

   return 0;
};   

