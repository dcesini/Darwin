#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <vector>
#include <string>
#include "Commons.h"
#include "Being.h"
#include "Food.h"
#include "Constants.h"
#include "Chromo.h"

class world {

   std::vector<food_point> food_;
   std_vector<being>       creatures_;
   long unsigned int N_generation_ ;

   public:

   world(long unsigned int N_being_init, int N_food_point_init);

   void create_food(long unsigned int N_food_point);
   void create_population(long unsigned int N_being);
   
   void load_food(std::string filename);
   void load_population(std::string filename);
   void save_food(std::string filename);
   void save_population(std::string filename);
   void save(std::string filename);
   void load(std::string filename);

   void add_being(const being& new_b);
   void remove_being();
   void add_food_point(const food_point& new_fp);

   void advance_one_generation(bool dump_to_file = false);
   void evolve(long unsigned int N_generations);

   const std_vector<being> creatures() { return creatures_; };
   const std_vector<food_point> food() { return food_; };

   long unsigned int age();
   long unsigned int N_beings();
   long unsigned int N_alive();
   float total_energy();
   long unsigned int N_food();
   void stats();

};







#endif
