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
   int64_t N_generation_ ;

   public:

   world(int64_t N_being_init, int N_food_point_init);

   void create_food(int64_t N_food_point);
   void create_population(int64_t N_being);
   
   void load_food(std::string const& filename);
   void load_population(std::string const& filename);
   void save_food(std::string const& filename);
   void save_population(std::string const& filename);
   void save(std::string const& filename);
   void load(std::string const& filename);

   void add(const being& new_b);
   void remove_being();
   void add(const food_point& new_fp);

   void advance_one_generation(bool dump_to_file = false);
   void evolve(int64_t N_generations);

   std_vector<being> creatures() { return creatures_; };
   const std_vector<food_point> food() { return food_; };

   int64_t age();
   int64_t N_beings();
   int64_t N_alive();
   float total_energy();
   int64_t N_food();
   void stats();

};


#endif
