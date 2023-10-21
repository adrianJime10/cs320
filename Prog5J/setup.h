#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
using namespace std;

void createdrive();
void createsegments();
void createfilemap();
void createcheckpointregion();
