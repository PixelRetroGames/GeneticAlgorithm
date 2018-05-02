#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <vector>
#include <windows.h>
#include "individual.h"

class Genetic_algorithm
{
 private:
 std::vector<Individual> individuals;
 std::vector<bool> Used;
 int achieved=0;

 public:
 Genetic_algorithm(int population_size);
 void Train_Generation();
 void Breed_Generation();
 void Evolve();
};

void Clear_output_folder();

#endif // GENETIC_ALGORITHM_H
