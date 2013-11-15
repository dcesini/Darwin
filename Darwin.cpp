#include <iostream>
#include "Constants.h"
#include "Commons.h"
#include "Being.h"
#include "Chromo.h"
#include "Food.h"
#include "DNA.h"
#include "World.h"
#include <vector>
#include <random>
#include <chrono>

using namespace std;

int main() {



   cout << "X_MIN = " << X_MIN << endl;
   cout << "X_MAX = " << X_MAX << endl;
   cout << "Y_MIN = " << Y_MIN << endl;
   cout << "Y_MAX = " << Y_MAX << endl;

   cout << "READ_FOOD_FROM_FILE = " << READ_FOOD_FROM_FILE << endl;
   cout << "FOOD_POINT_DISTRIBUTION = " << FOOD_POINT_DISTRIBUTION << endl;


   chromo beauty_d(beauty_default);
   chromo dim_d(dim_default);
   chromo athlet_d(athlet_default);
   chromo karma_d(karma_default);
   chromo attracted_d(attracted_default);
   chromo charm_d(charm_default);

   DNA dna1(charm_d, beauty_d, dim_d, athlet_d, karma_d, attracted_d);
   DNA dna2(charm_d, beauty_d, dim_d, athlet_d, karma_d, attracted_d);
   //dna2.set_chromo(c1,5);

   being b1(dna1, 0, starting_energy, true, 1.0, 2.0, 0, 0);
   //b1.show();
   being b2(dna2, 0, 100, true, 2.0, 2.0, 0, 0);

   food_point fp2(4.1,4.2);
   food_point fp3(1.1,2.2);

   world myworld(1000,1000);
   //myworld.add(b1);
   //myworld.add(b2);
   //myworld.add(fp2);
   //myworld.add(fp3);
   //myworld.stats();
   //myworld.advance_one_generation();
   //myworld.stats();


   vector<int> iv;
   iv.reserve(10);
   for (int i=0; i<10; ++i) iv.push_back(i);

   vector<int>::iterator iv_end = iv.end();
   for (vector<int>::iterator it = iv.begin(); it!=iv_end; ++it) {
      cout << *it << endl;
      iv.push_back(11);
   }


   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
   default_random_engine generator(seed);
   if (BEINGS_START_DISTRIBUTION == "UNIFORM") {
      uniform_real_distribution<float> beings_distribution_x(X_MIN , X_MAX);
      uniform_real_distribution<float> beings_distribution_y(Y_MIN , Y_MAX);
      for (int i = 0; i < N_BEINGS; ++i) {
         b1.set_x(beings_distribution_x(generator));
         b1.set_y(beings_distribution_y(generator));
         myworld.add(b1) ;
      };
   };

   if (FOOD_POINT_DISTRIBUTION == "UNIFORM") {
      uniform_real_distribution<float> food_distribution_x(X_MIN , X_MAX);
      uniform_real_distribution<float> food_distribution_y(Y_MIN , Y_MAX);
      for (int i = 0; i < N_FOOD_POINT_AT_START; ++i) {
         food_point fpx( food_distribution_x(generator) , food_distribution_y(generator) , default_nutrival );
         myworld.add(fpx) ;
      };
   };


   myworld.stats();
   myworld.evolve(1000000);

   return 0;
};
