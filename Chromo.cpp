#include "include/Constants.h"
#include "include/Constants_wrapper.h"
#include "include/Chromo.h"
#include <iostream>
#include <string>
#include <sstream>


std::string chromo::REPRODUCTION_METHOD = "";


chromo::chromo(){
   for(int i = 0; i < DIM ; ++i) ch_[i] = 0;
   REPRODUCTION_METHOD = "SEGMENTS_EXCHANGE";
};

chromo::chromo(const short int ch_ii[DIM]) {

   for(int i = 0; i < DIM ; i++) ch_[i] = ch_ii[i];
   REPRODUCTION_METHOD = "SEGMENTS_EXCHANGE";
};

chromo::chromo(const chromo& c1) {

   for(int i = 0; i < DIM ; i++) ch_[i] = c1.get_base(i);
   REPRODUCTION_METHOD = "SEGMENTS_EXCHANGE";
};


void chromo::set_base(int pos, short int val) {

   if((pos >= 0) && (pos < DIM))
   {
      ch_[pos] = val;
   }   
   else
   {
      std::cout << "Error(chromo::set_base): pos outside limits";
   }
};

short int chromo::get_base(int pos) const {

   if((pos >= 0) && (pos < DIM))
   {
      return ch_[pos];
   }  
   else
   {
      std::cout << "Error(chromo::get_pos): pos outside limits";
      return -1;
   }
};


chromo& chromo::operator=(const chromo &rhs) {
   
   for(int i = 0; i < DIM ; i++) ch_[i] = rhs.ch_[i];
   return *this;
};

bool operator== (chromo const& lhs , chromo const& rhs){

   for (int ii = 0; ii < DIM; ++ii) {
      if (!(lhs.get_base(ii) == rhs.get_base(ii))) return false;
   };

   return true;
}

void chromo::show_chromo() const {
std::string s;
std::string Result;
s = "";
for(int ii = 0; ii < CHROMO_SEGMENTS; ii++) {
   s = s + "[";
   for(int jj = 0; jj < SEGMENTS_LENGHT; jj++) {
 
      std::ostringstream convert;   // stream used for the conversion
      convert << ch_[ ii*SEGMENTS_LENGHT + jj];      // insert the textual representation of 'Number' in the characters in the stream
      Result = convert.str(); // set 'Result' to the contents of the stream
      if(jj == SEGMENTS_LENGHT - 1) s = s + Result ;
      else s = s + Result + ",";
      }
   if(ii == CHROMO_SEGMENTS - 1) s = s + "]";
   else s = s + "] + ";
   }


std::cout << s << std::endl;
};


std::ostream& operator<<(std::ostream& os, const chromo& obj) {

for(int ii = 0; ii < CHROMO_SEGMENTS; ++ii) {
   os << "[";
   std::string Result;

   for(int jj = 0; jj < SEGMENTS_LENGHT; jj++) {

      std::ostringstream convert;   // stream used for the conversion
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
   std::string REPRODUCTION_METHOD(lhs.repr_method());
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
