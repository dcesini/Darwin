#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <boost/any.hpp>
#include "Constants.h"
#include "Constants_wrapper.h"

namespace po = boost::program_options;

void constants_wrapper::read( po::options_description& desc_ , 
                              std::string const& cfg_file_name )  {

  std::ifstream settings_file( cfg_file_name );
  // Clear the map.
  vm_ = po::variables_map();
  po::store( po::parse_config_file( settings_file , desc_ ), vm_ );
  settings_file.close();
  po::notify( vm_ );    

};

/*
bool constants_wrapper::is_empty(const boost::any & operand) {
     return operand.empty();
};

bool constants_wrapper::is_int(const boost::any & operand) {
     return operand.type() == typeid(int);
};

bool constants_wrapper::is_double(const boost::any & operand) {
     return operand.type() == typeid(double);
};

bool constants_wrapper::is_char_ptr(const boost::any & operand) {
     try {
        boost::any_cast<const char *>(operand);
        return true;
     }
     catch(const boost::bad_any_cast &) {
        return false;
     }  
};

bool constants_wrapper::is_string(const boost::any & operand) {
     return boost::any_cast<std::string>(&operand);
};
*/

constants_wrapper::constants_wrapper() {
  
  po::options_description desc_("Options");
  // Setup options.
  desc_.add_options()
    ("SEED", po::value< int >( &SEED ), "Initial seed" );
   desc_.add_options()
    ("X_MIN", po::value< float >( &X_MIN ), "World X_MIN" );
  desc_.add_options()
    ("X_MAX", po::value< float >( &X_MAX ), "World X_MAX" );
  desc_.add_options()
    ("Y_MIN", po::value< float >( &Y_MIN ), "World Y_MIN" );
  desc_.add_options()
    ("Y_MAX", po::value< float >( &Y_MAX ), "World Y_MAX" );
  desc_.add_options()
    ("READ_FOOD_FROM_FILE", po::value< int >( &READ_FOOD_FROM_FILE ), "Get food points positions from the food_file" );
  desc_.add_options()
    ("default_nutrival", po::value< float >( &default_nutrival ), "default_nutrival" );
  desc_.add_options()
    ("N_FOOD_POINT_AT_START", po::value< int >( &N_FOOD_POINT_AT_START ), "Number of food point at start" );
  desc_.add_options()
    ("FOOD_POINT_DISTRIBUTION", po::value< std::string >( &FOOD_POINT_DISTRIBUTION ), "Type of food point distribution [Available: UNIFORM]" );
  desc_.add_options()
    ("ENABLE_RADIACTIVE_SOURCES", po::value< int >( &ENABLE_RADIACTIVE_SOURCES ), "ENABLE_RADIACTIVE_SOURCES" );
  desc_.add_options()
    ("N_RAD_SOURCES_AT_START", po::value< int >( &N_RAD_SOURCES_AT_START ), "N_RAD_SOURCES_AT_START" );
  desc_.add_options()
    ("default_rad", po::value< float >( &default_rad ), "radioactive sources activity at start" );
  desc_.add_options()
    ("READ_POPULATION_FROM_FILE", po::value< int >( &READ_POPULATION_FROM_FILE ), "Get radiaoactive sources from a file" );
  desc_.add_options()
    ("N_BEINGS", po::value< int >( &N_BEINGS ), "Number of beings at the beginning" );
  desc_.add_options()
    ("BEINGS_START_DISTRIBUTION", po::value< std::string >( &BEINGS_START_DISTRIBUTION ), "Type of beings distribution at the beginning [Available:UNIFORM]" );
  desc_.add_options()
    ("SOURCES_DISTRIBUTION", po::value< std::string >( &SOURCES_DISTRIBUTION ), "Type of the distribution of radioactive sources [Available: UNIFORM]" );
  desc_.add_options()
    ("ITER_NUMBER", po::value< int >( &ITER_NUMBER ), "Max Number of generations to run" );
  desc_.add_options()
    ("FIRST_BEING_IN_LOOP", po::value< std::string >( &FIRST_BEING_IN_LOOP ), "Distribution of the first Being considered in the evolving loop, not using for now" );
//  desc_.add_options()
//    ("CHROMO_NUMBER", po::value< int >( &CHROMO_NUMBER ), "Number of chromosomes in each being. CANNOT BE CHANGED!!!" );
//  desc_.add_options()
//    ("CHROMO_SEGMENTS", po::value< int >( &CHROMO_SEGMENTS ), "Numberof segments in each chromsome. Cannot be changed!!" );
//  desc_.add_options()
//    ("SEGMENTS_LENGHT", po::value< int >( &SEGMENTS_LENGHT ), "SEGMENTS LENGHT. Cannot be changed!!!" );
  desc_.add_options()
    ("starting_age", po::value< int >( &starting_age ), "starting_age of the World" );
  desc_.add_options()
    ("x_default", po::value< float >( &x_default ), "a x_default value" );
  desc_.add_options()
    ("y_default", po::value< float >( &y_default ), "a x_default value" );
  desc_.add_options()
    ("starting_energy", po::value< float >( &starting_energy ), "Beings starting energy" );
  desc_.add_options()
    ("epsath", po::value< float >( &epsath ), "Factor to control athleticity of Beings - higher the value greater the moving distance" );
  desc_.add_options()
    ("epsdim", po::value< float >( &epsdim ), "Factor to control dimension of Beings - higher the value greater the beings dimension" );
  desc_.add_options()
    ("max_move_1d", po::value< float >( &max_move_1d), "Maximum moving distance allowed per each dimension" );
  desc_.add_options()
    ("epsener", po::value< float >( &epsener ), "Factor to control energy absorption of Beings when moving - higher the value greater the energy absorption" );
  desc_.add_options()
    ("epsener2", po::value< float >( &epsener2 ), "Another factor to control athleticity of Beings - higher the value greater the moving distance" );
  desc_.add_options()
    ("pmov_distr", po::value< std::string >( &pmov_distr ), "Type of distribution for the moving direction. Available: [UNIFORM]" );
  desc_.add_options()
    ("epsnutri", po::value< float >( &epsnutri ), "Ratio of the food nutrival absorbed during eat" );
  desc_.add_options()
    ("PROBABLE_AGE_LIMIT", po::value< int >( &PROBABLE_AGE_LIMIT ), "When Biengs are expected to die on average" );
  desc_.add_options()
    ("epsage", po::value< float >( &epsage ), "Factor to control the probability of Beings to die. Higher the factor, higher the probability to survive. However it is not the probability itself!" );
  desc_.add_options()
    ("epsrepr", po::value< float >( &epsrepr ), "Factor to control the probability of Beings to reproduce. Higher the factor, higher the probability to reproduce. However it is not the probability itself!" );
  desc_.add_options()
    ("REPRODUCTION_METHOD", po::value< std::string >( &REPRODUCTION_METHOD ), "Type of chomosome mixing. Available: [SEGMENTS_EXCHANGE]" );
  desc_.add_options()
    ("pmut", po::value< float >( &pmut ), "Probability that a chromosome is mutated" );
  desc_.add_options()
    ("muted_gene_selection", po::value< std::string >( &muted_gene_selection ), "Distribution to control how a gene is selected for mutation. Available: [UNIFORM]" );
  desc_.add_options()
    ("fout_name", po::value< std::string >( &fout_name ), "Base path and name for output files" );
  desc_.add_options()
    ("food_file", po::value< std::string >( &food_file ), "Name of the food file containtng the points at the beginning" );
  desc_.add_options()
    ("rad_file", po::value< std::string >( &rad_file ), "Name of the radioactive sources file containtng the points at the beginning" );
  desc_.add_options()
    ("READ_RAD_FROM_FILE", po::value< int >( &READ_RAD_FROM_FILE ), "Read radiation sources positions form file" );
  desc_.add_options()
    ("beings_file", po::value< std::string >( &beings_file ), "Name of the  file containtng the beings at the beginning" );
  desc_.add_options()
    ("world_init_file_name", po::value< std::string >( &world_init_file_name ), "Name of the  file containtng the init world for restart" );
  desc_.add_options()
    ("chromo_affected", po::value< std::string >( &chromo_affected ), "Which chromo are affected by mutation. Available: [ALL]" );

  
  const std::string cfg_file_name("darwin.cfg");
  read( desc_, cfg_file_name);
  if (SEED == 0) SEED = abs(std::chrono::system_clock::now().time_since_epoch().count());
  else SEED = abs(SEED);

};    // close di ctor


