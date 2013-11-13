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



world::world(int64_t N_being_init, int N_food_point_init) {

   food_.reserve(N_food_point_init);
   creatures_.reserve( 2 * N_being_init);
   N_generation_ = 0;

};

void world::add(being const& new_b) {

   creatures_.push_back(new_b);

};


void world::add(boost::optional<being> const& new_b) {

   if(new_b) {
      being b = new_b;
      creatures_.push_back(b);
   };

};


void world::add(food_point const& new_fp) {

   food_.push_back(new_fp);

};

void world::remove_being() {

   creatures_.pop_back();

};

int64_t world::N_alive() {

   int64_t N = 0;
   for(std::vector<being>::const_iterator i = first_b(); i!= last_b(); ++i){
      if ( (*i).is_alive() ) ++N;
   };

   return N;

};

float world::total_nutrival() {

   float tnutri = 0.0;
   for(std::vector<food_point>::const_iterator i = first_fp(); i!= last_fp(); ++i){
      tnutri += (*i).get_nutrival();
   };

   return tnutri;

};

float world::total_energy() {

   float te = 0;
   for(std::vector<being>::const_iterator i = first_b(); i!=last_b(); ++i){
      te += (*i).get_energy() ;
   };

   return te;
};

void world::advance_one_generation(bool dump_to_file) {

   for(std::vector<being>::iterator lhs_b = first_b(); lhs_b!=last_b(); ++lhs_b){

      (*lhs_b).move() ;

      for(std::vector<food_point>::iterator fp_i = first_fp(); fp_i!=last_fp(); ++fp_i){
         (*lhs_b).eat( (*fp_i) ) ;
      };

   };

   for( std::vector<being>::iterator lhs_b = first_b(); lhs_b!=last_b() - 1 ; ++lhs_b){

      for (std::vector<being>::iterator rhs_b = lhs_b + 1; rhs_b!=last_b(); ++rhs_b){
          boost::optional<being> new_b = reproduce( (*lhs_b) , (*rhs_b) ) ;
          add(new_b);
      };

      (*lhs_b).mutation() ;

      (*lhs_b).older() ;

      (*lhs_b).die() ;
   };

};


void world::evolve(int64_t N_gen) {
   
   int64_t i = 0;
   while ( i < N_gen) {

      advance_one_generation();
      ++i;
      ++N_generation_;
      
      if ( N_alive() == 0 ) break;

   };

};
