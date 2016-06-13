#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <numeric> 
#include <fstream>
#include <chrono>
#include <omp.h>
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>
#include "include/Commons.h"
#include "include/Being.h"
#include "include/Food.h"
#include "include/Constants.h"
#include "include/Chromo.h"
#include "include/World.h"

world::world(int64_t N_being_init, int N_food_point_init) {

   food_.reserve(N_food_point_init);
   creatures_.reserve( 2 * N_being_init);
   dead_creatures_.reserve( 2 * N_being_init );
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
#pragma omp parallel for reduction(+:tnutri)

//   for(std::vector<food_point>::const_iterator i = food_begin(); i!= food_end(); ++i){
//      tnutri +=  i->get_nutrival();
//   };

     for(int64_t i = 0 ; i < world::N_food() ; ++i){
        tnutri += food_[i].get_nutrival();
} 

//   float tnutri = accumulate( food_.begin(), food_.end(), 0.0f, sum_nutri );
   return tnutri;

};

float world::total_energy() {

   float te = 0;
#pragma omp parallel for reduction(+:te)

// loop for serial execution
//   for(std::vector<being>::const_iterator i = beings_begin(); i!=beings_end(); ++i){
//      if (i->is_alive()) te += i->get_energy() ;
//   };
// end serial loop

//loop for openmp
for(int64_t i = 0 ; i < world::size(); ++i) {
   if(creatures_[i].is_alive()) te += creatures_[i].get_energy() ;
}
//end loop for openmp
//
   return te;
};

void world::dead_burial() {

   std::vector<being> tmp_alive;
   tmp_alive.reserve( N_alive() );
   for(std::vector<being>::iterator b = beings_begin(); b != beings_end(); ++b){

      if (b->is_alive()) 
      {
         tmp_alive.push_back( (*b) );
      }
      else
      {
         dead_creatures_.push_back( (*b) );
      }
   }

   creatures_ = tmp_alive;

};



void world::advance_one_generation(bool dump_to_file) {

   std::vector<being>::iterator this_generation_beings_end = beings_end();
   std::vector<food_point>::iterator this_generation_fp_end = food_end();

   int64_t creatures_end = size();
   std::string extension(".txt");
   std::string data_path("./DATA/");

   //for(std::vector<being>::iterator lhs_b = beings_begin(); lhs_b != this_generation_beings_end; ++lhs_b){
   std::cout << "Moving and feeding creatures..." << std::endl;
   std::chrono::time_point<std::chrono::high_resolution_clock> start_mov = std::chrono::high_resolution_clock::now();
#pragma omp parallel for
   for(int64_t ii = 0; ii < creatures_end ; ++ii){

      creatures_[ii].move() ;

      for(std::vector<food_point>::iterator fp_i = food_begin(); fp_i!=this_generation_fp_end; ++fp_i){
         creatures_[ii].eat( (*fp_i) ) ;
      };

   };
   std::chrono::time_point<std::chrono::high_resolution_clock> end_mov = std::chrono::high_resolution_clock::now();
   std::cout << "Timing for move and eat = " << std::chrono::duration_cast<std::chrono::milliseconds>(end_mov - start_mov).count() << "ms." << std::endl;
   
   std::cout << "Time to reproduce, mute and get older for  creatures..."  << std::endl;
   std::chrono::time_point<std::chrono::high_resolution_clock> start_rep = std::chrono::high_resolution_clock::now();
#pragma omp parallel for
   for( int64_t ii = 0; ii < creatures_end ; ++ii ){
      int nclose = 0;
      for ( int64_t jj = ii ; jj < creatures_end ; ++jj){
          if (are_close_enough(creatures_[ii] , creatures_[jj])) ++nclose;
          if ( ii != jj ) {
#pragma omp critical
{
             boost::optional<being> new_b = reproduce( creatures_[ii] , creatures_[jj] ) ;
             if (new_b) {
                being b2(new_b);
                add(b2); 
}
             };
          };
      };
      if (nclose > 4) creatures_[ii].make_inhibited();
      else creatures_[ii].remove_inhibition();
      creatures_[ii].mutation();
      creatures_[ii].older();
      creatures_[ii].die();
   };
   std::chrono::time_point<std::chrono::high_resolution_clock> end_rep = std::chrono::high_resolution_clock::now();
   std::cout << "Timing for reproduction, mutation and get older = " << std::chrono::duration_cast<std::chrono::milliseconds>(end_rep - start_rep).count() << "ms." << std::endl;


   std::cout << "Time for dead burial (RIP)..." << std::endl;
   std::chrono::time_point<std::chrono::high_resolution_clock> start_bur = std::chrono::high_resolution_clock::now();

   dead_burial();

   std::chrono::time_point<std::chrono::high_resolution_clock> end_bur = std::chrono::high_resolution_clock::now();
   std::cout << "Timing for dead burial = " << std::chrono::duration_cast<std::chrono::milliseconds>(end_bur - start_bur).count() << "ms." << std::endl;
   
   ++N_generation_;
   std::string s = boost::lexical_cast<std::string>( N_generation_ );
   
   if (dump_to_file) save(data_path + s + extension);

};


void world::evolve(int64_t N_gen) {
   
   bool VERBOSE = true;
   std::string gen_str;
   std::chrono::time_point<std::chrono::high_resolution_clock> start_1gen;
   std::chrono::time_point<std::chrono::high_resolution_clock> end_1gen;
   for (int64_t i = 0; i < N_gen; ++i) {
      gen_str = boost::lexical_cast<std::string>( i );
      bool file_dump(true);
      start_1gen = std::chrono::high_resolution_clock::now();
      advance_one_generation(file_dump);
      end_1gen = std::chrono::high_resolution_clock::now();
      std::cout << "Timing for one generation ( " << gen_str << " ) evolution = " << std::chrono::duration_cast<std::chrono::milliseconds>(end_1gen - start_1gen).count() << "ms." << std::endl;
//      ++N_generation_;
      if (VERBOSE) stats(); 
      if ( N_alive() == 0 ) break;

   };

};


float world::age_avg() {


   float age_avg(0.0);
   for(std::vector<being>::iterator b = beings_begin(); b!=beings_end(); ++b){

      if ( b->is_alive() ) age_avg += b->get_age() ;

   };   //use accumulate

   float N = float(N_alive());
   if (N !=0) {
      return float(age_avg) / float(N_alive());
   } 
   else {
      return 0;
   };
};

void world::stats() {

   std::cout << "World Stats:" << std::endl;
   std::cout << "World Age = " << age() << std::endl;
   std::cout << "N Alive = " << N_alive() << std::endl;
   std::cout << "N beings alive or dead = " << size() + N_dead() << std::endl;
   std::cout << "N dead dead_creatures = " << N_dead() << std::endl; 
   std::cout << "Total Energy = " << total_energy() << std::endl;
   std::cout << "Total Nutrival = " << total_nutrival() << std::endl;
   std::cout << "Total Food Points = " << N_food() << std::endl;
   std::cout << "Average Being Age = " << age_avg() << std::endl;

};

void world::save(std::string const& filename) {

      // create and open a character archive for output
   std::ofstream ofs2(filename);
   // save data to archive
    {
        boost::archive::text_oarchive oa(ofs2);
        // write class instance to archive
        oa << (*this);
        // archive and stream closed when destructors are called
    }


};


void world::load(std::string const& filename) {

   world newworld(1,1);
   std::ifstream ifs2(filename);
   boost::archive::text_iarchive ia(ifs2);
   ia >> (*this);

};

