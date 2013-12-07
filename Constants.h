#ifndef DARWIN_CONSTANTS_H
#define DARWIN_CONSTANTS_H
#include <string>

//const std::string fout_name = "./OUTPUT/darwin.out.";

//std::string world_init_file_name = "./OUTPUT/darwin.out.";

// ENVIRONMENT CONSTANTS

//float X_MIN = 0.0;
//float X_MAX = 2000.0;
//float Y_MIN = 0.0;
//float Y_MAX = 2000.0;

//bool READ_FOOD_FROM_FILE = false;
//std::string food_file = "food.txt";
//float default_nutrival = 100.0;
//int N_FOOD_POINT_AT_START = 1000;
//std::string FOOD_POINT_DISTRIBUTION = "UNIFORM";

//bool ENABLE_RADIACTIVE_SOURCES = false;
//int N_RAD_SOURCES_AT_START = 1000;
//std::string SOURCES_DISTRIBUTION = "UNIFORM";
//float default_rad = 100.0;
//bool READ_RAD_FROM_FILE = false;
//std::string rad_file = "rad.txt";

// STARTING POPULATATION CONSTANTS

//bool READ_POPULATION_FROM_FILE = false;
//std::string beings_file = "beings.txt";
//int N_BEINGS = 300;
//std::string BEINGS_START_DISTRIBUTION = "UNIFORM";

// LOOP CONSTANTS
//int ITER_NUMBER = 400;
//std::string FIRST_BEING_IN_LOOP = "UNIFORM";

// BEING CONSTANTS
const int CHROMO_NUMBER = 6;
const int CHROMO_SEGMENTS = 2;
const int SEGMENTS_LENGHT = 10;
const int DIM = CHROMO_SEGMENTS * SEGMENTS_LENGHT;
const short int charm_default[DIM] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
const short int beauty_default[DIM] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
const short int dim_default[DIM] = {1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const short int athlet_default[DIM] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
const short int karma_default[DIM] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
const short int attracted_default[DIM] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};


//int starting_age = 0;
//float x_default = 0.0;
//float y_default = 0.0;
//float starting_energy = 1500.0;

// #MOVEMENT CONSTANTS
//float epsath = 1.0;
//float epsdim = 0.1;
//float max_move_1d = 15.0;
//float epsener = 0.15;
//float epsener2 = 0.15;
//std::string pmov_distr = "UNIFORM";

// EAT CONSTANTS
//float epsnutri = 0.3;


// DIE CONSTANTS

//int PROBABLE_AGE_LIMIT = 100;
//float epsage = 0.9;

// REPRODUCTION CONSTANTS
//float epsrepr = 0.25;
//std::string REPRODUCTION_METHOD = "SEGMENTS_EXCHANGE";

// MUTATION CONSTANTS

//float pmut = 0.1;  // probability that a chromosome is mutated
//std::string muted_gene_selection = "UNIFORM";
//std::string chromo_affected = "ALL";

#endif
