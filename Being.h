#ifndef BEING_H
#define BEING_H

#include "Constants.h"
#include "Chromo.h"
#include "DNA.h"
#include "Commons.h"
#include "Food.h"
#include <iostream>
#include <utility>
#include <boost/optional.hpp>

typedef std::pair<long unsigned int, long unsigned int> Parents;

class being{

   static long unsigned int N_beings;

   int ID_;
   DNA mydna_;
   int age_;
   float energy_;
   bool ALIVE_;
   float x_;
   float y_;
   Parents prnts_;


public:
 
   being(const DNA& dna1, int age, float  energy, bool ALIVE, float x, float y, long unsigned int pID1, long unsigned int pID2) :
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



   being() :

   energy_(starting_energy)      ,
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

   long unsigned int get_N_beings() const;
   int get_id() const { return ID_; };
   int get_age() const { return age_; };
   float get_energy() const { return energy_; };
   void set_energy(float new_energy) { energy_ = new_energy; };
   bool is_alive() const { return ALIVE_; };
   float get_x() const { return x_; };
   float get_y() const { return y_; };
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


#endif
