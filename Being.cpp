#include <iostream>
#include "Constants.h"
#include "Being.h"
#include "Chromo.h"
#include "DNA.h"
#include "Commons.h"
#include "Food.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <boost/optional.hpp>

using namespace std;

int64_t being::N_beings = 0;

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);


being::being(boost::optional<being> b0) {

   if (b0) {

      mydna_    = b0->get_dna();
      age_      = b0->get_age();
      energy_   = b0->get_energy();
      ALIVE_    = b0->is_alive();
      x_        = b0->get_x();
      y_        = b0->get_y();
      prnts_    = b0->get_parents();
      ID_       = b0->get_id();
   };

   
};

void being::show() const {

   cout << "ID = " << ID_ << endl;
   cout << "Alive = " << ALIVE_ << endl;
   cout << "Age = " << age_ << endl;
   cout << "Energy = " << energy_ << endl;
   cout << "Position = " << "[" << x_ << "," << y_ << "]" << endl;
   cout << "Parents ID = " << "[" << prnts_.first << "," << prnts_.second << "]" << endl;
   cout << "DNA:" << endl;
   mydna_.show_dna(); 

};

   int64_t being::get_N_beings() const {
   return N_beings;
};


ostream& operator<<(ostream& os, const being& obj) {
   os << "ID = " << obj.get_id() << endl;
   os << "Alive = " << obj.is_alive() << endl;
   os << "Age = " << obj.get_age() << endl;
   os << "Energy = " << obj.get_energy() << endl;
   os << "Position = " << "[" << obj.get_x() << "," << obj.get_y() << "]" << endl;
   os << "Parents ID = " << "[" << obj.get_parents().first << "," << obj.get_parents().second << "]" << endl;
   os << "DNA:" << endl;
   os << obj.get_dna();
   
   return os;

};


being operator+(const being & lhs, const being& rhs) {

   DNA new_dna = lhs.get_dna() + rhs.get_dna();
   uniform_real_distribution<float> distribution_x(lhs.get_x(),rhs.get_x());
   float const new_x( distribution_x(generator) );
   uniform_real_distribution<float> distribution_y(lhs.get_y(),rhs.get_y());
   float new_y( distribution_y(generator) );
   being new_being(new_dna, 0 , starting_energy, true, new_x, new_y, lhs.get_id(), rhs.get_id());
   return new_being;
};


void being::move() {

   bool VERBOSE = true;
   float pmov_x = 0.0; 
   float pmov_y = 0.0;

   if (ALIVE_) {
      if (pmov_distr == "UNIFORM") {
      
         uniform_real_distribution<float> distribution_mov(-1 * max_move_1d , max_move_1d);
         pmov_x = distribution_mov(generator);
         //pmov_x = float(1200.0);
         pmov_y = distribution_mov(generator);
         //pmov_y = float(-1200.0);
      };
 
      float const resistance = get_dim() * epsdim; 
      float delta_x = pmov_x * max( epsath * get_athlet() - resistance, float(0.0) ) ;
      float delta_y = pmov_y * max( epsath * get_athlet() - resistance, float(0.0) ) ;
      x_ += delta_x ;
      y_ += delta_y ;
      if (x_ > X_MAX)  x_ = X_MIN + fmod( x_ , (X_MAX - X_MIN) ) ;
      if (x_ < X_MIN)  x_ = X_MAX - fmod( abs(x_) , (X_MAX - X_MIN) ) ;
      if (y_ > Y_MAX)  y_ = Y_MIN + fmod( y_ , (Y_MAX - Y_MIN) ) ;
      if (y_ < Y_MIN)  y_ = Y_MAX - fmod( abs(y_) , (Y_MAX - Y_MIN) ) ;

      float delta_enr = epsener * sqrt( pow(delta_x,2) + pow(delta_y,2) ) + epsener2 * get_dim() ;
      energy_ = energy_ - delta_enr ;

      if (VERBOSE)  cout << "Being " << ID_ << " : moved - " << pmov_x << "," << pmov_y << "," << delta_x << "," << delta_y << x_ << " , " << y_ << " - " << delta_enr << endl;

      if (energy_ < 0.0) { 
         ALIVE_ = false; 
         energy_ = 0.0;
         if (VERBOSE)  cout << "Being " << ID_ << " : died after move, energy = 0.0" << endl;
      };
      

   };
};


