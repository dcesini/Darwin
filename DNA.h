#ifndef DNA_H
#define DNA_H

#include "Constants.h"
#include "Chromo.h"
#include <iostream>

class DNA {

   chromo dn_[CHROMO_NUMBER];

   public:

      DNA();
      DNA(chromo const& charm_i, chromo const& beauty_i, chromo const& dim_i, chromo const& athlet_i, chromo const& karma_i, chromo const& attracted_i) :
         dn_ { charm_i , beauty_i ,dim_i , athlet_i , karma_i , attracted_i}  {};

      DNA(const DNA& d1);

      DNA& operator=(const DNA &rhs);
      void show_dna() const;
      chromo get_chromo(int i) const;
      void set_chromo(chromo const& ch, int chromo_num);

};

std::ostream& operator<<(std::ostream& os, const DNA & obj);
DNA operator+(const DNA& lhs, const DNA& rhs);
#endif
