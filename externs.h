#ifndef EXTERNS_H
#define EXTERNS_H

extern int CHROMOSOME_LENGTH;
extern int MAX_LOG;

#include <queue>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>

extern int MAP_SIZE;
extern std::vector<std::vector<bool>> MAP;
extern std::vector<std::vector<int>> MAP_FITNESS;
void Load_map(char *filename);
void BFS();
void itoa(int n, char s[]);
void atoi(int &n,char s[]);
void reverse(char s[]);

#endif // EXTERNS_H
