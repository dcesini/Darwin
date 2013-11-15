#include <iostream>
#include <vector>
#include <string>
#include "Commons.h"
#include "Being.h"
#include "Food.h"
#include "Constants.h"
#include "Chromo.h"
#include "World.h"
#include <boost/optional.hpp>
#include <algorithm> 
#include <numeric> 


world::world(int64_t N_being_init, int N_food_point_init) {

   food_.reserve(N_food_point_init);
   creatures_.reserve( 2 * N_being_init);
   N_generation_ = 0;

};

void world::add(being const& new_b) {

   creatures_.push_back(new_b);

};


void world::add(food_point const& new_fp) {

   food_.push_back(new_fp);

};

void world::remove_being() {

   creatures_.pop_back();

};

bool IsAlive(being const& b) { return b.is_alive(); };

int64_t world::N_alive() {

//   int64_t N = 0;
//   for(std::vector<being>::const_iterator i = first_b(); i!= last_b(); ++i){
//      if ( (*i).is_alive() ) ++N;
//   };

//   return N;
  
   int64_t N = count_if( creatures_.begin(), creatures_.end(), IsAlive );
   return N; 

};

float sum_nutri(food_point const& lhs, food_point const& rhs) { return lhs.get_nutrival() + rhs.get_nutrival(); };

float world::total_nutrival() {

   float tnutri = 0.0;
   for(std::vector<food_point>::const_iterator i = fp_begin(); i!= fp_end(); ++i){
      tnutri +=  i->get_nutrival();
   };
//   float tnutri = accumulate( food_.begin(), food_.end(), 0.0f, sum_nutri );
   return tnutri;

};

float world::total_energy() {

   float te = 0;
   for(std::vector<being>::const_iterator i = beings_begin(); i!=beings_end(); ++i){
      if (i->is_alive()) te += i->get_energy() ;
   };

   return te;
};

void world::advance_one_generation(bool dump_to_file) {

   std::vector<being>::iterator this_generation_beings_end = beings_end();
   std::vector<food_point>::iterator this_generation_fp_end = fp_end();

   for(std::vector<being>::iterator lhs_b = beings_begin(); lhs_b != this_generation_beings_end; ++lhs_b){

      lhs_b->move() ;

      for(std::vector<food_point>::iterator fp_i = fp_begin(); fp_i!=this_generation_fp_end; ++fp_i){
         lhs_b->eat( (*fp_i) ) ;
      };

   };

   for( std::vector<being>::iterator lhs_b = beings_begin(); lhs_b != this_generation_beings_end; ++lhs_b){

      for (std::vector<being>::iterator rhs_b = lhs_b; rhs_b != this_generation_beings_end; ++rhs_b){
          if (rhs_b!=lhs_b) {
             boost::optional<being> new_b = reproduce( (*lhs_b) , (*rhs_b) ) ;
             if (new_b) {
                being b2(new_b);
                add(b2); 
             };
          };
      };

      lhs_b->mutation() ;

      lhs_b->older() ;

      lhs_b->die() ;
   };
   
   ++N_generation_;

};


void world::evolve(int64_t N_gen) {
   
   bool VERBOSE = true;
   for (int64_t i = 0; i < N_gen; ++i) {

      advance_one_generation();
//      ++N_generation_;
      if (VERBOSE) stats(); 
      if ( N_alive() == 0 ) break;

   };

};


int64_t world::age_avg() {


   int64_t age_avg(0.0);
   for(std::vector<being>::iterator b = beings_begin(); b!=beings_end(); ++b){

      age_avg += (b->get_age()) ;

   };   //use accumulate

   return float(age_avg) / float(size());

};

void world::stats() {

   std::cout << "World Stats:" << std::endl;
   std::cout << "World Age = " << age() << std::endl;
   std::cout << "N Alive = " << N_alive() << std::endl;
   std::cout << "N beings alive or death = " << size() << std::endl;
   std::cout << "Total Energy = " << total_energy() << std::endl;
   std::cout << "Total Nutrival = " << total_nutrival() << std::endl;
   std::cout << "Total Food Points = " << N_food() << std::endl;
   std::cout << "Average Being Age = " << age_avg() << std::endl;

};
