#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/any.hpp>
#include "Constantes.h"


//used to handle constants, in particular those that are not needed at compile time and that can be read from a cfg file
// avoiding recompilation all the times

// used boost::program_option to parse the file
//in the conf file comments are possible with a #
//data are stored in the  po::variables_map vm_, if different from those stored in teh global variables, global variables will be modified

// save will recreated a cfg file with a different anme for future reference a re-submit of hte same run

namespace po = boost::program_options;

class constants_wrapper() {

   private:
     
      po::variables_map vm_;

   public:
   
      constants_wrapper(std::string const& filename = "darwin.cfg");
      void read(std::string const& filename = "darwin.cfg");
      void save(std::string const& filename = "darwin.cfg.bak");
      void set(std:string const& var_name , boost::any var_value);
      void get(std::string const& var_name);
      void show();

      bool is_empty(const boost::any & operand)    { return operand.empty(); }
      bool is_int(const boost::any & operand)      { return operand.type() == typeid(int); }
      bool is_double(const boost::any & operand)   { return operand.type() == typeid(double); }
      bool is_char_ptr(const boost::any & operand) {
        try {
           boost::any_cast<const char *>(operand);
           return true;
        }
        catch(const boost::bad_any_cast &) {
           return false;
        }  
      }    

      bool is_string(const boost::any & operand)   { return boost::any_cast<std::string>(&operand); }

};
