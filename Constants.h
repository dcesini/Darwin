#ifndef DARWIN_CONSTANTS_H
#define DARWIN_CONSTANTS_H
#include <string>

const char fout_name[] = "./OUTPUT/darwin.out.";
const char food_file[] = "food.txt";

// ENVIRONMENT CONSTANTS

const float X_MIN = 0.0;
const float X_MAX = 2000.0;
const float Y_MIN = 0.0;
const float Y_MAX = 2000.0;

const bool READ_FOOD_FROM_FILE = false;

const float default_nutrival = 100.0;

const int N_FOOD_POINT_AT_START = 1000;
const std::string FOOD_POINT_DISTRIBUTION = "UNIFORM";

const bool ENABLE_RADIACTIVE_SOURCES = false;
const int N_RAD_SOURCES_AT_START = 1000;
const std::string SOURCES_DISTRIBUTION = "UNIFORM";
const float default_rad = 100.0;

// STARTING POPULATATION CONSTANTS

const bool READ_POPULATION_FROM_FILE = false;
const int N_BEINGS = 300;
const std::string BEINGS_START_DISTRIBUTION = "UNIFORM";

// LOOP CONSTANTS
const int ITER_NUMBER = 400;
const std::string FIRST_BEING_IN_LOOP = "UNIFORM";

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
const int starting_age = 0;
const float x_default = 0.0;
const float y_default = 0.0;
const float starting_energy = 1500.0;

// #MOVEMENT CONSTANTS
const float epsath = 1.0;
const float epsdim = 0.1;
const float max_move_1d = 15.0;
const float epsener = 0.15;
const float epsener2 = 0.15;
const std::string pmov_distr = "UNIFORM";

// EAT CONSTANTS
const float epsnutri = 0.3;


// DIE CONSTANTS

const int PROBABLE_AGE_LIMIT = 100;
const float epsage = 0.9;

// REPRODUCTION CONSTANTS
const float epsrepr = 0.25;
const std::string REPRODUCTION_METHOD = "SEGMENTS_EXCHANGE";

// MUTATION CONSTANTS

const float pmut = 0.1;  // probability that a chromosome is mutated
const std::string muted_gene_selection = "UNIFORM";
const std::string chromo_affected = "ALL";

#endif
