#include "Constants.h"
#include "Chromo.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

chromo::chromo(){
   for(int i = 0; i < DIM ; ++i) ch_[i] = 0;
};

chromo::chromo(const short int ch_ii[DIM]) {

   for(int i = 0; i < DIM ; i++) ch_[i] = ch_ii[i];

};

chromo::chromo(const chromo& c1) {

   for(int i = 0; i < DIM ; i++) ch_[i] = c1.get_base(i);


};


void chromo::set_base(int pos, short int val) {

   if((pos >= 0) && (pos < DIM))
   {
      ch_[pos] = val;
   }   
   else
   {
      cout << "Error(chromo::set_pos): pos outside limits";
   }
};

short int chromo::get_base(int pos) const {

   if((pos >= 0) && (pos < DIM))
   {
      return ch_[pos];
   }  
   else
   {
      cout << "Error(chromo::get_pos): pos outside limits";
      return -1;
   }
};


chromo& chromo::operator=(const chromo &rhs) {
   
   for(int i = 0; i < DIM ; i++) ch_[i] = rhs.ch_[i];
   return *this;
};

void chromo::show_chromo() const {
string s;
string Result;
s = "";
for(int ii = 0; ii < CHROMO_SEGMENTS; ii++) {
   s = s + "[";
   for(int jj = 0; jj < SEGMENTS_LENGHT; jj++) {
 
      ostringstream convert;   // stream used for the conversion
      convert << ch_[ ii*SEGMENTS_LENGHT + jj];      // insert the textual representation of 'Number' in the characters in the stream
      Result = convert.str(); // set 'Result' to the contents of the stream
      if(jj == SEGMENTS_LENGHT - 1) s = s + Result ;
      else s = s + Result + ",";
      }
   if(ii == CHROMO_SEGMENTS - 1) s = s + "]";
   else s = s + "] + ";
   }


cout << s << endl;
};


ostream& operator<<(ostream& os, const chromo& obj) {

for(int ii = 0; ii < CHROMO_SEGMENTS; ++ii) {
   os << "[";
   string Result;

   for(int jj = 0; jj < SEGMENTS_LENGHT; jj++) {

      ostringstream convert;   // stream used for the conversion
      convert << obj.get_base(ii*SEGMENTS_LENGHT + jj);      // insert the textual representation of 'Number' in the characters in the stream
      Result = convert.str(); // set 'Result' to the contents of the stream
      if(jj == SEGMENTS_LENGHT - 1) os << Result ;
      else os << Result << ",";
      }
   if(ii == CHROMO_SEGMENTS - 1) os << "]";
   else os << "] + ";
   }

return os;
};


chromo chromo_mix(chromo const& lhs, chromo const& rhs) {

   chromo new_chromo;

   if (REPRODUCTION_METHOD == "SEGMENTS_EXCHANGE") {

      for(int jj = 0; jj < (CHROMO_SEGMENTS * SEGMENTS_LENGHT) / 2; ++jj) {
         new_chromo.set_base(jj,rhs.get_base(jj)); 
      }
      for(int jj = (CHROMO_SEGMENTS * SEGMENTS_LENGHT) / 2; jj < DIM; ++jj) {
         new_chromo.set_base(jj,lhs.get_base(jj));
      }

  }

  return new_chromo;
};

chromo operator+(chromo const& lhs, chromo const& rhs) {

   return chromo_mix(lhs, rhs);

};

int chromo::sum_chromo() const {

   int sum(0);
   for (int ii = 0; ii < DIM; ++ii) sum = sum + ch_[ii];
   return sum;

};
