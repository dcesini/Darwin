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


using namespace std;

long unsigned int being::N_beings = 0;

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);



being::being(const DNA& dna1, int age_i, float energy_i, bool ALIVE_i, float x_i, float y_i, int pID1_i, int pID2_i) {

   
   ID_ = N_beings;
   mydna_ = dna1;   
   age_ = age_i;
   energy_ = energy_i;
   ALIVE_ = ALIVE_i;
   x_ = x_i;
   y_ = y_i;
   parentID_[0] = pID1_i;
   parentID_[1] = pID2_i;
   N_beings++ ;

   cout << "Created being with ID = " << ID_ << endl;
};

being::being() {
   chromo ch;
   for (int ii = 0 ; ii < CHROMO_NUMBER; ++ii) {
      mydna_.set_chromo(ch,ii);
   };
   energy_ = starting_energy;
   ALIVE_ = true;
   x_ = 0.0;
   y_ = 0.0;
   parentID_[0] = 0;
   parentID_[1] = 0;
   ID_ = N_beings;
   N_beings++ ;
};

being::being(const being& b0) {

   
   mydna_ = b0.get_dna();
   age_ = b0.get_age();
   energy_ = b0.get_energy();
   ALIVE_ = b0.get_alive();
   x_ = b0.get_x();
   y_ = b0.get_y();
   parentID_[0] = b0.get_parentID()[0];
   parentID_[1] = b0.get_parentID()[1];
   ID_ = N_beings;
   N_beings++ ;

};

void being::show() const {

   cout << "ID = " << ID_ << endl;
   cout << "Alive = " << ALIVE_ << endl;
   cout << "Age = " << age_ << endl;
   cout << "Energy = " << energy_ << endl;
   cout << "Position = " << "[" << x_ << "," << y_ << "]" << endl;
   cout << "Parents ID = " << "[" << parentID_[0] << "," << parentID_[1] << "]" <<endl;
   cout << "DNA:" << endl;
   mydna_.show_dna(); 

};

long unsigned int being::get_N_beings() const {
   return N_beings;
};


ostream& operator<<(ostream& os, const being& obj) {
   os << "ID = " << obj.get_id() << endl;
   os << "Alive = " << obj.get_alive() << endl;
   os << "Age = " << obj.get_age() << endl;
   os << "Energy = " << obj.get_energy() << endl;
   os << "Position = " << "[" << obj.get_x() << "," << obj.get_y() << "]" << endl;
   os << "Parents ID = " << "[" << obj.get_parentID()[0] << "," << obj.get_parentID()[1] << "]" << endl;
   os << "DNA:" << endl;
   DNA dna1 = obj.get_dna();
   os << dna1;
   
   return os;

};


being operator+(const being & lhs, const being& rhs) {

   DNA new_dna;
   new_dna = lhs.get_dna() + rhs.get_dna();
   uniform_real_distribution<float> distribution_x(lhs.get_x(),rhs.get_x());
   float dice_roll = distribution_x(generator);
   float new_x(dice_roll);
   uniform_real_distribution<float> distribution_y(lhs.get_y(),rhs.get_y());
   dice_roll = distribution_y(generator);
   float new_y(dice_roll);
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
 
      float resistance = get_dim() * epsdim; 
      float delta_x = pmov_x * max( epsath * get_athlet() - resistance, float(0.0) ) ;
      float delta_y = pmov_y * max( epsath * get_athlet() - resistance, float(0.0) ) ;
      x_ = x_ + delta_x ;
      y_ = y_ + delta_y ;
      if (x_ > X_MAX)  x_ = X_MIN + fmod( x_ , (X_MAX - X_MIN) ) ;
      if (x_ < X_MIN)  x_ = X_MAX - fmod( abs(x_) , (X_MAX - X_MIN) ) ;
      if (y_ > Y_MAX)  y_ = Y_MIN + fmod( y_ , (Y_MAX - Y_MIN) ) ;
      if (y_ < Y_MIN)  y_ = Y_MAX - fmod( abs(y_) , (Y_MAX - Y_MIN) ) ;

      energy_ = energy_ - epsener * sqrt( pow(delta_x,2) + pow(delta_y,2) ) - epsener2 * get_dim() ;

      if (VERBOSE)  cout << "Being " << ID_ << " : moved - " << pmov_x << "," << pmov_y << "," << delta_x << "," << delta_y << endl;

      if (energy_ < 0.0) { 
         ALIVE_ = false; 
         if (VERBOSE)  cout << "Being " << ID_ << " : died after move" << endl;
      };
      

   };
};


void being::eat(food_point& fp) {

   float dfp, delta_nutri;
   bool VERBOSE = true;

   if (ALIVE_) {
      dfp = dist( get_pos() , fp.get_pos() ) ;
      if ( float(get_dim()) >= dfp && fp.get_nutrival() > 0.0 ) {
         delta_nutri = epsnutri * fp.get_nutrival() ;  
         energy_ = energy_ + delta_nutri ;
         fp.decrease_nutrival(delta_nutri) ;
         if (fp.get_nutrival() < 0.0) fp.set_nutrival(0.0) ;
         if (VERBOSE) cout << "Being " << ID_ << " eat food for " << delta_nutri << " calories" << endl;
      };
   };   

};

int get_compatibility(const being& lhs, const being& rhs) {
   int compat = 0;
   chromo l_beauty( lhs.get_dna().get_chromo(1) );
   chromo r_attracted( rhs.get_dna().get_chromo(5) );
   for (int ii = 0; ii < DIM; ++ii) {
      if (l_beauty.get_base(ii) !=  r_attracted.get_base(ii)) compat = compat + 1 ;
   };

   return compat;
};


being* reproduce(const being& lhs, const being& rhs) {
   
   float dbs, prepr, dice_roll;
   int compat;
   uniform_real_distribution<float> distribution_rep(0 , 1);
   bool VERBOSE = true;
   being* new_being_ptr = NULL;
  
   if (lhs.get_alive() && rhs.get_alive() ) {
      dbs = dist( lhs.get_pos() , rhs.get_pos() ) ;
      if (dbs < float( lhs.get_dim() + rhs.get_dim() ) ) {
         compat = get_compatibility(lhs,rhs);
         prepr = epsrepr * ( float(compat) / float( lhs.get_beauty() ) ) ;
         dice_roll = distribution_rep(generator);
         if (dice_roll < prepr) {
            if (VERBOSE) cout << "They were lucky, reproduction! ("  << dbs << "," << compat << "," << prepr << "," << dice_roll << ")" << endl;
            new_being_ptr = new (nothrow) being(lhs + rhs) ;
         }
         else {
            if (VERBOSE) cout << "They were not lucky, no reproduction." << dbs << "," << compat << "," << prepr << "," << dice_roll << ")" << endl;
         }        
      };
   };
   
   return new_being_ptr;
};

void being::mutation() {

   uniform_real_distribution<float> distribution_mut(0 , 1);
   uniform_int_distribution<int> distribution_gene(0 , DIM);
   int newval = 0, ngene = 0;
   bool VERBOSE = true;
   float dice_roll = 1.0;

   if (ALIVE_) {
      if (chromo_affected == "ALL") {
         for (int ii=0; ii<CHROMO_NUMBER; ++ii) {
            dice_roll = distribution_mut(generator);
            if (dice_roll < pmut) {
               if( muted_gene_selection == "UNIFORM") {
               ngene = distribution_gene(generator);
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
