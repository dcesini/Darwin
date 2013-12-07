#ifndef CONS_WRAPPER_H
#define CONS_WRAPPER_H

#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/any.hpp>
#include "Constants.h"


//used to handle constants, in particular those that are not needed at compile time and that can be read from a cfg file
// avoiding recompilation all the times

// used boost::program_option to parse the file
//in the conf file comments are possible with a #
//data are stored in the  po::variables_map vm_, if different from those stored in teh global variables, global variables will be modified

// save will recreated a cfg file with a different anme for future reference a re-submit of hte same run

namespace po = boost::program_options;

class constants_wrapper {

   private:
     
      po::variables_map vm_;
   
   public:
    
      int SEED;
      float X_MIN;
      float X_MAX;
      float Y_MIN;
      float Y_MAX;
      bool READ_FOOD_FROM_FILE;
      float default_nutrival;
      int N_FOOD_POINT_AT_START;
      std::string FOOD_POINT_DISTRIBUTION; 
      bool ENABLE_RADIACTIVE_SOURCES;
      int N_RAD_SOURCES_AT_START;
      float default_rad;
      bool READ_POPULATION_FROM_FILE;
      int N_BEINGS;
      std::string BEINGS_START_DISTRIBUTION;
      std::string SOURCES_DISTRIBUTION;
      int ITER_NUMBER;
      std::string FIRST_BEING_IN_LOOP;
      int starting_age;
      float x_default;
      float y_default;
      float starting_energy;
      float epsath;
      float epsdim;
      float max_move_1d;
      float epsener;
      float epsener2;
      float epsrepr;
      std::string pmov_distr;
      float epsnutri;
      int PROBABLE_AGE_LIMIT;
      float epsage;
      std::string REPRODUCTION_METHOD;
      float pmut;
      std::string muted_gene_selection;
      std::string food_file;
      std::string rad_file;
      bool READ_RAD_FROM_FILE;
      std::string beings_file;
      std::string world_init_file_name;
      std::string fout_name;
      std::string chromo_affected;

   
      constants_wrapper();
      void read( po::options_description& desc_ ,
                 std::string const& filename = "darwin.cfg");
      void save(std::string const& filename = "darwin.cfg.bak");
      void set(std::string const& var_name , boost::any var_value);
      void get(std::string const& var_name);
      void show();
      constants_wrapper configure() { return *this; };
      bool is_empty(const boost::any & operand)    { return operand.empty(); }
      bool is_int(const boost::any & operand)      { return operand.type() == typeid(int); }
      bool is_double(const boost::any & operand)   { return operand.type() == typeid(double); }
      bool is_float(const boost::any & operand)   { return operand.type() == typeid(float); }
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



/*      float X_MIN()                             { return X_MIN; };
      float X_MAX()                             { return X_MAX; };
      float Y_MIN()                             { return Y_MIN; };
      float X_MAX()                             { return Y_MAX; }; 
      bool READ_FOOD_FROM_FILE()                { return READ_FOOD_FROM_FILE; };
      float default_nutrival()                  { return default_nutrival; };
      int N_FOOD_POINT_AT_START()               { return N_FOOD_POINT_AT_START; };
      std::string FOOD_POINT_DISTRIBUTION()     { return FOOD_POINT_DISTRIBUTION; }; 
      bool ENABLE_RADIACTIVE_SOURCES()          { return ENABLE_RADIACTIVE_SOURCES; };
      int N_RAD_SOURCES_AT_START()              { return N_RAD_SOURCES_AT_START; };
      float default_rad()                       { return default_rad; };
      bool READ_POPULATION_FROM_FILE()          { return READ_POPULATION_FROM_FILE; };
      int N_BEINGS()                            { return N_BEINGS; };
      std::string BEINGS_START_DISTRIBUTION()   { return BEINGS_START_DISTRIBUTION; };
      std::string SOURCES_DISTRIBUTION()        { return SOURCES_DISTRIBUTION; };
      int ITER_NUMBER()                         { return ITER_NUMBER; };
      std::string FIRST_BEING_IN_LOOP()         { return FIRST_BEING_IN_LOOP; };
      int starting_age()                        { return starting_age; };
      float x_default()                         { return x_default; };
      float y_default()                         { return y_default; };
      float starting_energy()                   { return starting_energy; };
      float epsath()                            { return epsath; };
      float epsdim()                            { return epsdim; };
      float max_move_1d()                       { return max_move_1d; };
      float epsener()                           { return epsener; };
      float epsener2()                          { return epsener2; };
      std::string pmov_distr()                  { return pmov_distr; };
      float epsnutri()                          { return epsnutri; };
      int PROBABLE_AGE_LIMIT()                  { return PROBABLE_AGE_LIMIT; };
      float epsage()                            { return epsage; };
      std::string REPRODUCTION_METHOD()         { return REPRODUCTION_METHOD; };
      float pmut()                              { return pmut; };
      std::string muted_gene_selection()        { return muted_gene_selection; };
      std::string chromo_affected()             { return chromo_affected; };
      std::string food_file()                   { return food_file; };
      std::string rad_file()                    { return rad_file; };
      bool READ_RAD_FROM_FILE()                 { return READ_RAD_FROM_FILE; };
      std::string beings_file()                 { return beings_file; };
      std::string world_init_file_name()        { return world_init_file_name; };
      std::string fout_name()                   { return fout_name; };

*/
};


#endif