void constants_wrapper::show() {

  for (po::variables_map::iterator it=vm_.begin(); it != vm_.end();
it++ ) {

       if (is_empty(it->second.value()))
         std::cout << "# " << it->first << "=is_empty" << std::endl;

       if (vm_[it->first].defaulted())
         std::cout << "# " << it->first << "=is_defaulted" << std::endl;

       if (is_int(it->second.value()))
         std::cout << it->first << "=" << vm_[it->first].as<int>() << std::endl;
       else if (is_double(it->second.value()))
         std::cout << it->first << "=" << vm_[it->first].as<double>() << std::endl;
       else if (is_char_ptr(it->second.value()))
         std::cout << it->first << "=" << vm_[it->first].as<const char*>() << std::endl;
       else if (is_float(it->second.value()))
         std::cout << it->first << "=" << vm_[it->first].as<float>() << std::endl;
       else if (is_string(it->second.value())) {
         std::cout << it->first << "=";
         std::string temp = vm_[it->first].as<std::string>();
         if (temp.size())
           std::cout << temp << std::endl;
         else
           std::cout << "true" << std::endl;
       }
  }
};

void constants_wrapper::save(std::string const& filename) {

   std::ofstream outstr;
   outstr.open(filename);
   
   for (po::variables_map::iterator it=vm_.begin(); it != vm_.end();
it++ ) {

       if (is_empty(it->second.value()))
         outstr << "# " << it->first << "= is_empty" << std::endl;

       if (vm_[it->first].defaulted())
         outstr << "# " << it->first << "= is_defaulted" << std::endl;

       if (is_int(it->second.value()))
         outstr << it->first << " = " << vm_[it->first].as<int>() << std::endl;
       else if (is_double(it->second.value()))
         outstr << it->first << " = " << vm_[it->first].as<double>() << std::endl;
       else if (is_char_ptr(it->second.value()))
         outstr << it->first << " = " << vm_[it->first].as<const char*>() << std::endl;
       else if (is_float(it->second.value()))
         outstr << it->first << " = " << vm_[it->first].as<float>() << std::endl;
       else if (is_string(it->second.value())) {
         outstr << it->first << " = ";
         std::string temp = vm_[it->first].as<std::string>();
         if (temp.size())
           outstr << temp << std::endl;
         else
           outstr << "true" << std::endl;
       }
  }
  outstr.close();
}; 
/*
void program_options_wrapper::get_typeid(const boost::any & operand) {
     std::cout << operand.type().name() << std::endl;
}
*/ 

  // Write, read, and print newer settings.
  //write_settings( "another test" );
  //read_settings( desc, vm );
  //std::cout << "name = " << name << std::endl;
