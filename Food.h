#ifndef FOOD_POINT_H
#define FOOD_POINT_H

#include "Constants.h"
#include "Commons.h"
#include <iostream>

class food_point {

   point_2d pos_;
   float nutrival_;

   public:

      food_point(float x, float y);
      food_point(float x, float y, float nutri);
      food_point(const point_2d& p)
         : pos_(p) {}; 
      food_point();
      food_point(const food_point& other);
      point_2d get_pos() const ;
      float get_nutrival() const ;
      void set_nutrival(float val) ;
      void decrease_nutrival(float delta) ;
      void show_food() const;

};

std::ostream& operator<<(std::ostream& os, const food_point& obj);
#endif
