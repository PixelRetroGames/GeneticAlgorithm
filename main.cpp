#include "externs.h"
#include "individual.h"
#include "genetic_algorithm.h"

#include <iostream>

int main()
{
 srand(time(NULL));
 Load_map("map.txt");
 Genetic_algorithm test(200);
 test.Evolve();
}
