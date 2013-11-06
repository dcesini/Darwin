#include "Commons.h"
#include <iostream>

using namespace std;

void point_2d::show_point() const {
   cout << "[" << x_ << "," << y_ << "]";
};

float dist( const point_2d& p1 , const point_2d& p2) {
   float d;
   d = sqrt( pow((p2.get_x() - p1.get_x()),2) + pow((p2.get_y()-p1.get_y()),2));
   return d;
};

