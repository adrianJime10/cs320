#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <deque>
#include <vector>
using namespace std;

void writeNoLocal(int*, vector<double>, vector<double>, vector<double>, vector<double>, vector<double>);
void write8020(int*, vector<double>, vector<double>, vector<double>, vector<double>, vector<double>);
void writeLooping(int*, vector<double>, vector<double>, vector<double>, vector<double>, vector<double>);
vector<double> opt(int*);
vector<double> lru(int*);
vector<double> fifo(int*);
vector<double> random_pgr(int*);
vector<double> clock_pgr(int*);
vector<vector<int>> create_frames();
