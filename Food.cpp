#include "Food.h"
#include "Constants.h"
#include "Commons.h"
#include <iostream>

using namespace std;

point_2d food_point::get_pos() const { return pos_; };

float food_point::get_nutrival() const { return nutrival_; };

void food_point::set_nutrival(float val) { nutrival_ = val; };

void food_point::decrease_nutrival(float delta) { nutrival_ = nutrival_ - delta; };

void food_point::show_food() const {
   cout << "Pos = ";
   pos_.show_point();
   cout << " - Nutrival = "  << nutrival_ << endl;
};

ostream& operator<<(ostream& os, const food_point& obj) {

   os << "Pos = " << "[" << obj.get_pos().get_x() << "," << obj.get_pos().get_y() << "]" << " - Nutrival = "  << obj.get_nutrival();
   return os;

};
