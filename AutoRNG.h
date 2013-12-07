#ifndef AUTORNG_H
#define AUTORNG_H

#include "Constants.h"
#include "Constants_wrapper.h"
#include "Commons.h"
#include <iostream>
#include <random>


class InitRNG {
public:
    std::default_random_engine generator;
    InitRNG() {
        generator.seed(12345);
    };

    void seed(unsigned seed_) { generator.seed(seed_); };
};

#endif
