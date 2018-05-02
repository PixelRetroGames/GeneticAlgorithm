#include<windows.h>
#include "genetic_algorithm.h"
#include <algorithm>

Genetic_algorithm::Genetic_algorithm(int population_size)
{
 for(int i=0;i<population_size;i++)
 {
     Individual new_individual;
     individuals.push_back(new_individual);
     Used.push_back(0);
 }
}

void Genetic_algorithm::Train_Generation()
{
 achieved=0;
 for(int i=0;i<individuals.size();i++)
 {
     individuals[i].Calculate_fitness();
     Used[i]=0;
     achieved+=individuals[i].Get_finish();
 }
 std::sort(individuals.begin(),individuals.end(),Compare_individuals);
}

void Genetic_algorithm::Breed_Generation()
{
    std::vector<Individual> Parents;
    int pos=0;
    while(Parents.size()<individuals.size()/2)
    {
        int prob=100*(individuals.size()-pos)/individuals.size();
        int act=(1+rand()%100);
        if(act<=prob&&!Used[pos])
            Parents.push_back(individuals[pos]),Used[pos]=1;
        pos=(pos+1)%individuals.size();
    }
    individuals.clear();
    for(int i=0;i<Parents.size();i+=2)
    {
        individuals.push_back(Parents[i]);
        individuals.push_back(Parents[i+1]);
        individuals.push_back(Parents[i].Breed(&Parents[i+1]));
        individuals.push_back(Parents[i].Breed(&Parents[i+1]));
    }
}

const int SAVE_FREQUENCY=10;

void Genetic_algorithm::Evolve()
{
    Clear_output_folder();
    int generation=0;
    while(1)
    {
        Train_Generation();
        int average_fitness=0;
        for(int i=0;i<individuals.size();i++)
            average_fitness+=individuals[i].Get_fitness();
        average_fitness/=individuals.size();
        if(generation%SAVE_FREQUENCY==0)
           individuals[0].Save(generation);
        generation++;
        //if(generation%10==0)
            printf("Gen:%d Average:%d\n",generation,average_fitness);
        if(achieved>=individuals.size()*9/10)
            break;
        Breed_Generation();
    }
    individuals[0].Save(generation);
    printf("Generations: %d ",generation);
    FILE *out=fopen("solution.txt","w");
    for(int i=0;i<individuals.size();i++)
        //if(individuals[i].Get_finish())
            individuals[i].Print_Genome(out);
}

void Clear_output_folder()
{
 //system("cd output");
 system("clear.bat");
}

