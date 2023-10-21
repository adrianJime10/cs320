#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <sys/stat.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <typeinfo>
using namespace std;

void import(string, string);
void list();
void shutdown();
void setup();
void remove1(string);
long getfilesize(string);

typedef struct inode
{
  char name[128];
  unsigned int size;
  int dblock[128];
  char dummy[380];
} inode;

typedef struct imap_block
{
  int imap_part[256];
}imap_block;

typedef union datablock
{
  char dataC[1024];
  //int dataI[256];
} datablock;

typedef union block
{
  inode virtual_inode;
  datablock virtual_datablock;
  imap_block virtual_imap_block;
}block;
