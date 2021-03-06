#include <iostream>
#include "include/Constants.h"
#include "include/Constants_wrapper.h"
#include "include/Commons.h"
#include "include/Being.h"
#include "include/Chromo.h"
#include "include/Food.h"
#include "include/DNA.h"
#include "include/World.h"
#include "include/AutoRNG.h"
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


//using namespace std;

int main() {
   constants_wrapper cfg;
   cfg.show();
   InitRNG RNG;
   RNG.seed(cfg.SEED);
   int a(0);
   if (!a) std::cout << "TRUEEEEE!!!" << std::endl;
   std::cout << std::endl << std::endl;
   std::cout << "X_MIN = " << cfg.X_MIN << std::endl;
   std::cout << "X_MAX = " << cfg.X_MAX << std::endl;
   std::cout << "Y_MIN = " << cfg.Y_MIN << std::endl;
   std::cout << "Y_MAX = " << cfg.Y_MAX << std::endl;

   std::cout << "READ_FOOD_FROM_FILE = " << cfg.READ_FOOD_FROM_FILE << std::endl;
   std::cout << "FOOD_POINT_DISTRIBUTION = " << cfg.FOOD_POINT_DISTRIBUTION << std::endl;


   chromo beauty_d(beauty_default);
   chromo dim_d(dim_default);
   chromo athlet_d(athlet_default);
   chromo karma_d(karma_default);
   chromo attracted_d(attracted_default);
   chromo charm_d(charm_default);

   DNA dna1(charm_d, beauty_d, dim_d, athlet_d, karma_d, attracted_d);
   DNA dna2(attracted_d, beauty_d, dim_d, athlet_d, karma_d, attracted_d);
   //dna2.set_chromo(c1,5);
   if (dna1 == dna2)  {
      std::cout << "TRUE1" << std::endl;
   } else { std::cout << "qualche problema" << std::endl;
     };
   
   being conf_being(dna1, 0, cfg.starting_energy, true, 1.0, 2.0, 0, 0);
   conf_being.configure(cfg);
   being b1(dna1, 0, cfg.starting_energy, true, 1.0, 2.0, 0, 0);
   //b1.show();
   being b2(dna2, 0, 100, true, 2.0, 2.0, 0, 0);

   food_point fp2(4.1, 4.2, cfg.default_nutrival);
   food_point fp3(1.1, 2.2, cfg.default_nutrival);

   point_2d p1(1,1);
   point_2d p2(2,2);

   // create and open a character archive for output
   std::ofstream ofs("./points.txt");
   // save data to archive
    {
        boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        oa << p1;
        oa << p2;
        oa << beauty_d;
        oa << dna1;
        oa << b1;
    	// archive and stream closed when destructors are called
    }


    // ... some time later restore the class instance to its orginal state
    point_2d p1new;
    point_2d p2new;
    chromo new_beauty;
    DNA dna1new;
    being b1new;

    {
        // create and open an archive for input
        std::ifstream ifs("./points.txt");
        boost::archive::text_iarchive ia(ifs);
        // read class state from archive
        ia >> p1new;
        ia >> p2new;
        ia >> new_beauty;
        ia >> dna1new;
        ia >> b1new;
        // archive and stream closed when destructors are called
    }

   std::cout << "P1new = ";
   p1new.show_point();
   std::cout << std::endl;

   std::cout << "P2new = ";
   p2new.show_point();
   std::cout << std::endl;

   std::cout << "new beauty = " << new_beauty << std::endl;
   std::cout << "newdna1 = " << dna1new << std::endl;

   if (dna1 == dna1new) std::cout << "TRUE!" << std::endl;

   std::cout << "B1NEW = " << std::endl << b1new << std::endl;

   world myworld(cfg.N_BEINGS,cfg.N_FOOD_POINT_AT_START);
   myworld.name("MyWorld");
   std::cout << "World name = " << myworld.name() << std::endl;
   
   //myworld.add(b1);
   //myworld.add(b2);
   //myworld.add(fp2);
   //myworld.add(fp3);
   //myworld.stats();
   //myworld.advance_one_generation();
   //myworld.stats();

//   myworld.load("DATA/200.txt");
//   myworld.stats();
//   myworld.evolve(1);
//   myworld.stats();

   std::vector<int> iv;
   iv.reserve(10);
   for (int i=0; i<10; ++i) iv.push_back(i);

   std::vector<int>::iterator iv_end = iv.end();
   for (std::vector<int>::iterator it = iv.begin(); it!=iv_end; ++it) {
      std::cout << *it << std::endl;
      iv.push_back(11);
   }

   if (cfg.BEINGS_START_DISTRIBUTION == "UNIFORM") {
      std::uniform_real_distribution<float> beings_distribution_x(cfg.X_MIN , cfg.X_MAX);
      std::uniform_real_distribution<float> beings_distribution_y(cfg.Y_MIN , cfg.Y_MAX);
      for (int i = 0; i < cfg.N_BEINGS; ++i) {
         b1.set_x(beings_distribution_x(RNG.generator));
         b1.set_y(beings_distribution_y(RNG.generator));
         myworld.add(b1) ;
      };
   };

   std::cout << "READ_FOOD_FROM_FILE = " << cfg.READ_FOOD_FROM_FILE << std::endl;
   if (!cfg.READ_FOOD_FROM_FILE) 
   {
      std::cout << "Creating food point from scratch" << std::endl;
      if (cfg.FOOD_POINT_DISTRIBUTION == "UNIFORM") {
         std::uniform_real_distribution<float> food_distribution_x(cfg.X_MIN , cfg.X_MAX);
         std::uniform_real_distribution<float> food_distribution_y(cfg.Y_MIN , cfg.Y_MAX);
         for (int i = 0; i < cfg.N_FOOD_POINT_AT_START; ++i) {
            food_point fpx( food_distribution_x(RNG.generator) , food_distribution_y(RNG.generator) , cfg.default_nutrival );
            myworld.add(fpx) ;
         }
      }
   }
   else 
   {
      std::cout << "Reading food points from file = " << cfg.food_file << std::endl;
      // create and open an archive for input
      std::ifstream ifs2(cfg.food_file);
      boost::archive::text_iarchive ia(ifs2);
      food_point newfp;
      // read class state from archive
      for (int i=0; i<cfg.N_FOOD_POINT_AT_START; ++i) {
         ia >> newfp;
         myworld.add(newfp);
      }
   };
  

   myworld.stats();

   //return 0;
   std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
   start = std::chrono::high_resolution_clock::now();
   myworld.evolve(cfg.ITER_NUMBER);
   end = std::chrono::high_resolution_clock::now();
   cfg.save("myworld.cfg");
   std::cout << "World evolved in = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms." << std::endl;
/*
   // create and open a character archive for output
   std::ofstream ofs2("./world.txt");
   // save data to archive
    {
        boost::archive::text_oarchive oa(ofs2);
        // write class instance to archive
        oa << myworld;
        // archive and stream closed when destructors are called
    }



    world newworld(1000,1000);


    {
        // create and open an archive for input
        std::ifstream ifs2("./world.txt");
        boost::archive::text_iarchive ia(ifs2);
        // read class state from archive
        ia >> newworld;
        // archive and stream closed when destructors are called
    }


   newworld.stats();
*/
   return 0;
};
