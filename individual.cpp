#include<cmath>
#include "individual.h"

Individual::Individual()
{
 finish=0;
 fitness=-1;
 chromosome=new char[CHROMOSOME_LENGTH];
 for(int i=0;i<CHROMOSOME_LENGTH;i++)
     chromosome[i]=rand()%4;
}

void Individual::Calculate_fitness()
{
    finish=0;
    int x=0,y=0;
    const int dirx[]={1,0,-1,0};
    const int diry[]={0,1,0,-1};
    fitness=0;
    for(int i=0;i<CHROMOSOME_LENGTH;i++)
    {
        int x1=x+dirx[chromosome[i]];
        int y1=y+diry[chromosome[i]];
        if(x1<0||x1>=MAP_SIZE||y1<0||y1>=MAP_SIZE)
        {
            fitness+=MAP_FITNESS[x][y];
                continue;
        }
        if(!MAP[x1][y1])
        {
            x=x1;
            y=y1;
        }
        fitness+=MAP_FITNESS[x][y];
        if(x==MAP_SIZE-1&&y==MAP_SIZE-1)
        {
            finish=1;
            break;
        }
    }
    //fitness/=CHROMOSOME_LENGTH;
}

bool Individual::Get_finish()
{
    return finish;
}

int Individual::Get_fitness()
{
 if(fitness==-1)
    Calculate_fitness();
 return fitness;
}

Individual Individual::Breed(Individual *other)
{
    int preffix=rand()%CHROMOSOME_LENGTH;
    Individual child;

    for(int i=0;i<=preffix;i++)
        child.chromosome[i]=chromosome[i];
    for(int i=preffix+1;i<CHROMOSOME_LENGTH;i++)
        child.chromosome[i]=other->chromosome[i];
    //int MAX=log(CHROMOSOME_LENGTH);
    int steps=rand()%(MAX_LOG+2);
    for(int i=0;i<steps;i++)
    {
        int pos=rand()%CHROMOSOME_LENGTH;
        child.chromosome[pos]=rand()%4;
    }
    return child;
}

char *Individual::Get_genome()
{
    return chromosome;
}

void Individual::Print_Genome(FILE *out)
{
    const char *dir[]={"jos","dreapta","sus","stanga"};

    for(int i=0;i<CHROMOSOME_LENGTH;i++)
        fprintf(out,"%s ",dir[chromosome[i]]);
    fprintf(out,"\n");
}

void Individual::Save(int generation)
{
 char path[100]={NULL},aux[100]={NULL};
 strcpy(path,"output/gen_");
 itoa(generation,aux);
 strcat(path,aux);
 strcat(path,".txt");
 FILE *out=fopen(path,"w");
 fprintf(out,"%d\n",CHROMOSOME_LENGTH);
 for(int i=0;i<CHROMOSOME_LENGTH;i++)
     {
      int sq=chromosome[i];
      fprintf(out,"%d ",sq);
     }
 fclose(out);
}

bool Compare_individuals(Individual a,Individual b)
{
 return a.Get_fitness()<b.Get_fitness();
}
