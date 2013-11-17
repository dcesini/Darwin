#include<math.h>
#ifndef DARWIN_COMMONS_H
#define DARWIN_COMMONS_H 
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


class point_2d{

   friend class boost::serialization::access;
   float x_;
   float y_;

   template<class Archive>
   void serialize(Archive & ar, const unsigned int version)
   {
        ar & x_;
        ar & y_;
    };


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

float dist( point_2d const& p1 , point_2d const& p2);

#endif
