#ifndef FOOD_POINT_H
#define FOOD_POINT_H

#include "Constants.h"
#include "Commons.h"
#include <iostream>

class food_point {

   point_2d pos_;
   float nutrival_;

   public:

      food_point(float x, float y):
         pos_(x,y) ,
         nutrival_(default_nutrival) {};

      food_point(float x, float y, float nutri) :
         pos_(x,y) ,
         nutrival_(nutri) {};

      food_point(const point_2d& p)
         : pos_(p) , nutrival_(default_nutrival) {}; 

      food_point(const point_2d& p , float nutri)
         : pos_(p) , nutrival_(nutri) {};

      food_point()
         : pos_(0.0,0.0) , nutrival_(default_nutrival) {};

      food_point(const food_point& other)
         : pos_(other.pos_) , nutrival_(other.nutrival_) {};


      point_2d get_pos() const ;
      float get_nutrival() const ;
      void set_nutrival(float val) ;
      void decrease_nutrival(float delta) ;
      void show_food() const;

};

std::ostream& operator<<(std::ostream& os, const food_point& obj);
#endif
