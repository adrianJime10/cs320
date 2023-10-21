#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include "llc.h"
#include <unistd.h>
using namespace std;

void createThreads(int, int, int, LLC*);
void *read(void*);
void *write(void*);

typedef struct
{
  int random;
  int ID;
  LLC * list;
}arguments;
