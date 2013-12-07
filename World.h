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
#include <boost/optional.hpp>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/assume_abstract.hpp>

class world {

   friend class boost::serialization::access;
   std::vector<food_point> food_;
   std::vector<being>      creatures_;
   int64_t N_generation_ ;
   std::string name_;
   static constants_wrapper cfg;

   template<class Archive>
   void serialize(Archive & ar, const unsigned int version)
   {
        ar & food_;
        ar & creatures_;
        ar & N_generation_;
        ar & name_;
    };

   public:

   world(int64_t N_being_init, int N_food_point_init);
   void configure(constants_wrapper const& conf) { cfg = conf; };
//   void create_food(int64_t N_food_point);
//   void create_population(int64_t N_being);
   
   std::vector<being>::iterator beings_begin()  { return creatures_.begin(); };
   std::vector<being>::iterator beings_end()   { return creatures_.end(); };
   std::vector<food_point>::iterator food_begin() { return food_.begin(); };
   std::vector<food_point>::iterator food_end()  { return food_.end(); };

   std::vector<being>::const_iterator beings_begin()  const { return creatures_.begin(); };
   std::vector<being>::const_iterator beings_end() const  { return creatures_.end(); };
   std::vector<food_point>::const_iterator food_begin() const { return food_.begin(); };
   std::vector<food_point>::const_iterator food_end()  const { return food_.end(); };
 


   void load_food(std::string const& filename);
   void load_population(std::string const& filename);
   void save_food(std::string const& filename);
   void save_population(std::string const& filename);
   void save(std::string const& filename);
   void load(std::string const& filename);

   void add(being const& new_b);
   void remove_being();
   void add(const food_point& new_fp);

   void advance_one_generation(bool dump_to_file = false);
   void evolve(int64_t N_generations);

   std::vector<being> creatures() { return creatures_; };
   const std::vector<food_point> food() { return food_; };

   int64_t age() { return N_generation_; };
   int64_t size() { return creatures_.size(); } ;
   float age_avg();
   int64_t N_alive();
   float total_energy();
   float total_nutrival();
   int64_t N_food() { return food_.size(); };
   void stats();
   void name(std::string const& Name) { name_ = Name; };
   std::string name() { return name_; };

};


#endif
