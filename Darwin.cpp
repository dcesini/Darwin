#include <iostream>
#include "Constants.h"
#include "Commons.h"
#include "Being.h"
#include "Chromo.h"
#include "Food.h"
#include "DNA.h"
#include <vector>

using namespace std;

int main() {

   cout << "X_MIN = " << X_MIN << endl;
   cout << "X_MAX = " << X_MAX << endl;
   cout << "Y_MIN = " << Y_MIN << endl;
   cout << "Y_MAX = " << Y_MAX << endl;

   cout << "READ_FOOD_FROM_FILE = " << READ_FOOD_FROM_FILE << endl;
   cout << "FOOD_POINT_DISTRIBUTION = " << FOOD_POINT_DISTRIBUTION << endl;


   point_2d p1(1,1);
   point_2d p2(2,2);
   cout << "Distanza = " << dist(p1,p2) << endl;
   cout << "charm_default : " << endl;
   for (int ii = 0; ii< DIM; ii++) cout << charm_default[ii];
   cout << endl;
   chromo charm_d(charm_default);
   cout << "charm_d : " << endl;
   cout << "Chromo with show_chromo : ";
   charm_d.show_chromo();
   cout << " Chomo with operator overloaded : " << charm_d << endl;

   chromo beauty_d(beauty_default);
   chromo dim_d(dim_default);
   chromo athlet_d(athlet_default);
   chromo karma_d(karma_default);
   chromo attracted_d(attracted_default);

   const short int arra1[DIM] = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1};
   chromo c1(arra1);
   cout << "Mixing " << attracted_d << "    and    " << c1 << endl;
   chromo cnew( chromo_mix(attracted_d, c1) );
   cout << "cnew = " << cnew << endl;

   cout << "cnew with + " << attracted_d + c1 << endl;

   DNA dna1(charm_d, beauty_d, dim_d, athlet_d, karma_d, attracted_d);
   DNA dna2(charm_d, beauty_d, dim_d, athlet_d, karma_d, attracted_d);
   dna2.set_chromo(c1,5);
   cout << "DNA1 = " << dna1 << endl;
   cout << "DNA1 = " << endl;
   dna1.show_dna(); 
   cout << "DNA2 = " << dna2 << endl;

   DNA dna3(dna1 + dna2) ;
   cout << "DNA3 = " << dna3 << endl;

   being b1(dna1, 0, 100, true, 1.0, 2.0, 0, 0);
   b1.show();
   cout << "printing b1 with operator << " << endl;
   cout << b1 << endl;
   being b2(dna2, 0, 100, true, 2.0, 2.0, 0, 0);
   b2.show();
   being b3;
   b3 = b1 + b2;
   cout << "B3" << endl;
   cout << b3 << endl;


   b3.move();
   cout << "B3 after move" << endl << b3;



   cout << "We have a total of " << b1.get_N_beings() << " beings" << endl;

   food_point fp2(4.1,4.2);
   cout << "FP2 created" << endl;
   fp2.show_food();
   cout << "FP2 with overloaded operator : " << fp2 << endl; 
   food_point fp3(1.1,2.2,10.1);
   cout << "FP3 created" << endl;
   fp3.show_food();

   food_point fp1(fp3);
   cout << "fp3" << fp3 << endl;
   vector<food_point> food_list;
   vector<food_point>::iterator it;

//   food_list.push_back(fp1);
   food_list.push_back(fp2);
   food_list.push_back(fp3);
   for(it = food_list.begin(); it != food_list.end(); ++it)  it->show_food();

   b1.eat(fp2) ;
   cout << "FP2 : " << fp2 << endl;

   being* b4_ptr = reproduce(b1,b2) ;
   if(b4_ptr) (*b4_ptr).show();


   cout << "B3" << endl << b3 << endl;;
   b3.mutation();
   cout << "B3 after mutation" << endl << b3 << endl;


//   cout << "B4" << endl << b4 << endl;

 
   return 0;
};
