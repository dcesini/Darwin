#ifndef AUTORNG_H
#define AUTORNG_H

#include "Constants.h"
#include "Constants_wrapper.h"
#include "Commons.h"
#include <iostream>
#include <random>


class InitRNG {
public:
    std::mt19937 generator;
    InitRNG() {
        generator.seed(12345);
    };

    void seed(unsigned seed_) { 
       if (seed_ != 0) 
       {
          generator.seed(seed_); 
       }
       else
       {
          generator.seed(std::random_device());
       }
   }
};

#endif
