#include "Constants.h"
#include "Chromo.h"
#include "DNA.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

DNA::DNA(){

   chromo a;
   dn_[0] = a;
   dn_[1] = a;
   dn_[2] = a;
   dn_[3] = a;
   dn_[4] = a;
   dn_[5] = a;


};
 
DNA::DNA(chromo const & charm_i, chromo const & beauty_i, chromo const & dim_i, chromo const & athlet_i, chromo const & karma_i, chromo const & attracted_i) {

   dn_[0] = charm_i;
   dn_[1] = beauty_i;
   dn_[2] = dim_i;
   dn_[3] = athlet_i;
   dn_[4] = karma_i;
   dn_[5] = attracted_i;

};

DNA::DNA(const DNA& d1) {

   for (int ii = 0; ii < CHROMO_NUMBER; ++ii)  dn_[ii] = d1.get_chromo(ii);

};
 
chromo DNA::get_chromo(int i) const {

   return dn_[i];

};

void DNA::set_chromo(chromo const& ch, int chromo_num) {

   if (chromo_num >= 0 && chromo_num < DIM) dn_[chromo_num] = ch;

};


DNA& DNA::operator=(const DNA &rhs) {
   for(int ii = 0; ii<CHROMO_NUMBER; ii++) dn_[ii] = rhs.dn_[ii];
};


void DNA::show_dna() const {
  for(int ii = 0; ii<CHROMO_NUMBER; ii++) dn_[ii].show_chromo();
};



ostream& operator<<(ostream& os, const DNA& obj) {

   for(int ii = 0; ii<CHROMO_NUMBER; ii++) {
      if (ii == CHROMO_NUMBER - 1)    os << obj.get_chromo(ii);
      else os << obj.get_chromo(ii) << endl;
   };

   return os;

};

DNA operator+(const DNA& lhs, const DNA& rhs) {

   DNA new_dna(lhs.get_chromo(0) + rhs.get_chromo(0), 
               lhs.get_chromo(1) + rhs.get_chromo(1), 
               lhs.get_chromo(2) + rhs.get_chromo(2),
               lhs.get_chromo(3) + rhs.get_chromo(3),
               lhs.get_chromo(4) + rhs.get_chromo(4),
               lhs.get_chromo(5) + rhs.get_chromo(5)); 
   return new_dna;
};
