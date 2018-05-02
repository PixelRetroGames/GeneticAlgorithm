#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "externs.h"
#include <ctime>
#include <cstdlib>
#include <cstdio>

class Individual
{
 private:
 int fitness;
 bool finish;
 char *chromosome;

 public:
 Individual();
 void Calculate_fitness();
 int Get_fitness();
 bool Get_finish();
 Individual Breed(Individual *other);
 char *Get_genome();
 void Print_Genome(FILE *out);
 void Save(int generation);
};

bool Compare_individuals(Individual a,Individual b);

#endif // INDIVIDUAL_H
