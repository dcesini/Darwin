#ifndef DNA_H
#define DNA_H

#include "Constants.h"
#include "Chromo.h"
#include <iostream>

using namespace std;

class DNA {

   chromo dn_[CHROMO_NUMBER];

   public:

      DNA();
      DNA(chromo const& charm_i, chromo const& beauty_i, chromo const& dim_i, chromo const& athlet_i, chromo const& karma_i, chromo const& attracted_i);

      DNA(const DNA& d1);

      DNA& operator=(const DNA &rhs);
      void show_dna() const;
      chromo get_chromo(int i) const;
      void set_chromo(chromo const& ch, int chromo_num);

};

ostream& operator<<(ostream& os, const DNA & obj);
DNA operator+(const DNA& lhs, const DNA& rhs);
#endif
