#include "externs.h"

int MAP_SIZE=0;
int CHROMOSOME_LENGTH=100;
int MAX_LOG=2;
std::vector<std::vector<bool>> MAP;
std::vector<std::vector<int>> MAP_FITNESS;

void Load_map(char *filename)
{
 MAX_LOG=log(CHROMOSOME_LENGTH);

 FILE *in=fopen(filename,"r");
 fscanf(in,"%d ",&MAP_SIZE);
 MAP.resize(MAP_SIZE);
 MAP_FITNESS.resize(MAP_SIZE);
 for(int i=0;i<MAP_SIZE;i++)
 {
     MAP[i].resize(MAP_SIZE);
     MAP_FITNESS[i].resize(MAP_SIZE);
 }
 for(int i=0;i<MAP_SIZE;i++)
 {
     for(int j=0;j<MAP_SIZE;j++)
     {
         int aux;
         fscanf(in,"%d ",&aux);
         MAP[i][j]=(aux==1);
         MAP_FITNESS[i][j]=2e9;
     }
 }
 BFS();
}

void BFS()
{
    const int dirx[]={1,0,-1,0};
    const int diry[]={0,1,0,-1};
    std::queue<std::pair<int,int> > Q;
    int x=MAP_SIZE-1,y=MAP_SIZE-1;
    MAP_FITNESS[x][y]=0;
    Q.push({x,y});
    while(!Q.empty())
    {
        x=Q.front().first;
        y=Q.front().second;
        Q.pop();
        for(int d=0;d<4;d++)
        {
            int x1=x+dirx[d];
            int y1=y+diry[d];
            if(x1<0||x1>=MAP_SIZE||y1<0||y1>=MAP_SIZE)
                continue;
            if(!MAP[x1][y1]&&MAP_FITNESS[x1][y1]>1+MAP_FITNESS[x][y])
            {
                Q.push({x1,y1});
                MAP_FITNESS[x1][y1]=1+MAP_FITNESS[x][y];
            }
        }
    }
    CHROMOSOME_LENGTH=1.618*MAP_FITNESS[0][0];
    MAX_LOG=log10(CHROMOSOME_LENGTH);
}

void itoa(int n, char s[])
{
 int i,sign;
 if((sign=n)<0)
     n=-n;
 i=0;
 do
   {
    s[i++]=n%10+'0';
   }
 while((n/=10)>0);
 if(sign<0)
    s[i++]='-';
 s[i]='\0';
 reverse(s);
}

void atoi(int &n,char s[])
{
 n=0;
 int x=strlen(s);
 for(int i=0;i<x;i++)
     {
      n=n*10;
      n+=(int)(s[i]-'0');
     }
}

void reverse(char s[])
{
 int i,j;
 char c;
 for(i=0,j=strlen(s)-1;i<j;i++,j--)
     {
      c=s[i];
      s[i]=s[j];
      s[j]=c;
     }
}
