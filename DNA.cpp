#include "Constants.h"
#include "Chromo.h"
#include "DNA.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

DNA::DNA(){

   chromo a;
   for (int ii = 0; ii < CHROMO_NUMBER; ++ii)  dn_[ii] = a ;

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
   return *this;
};


void DNA::show_dna() const {
  for(int ii = 0; ii<CHROMO_NUMBER; ii++) dn_[ii].show_chromo();
};

bool operator== (DNA const& lhs , DNA const& rhs){

   for (int ii = 0; ii < CHROMO_NUMBER; ++ii) {
      if (!(lhs.get_chromo(ii) == rhs.get_chromo(ii))) return false;
   };

   return true;
}

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
