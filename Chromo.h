#ifndef CHROMO_H
#define CHROMO_H

#include "Constants.h"
#include <iostream>

using namespace std;

class chromo {

    short int ch_[DIM];
//    char name[];

    public:

       chromo();
       chromo(const chromo& c1);
       chromo(const short int c1[DIM]);
       chromo& operator=(const chromo &rhs);
       void show_chromo() const;
       void set_base(int pos, short int val);
       short int get_base(int pos) const;
       int sum_chromo() const;
};

ostream& operator<<(ostream& os, const chromo& obj);

chromo chromo_mix(chromo const& lhs, chromo const& rhs);

chromo operator+(chromo const& lhs, chromo const& rhs);

#endif
