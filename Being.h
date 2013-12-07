#ifndef BEING_H
#define BEING_H

#include "Constants.h"
#include "Constants_wrapper.h"
#include "Chromo.h"
#include "DNA.h"
#include "Commons.h"
#include "Food.h"
#include "AutoRNG.h"
#include <iostream>
#include <utility>
#include <boost/optional.hpp>
#include <fstream>
#include <random>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>


typedef std::pair<int64_t, int64_t> Parents;

class being{
   
   friend class boost::serialization::access;
   friend   bool are_compatible(const being& lhs, const being& rhs);
   static int64_t N_beings;

   int ID_;
   DNA mydna_;
   int age_;
   float energy_;
   bool ALIVE_;
   float x_;
   float y_;
   Parents prnts_;
   static constants_wrapper cfg;
   unsigned seed_;
   template<class Archive>
   void serialize(Archive & ar, const unsigned int version)
   {
        ar & ID_;
        ar & mydna_;
        ar & age_;
        ar & energy_;
        ar & ALIVE_;
        ar & x_;
        ar & y_;
        ar & prnts_;

    };


public:
   
   static InitRNG RNG;

   being(const DNA& dna1, int age, float  energy, bool ALIVE, float x, float y, int64_t pID1, int64_t pID2) :
      ID_(N_beings)      ,
      mydna_(dna1)       ,
      age_(age)          ,
      energy_(energy)    ,
      ALIVE_(ALIVE)      ,
      x_(x)              ,
      y_(y)              ,
      prnts_(std::make_pair(pID1 , pID2))             
      { 
      N_beings++ ;
      } ;

   being(const being& b0) :
      mydna_(b0.get_dna())       ,
      age_(b0.get_age())         ,
      energy_(b0.get_energy())   ,
      ALIVE_(b0.is_alive())     ,
      x_(b0.get_x())             , 
      y_(b0.get_y())             ,
      prnts_(b0.get_parents())   ,
      ID_(N_beings)  {N_beings++ ;};

   being(boost::optional<being> b0);

   being() :
   energy_(cfg.starting_energy)      ,
   ALIVE_(true)                  ,
   x_(0.0)                       ,
   y_(0.0)                       ,
   prnts_(std::make_pair(0,0))        ,
   ID_(N_beings)              
   { 
       chromo ch;
       for (int ii = 0 ; ii < CHROMO_NUMBER; ++ii) {
           mydna_.set_chromo(ch,ii);
       };
       N_beings++ ;

   };

   void configure(constants_wrapper const& conf);
   unsigned seed() {return seed_ ;};
   constants_wrapper get_cfg() const { return cfg; };
   int64_t get_N_beings() const;
   int get_id() const { return ID_; };
   int get_age() const { return age_; };
   float get_energy() const { return energy_; };
   void set_energy(float new_energy) { energy_ = new_energy; };
   bool is_alive() const { return ALIVE_; };
   float get_x() const { return x_; };
   float get_y() const { return y_; };
   void  set_x(float x) { x_ = x; };
   void  set_y(float y) { y_ = y; };
   point_2d get_pos() const { point_2d pos; pos.set_x(x_); pos.set_y(y_); return pos;};
   Parents get_parents() const { return prnts_; };
   DNA get_dna() const { return mydna_; };
   int get_charm()     const { return mydna_.get_chromo(0).sum_chromo(); };
   int get_beauty()    const { return mydna_.get_chromo(1).sum_chromo(); };
   int get_dim()       const { return mydna_.get_chromo(2).sum_chromo(); };
   int get_athlet()    const { return mydna_.get_chromo(3).sum_chromo(); };
   int get_karma()     const { return mydna_.get_chromo(4).sum_chromo(); };
   int get_attracted() const { return mydna_.get_chromo(5).sum_chromo(); };
   void show() const;
   void move();
   void mutation();
   void eat(food_point& fp);
   void die(bool force_death = false);
   void older(int n_old = 1);

}; 

std::ostream& operator<<(std::ostream& os, const being& obj);

being operator+(const being & lhs, const being& rhs);
boost::optional<being> reproduce(const being& lhs, const being& rhs);
int get_compatibility(const being& lhs, const being& rhs);
bool are_alive(const being& lhs, const being& rhs); 
 
bool are_close_enough(const being& lhs, const being& rhs);
bool are_compatible(const being& lhs, const being& rhs);

float dist(const being& lhs, const being& rhs); 
#endif
