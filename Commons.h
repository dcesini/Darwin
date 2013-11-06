#include<math.h>
#ifndef DARWIN_COMMONS_H
#define DARWIN_COMMONS_H 

class point_2d{
   float x_;
   float y_;
   public:
      point_2d(float a, float b)
         : x_(a) , 
           y_(b) {};
      point_2d() {x_ = 0.0; y_ = 0.0;};
      void set_x(float a)  { x_ = a; };
      void set_y(float b)  { y_ = b; };
      float get_x() const { return x_; };
      float get_y() const { return y_; };
      void show_point() const;
     
};

class Parents {
   long unsigned int  ID1_;
   long unsigned int  ID2_;
   public:
      Parents(long unsigned int& a, long unsigned int& b)
         : ID1_(a) ,
           ID2_(b) {};
      Parents() {ID1_ = 0; ID2_ = 0;};
      Parents(const Parents& p0) : ID1_(p0.ID1_) , ID2_(p0.ID2_) {} ;
      void set_ID1(long unsigned int a)  { ID1_ = a; };
      void set_ID2(long unsigned int b)  { ID2_ = b; };
      long unsigned int get_ID1() const { return ID1_; };
      long unsigned int get_ID2() const { return ID2_; };
      void show_parents() const;

};

float dist( point_2d const& p1 , point_2d const& p2);

#endif
