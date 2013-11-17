#ifndef CHROMO_H
#define CHROMO_H

#include "Constants.h"
#include <iostream>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class chromo {

    friend class boost::serialization::access;
    short int ch_[DIM];

   template<class Archive>
   void serialize(Archive & ar, const unsigned int version)
   {
        ar & ch_;
    };

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

std::ostream& operator<<( std::ostream& os, const chromo& obj);

chromo chromo_mix(chromo const& lhs, chromo const& rhs);

chromo operator+(chromo const& lhs, chromo const& rhs);

bool operator== (chromo const& lhr, chromo const& rhs);

#endif
