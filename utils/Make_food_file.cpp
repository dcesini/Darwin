#include <iostream>
#include "Constants.h"
#include "Constants_wrapper.h"
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


int main() {

   constants_wrapper cfg;
   cfg.show();
   InitRNG RNG;
   RNG.seed(cfg.SEED);

   //food_point fp2(4.1, 4.2, cfg.default_nutrival);
   //food_point fp3(1.1, 2.2, cfg.default_nutrival);
   
   // create and open a character archive for output
   std::ofstream ofs("./my_food_points.txt");
   boost::archive::text_oarchive oa(ofs);

   std::uniform_real_distribution<float> food_distribution_x(cfg.X_MIN , cfg.X_MAX / 4 );
   std::uniform_real_distribution<float> food_distribution_y(cfg.Y_MIN , cfg.Y_MAX);
   for (int i = 0; i < cfg.N_FOOD_POINT_AT_START / 2 ; ++i) {
      food_point fpx( food_distribution_x(RNG.generator) , food_distribution_y(RNG.generator) , cfg.default_nutrival );

   // save data to archive
   // write class instance to archive
      oa << fpx;
   // archive and stream closed when destructors are called
    };
   float new_min_x = cfg.X_MAX - (cfg.X_MAX / 4);
   float new_max_x = cfg.X_MAX;
   float new_min_y = cfg.Y_MIN;
   float new_max_y = cfg.Y_MAX;
   std::cout << new_min_x << " ; " << new_max_x << " ; " << new_min_y << " ; " << new_max_y << std::endl;
   std::uniform_real_distribution<float> food_distribution_x_2(new_min_x , new_max_x );
   std::uniform_real_distribution<float> food_distribution_y_2(new_min_y , new_max_y );
   
   for (int i = cfg.N_FOOD_POINT_AT_START / 2; i < cfg.N_FOOD_POINT_AT_START; ++i) {
      food_point fpx( food_distribution_x_2(RNG.generator) , food_distribution_y_2(RNG.generator) , cfg.default_nutrival );
         
   // save data to archive
   // write class instance to archive
      oa << fpx;
   // archive and stream closed when destructors are called
    };

   return 0;
};