void being::eat(food_point& fp) {

   bool VERBOSE = true;

   if (ALIVE_) {
      float const dfp = dist( get_pos() , fp.get_pos() ) ;
      if ( float(get_dim()) >= dfp && fp.get_nutrival() > 0.0 ) {
         float const delta_nutri = epsnutri * fp.get_nutrival() ;  
         energy_ += delta_nutri ;
         fp.decrease_nutrival(delta_nutri) ;
         if (fp.get_nutrival() < 0.0) fp.set_nutrival(0.0) ;
         if (VERBOSE) cout << "Being " << ID_ << " eat food for " << delta_nutri << " calories" << "( " << dfp << ", " << get_dim() << " )" << endl;
      };
   };   

};

int get_compatibility(const being& lhs, const being& rhs) {
   int compat = 0;
   chromo l_beauty( lhs.get_dna().get_chromo(1) );
   chromo r_attracted( rhs.get_dna().get_chromo(5) );
   for (int ii = 0; ii < DIM; ++ii) {
      if (l_beauty.get_base(ii) !=  r_attracted.get_base(ii)) ++compat ;
   };

   return compat;
};

bool are_alive(const being& lhs, const being& rhs) {

   return (lhs.is_alive() && rhs.is_alive());

};

float dist(const being& lhs, const being& rhs) { 

return dist( lhs.get_pos() , rhs.get_pos() ) ; 

};


bool are_close_enough(const being& lhs, const being& rhs) {
   
   return dist(lhs,rhs) < float( lhs.get_dim() + rhs.get_dim() );

};

bool are_compatible(const being& lhs, const being& rhs) {

   uniform_real_distribution<float> distribution_rep(0 , 1);
   int const compat = get_compatibility(lhs,rhs);
   float prepr = epsrepr * ( float(compat) / float( lhs.get_beauty() ) ) ;
   float dice_roll = distribution_rep(generator);

   return distribution_rep(generator) < prepr;

};

boost::optional<being> reproduce(const being& lhs, const being& rhs) {

   bool VERBOSE = true;
   boost::optional<being> new_being;
 
   if ( are_alive(lhs,rhs) && are_close_enough(lhs,rhs) && are_compatible(lhs,rhs) ) { 
      if (VERBOSE) cout << "ID " << lhs.get_id() << " and ID " << rhs.get_id() << " were lucky, reproduction!" << endl;
      new_being = being(lhs + rhs);
   }
   else {
         if (false) cout << "They were not lucky, no reproduction." << endl;
   };        
   return new_being ;
};
   
void being::mutation() {

   uniform_real_distribution<float> distribution_mut(0 , 1);
   uniform_int_distribution<int> distribution_gene(0 , DIM - 1);
   int newval = 0;
   bool VERBOSE = true;

   if (ALIVE_) {
      if (chromo_affected == "ALL") {
         for (int ii=0; ii<CHROMO_NUMBER; ++ii) {
            float dice_roll = distribution_mut(generator);
            if (dice_roll < pmut) {
               if( muted_gene_selection == "UNIFORM") {
               int const ngene = distribution_gene(generator);
               if (mydna_.get_chromo(ii).get_base(ngene) == 0) newval = 1;
               else newval = 0;
               chromo newchromo(mydna_.get_chromo(ii));
               newchromo.set_base(ngene,newval);
               mydna_.set_chromo( newchromo , ii );
               if (VERBOSE) cout << "Being " << get_id() << " muted at chromo " << ii << " and gene " << ngene << " ( pmut = " << pmut << " dice = " << dice_roll << " )" << endl;
               };
            };
         };
      };
   };
};


void being::older(int n_old) {

   age_ = age_ + n_old;

};

void being::die(bool force_death) {

   bool VERBOSE = true;
   float pdie = 0.0;

   uniform_real_distribution<float> distribution_life(0 , 1);

   if (ALIVE_ && force_death) ALIVE_ = false;

   if (ALIVE_ && energy_ < 0.0) {
      ALIVE_ = false;
      if (VERBOSE) cout << "Being " << get_id() << " died at age = " << get_age()  << "( energy = " << get_energy() << " )" << endl;
   };

   if (ALIVE_){


      float life_dice = distribution_life(generator);
      if (age_ <= PROBABLE_AGE_LIMIT) pdie = epsage * (age_ / PROBABLE_AGE_LIMIT);
      else pdie = 1 - (epsage / (age_ - PROBABLE_AGE_LIMIT) );
      if (life_dice < pdie) {
         ALIVE_ = false;
         if (VERBOSE) cout << "Being " << get_id() << " died at age = " << get_age()  << "( " << pdie << "," << life_dice << " )" << endl;
      }
      else {
         if (VERBOSE) cout << "Being " << get_id() << " survived at age = " << get_age()  << "( " << pdie << "," << life_dice << " )" << endl;
      };
   };
};
