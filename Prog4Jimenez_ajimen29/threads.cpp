#include <stdlib.h>
#include <iostream>
#include "threads.h"
#include <fstream>


using namespace std;

pthread_mutex_t listenerMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t listenerCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t rmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t xmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t readTry = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resource = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t readcountLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t toFile = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t safe1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t safe2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t safe3 = PTHREAD_MUTEX_INITIALIZER;
int readcount, writecount = 0;
int numcount[9] = {0,0,0,0,0,0,0,0,0};
int counter[9] = {1,1,1,1,1,1,1,1,1};
Node *traverser[9];
ofstream file;

void *listenWait(void*){
  pthread_mutex_lock(&listenerMutex);
  pthread_cond_wait(&listenerCond, &listenerMutex);
  
  cout << "Almost Done!" << endl;
  
  pthread_mutex_unlock(&listenerMutex);
  return NULL;
}

void *read(void* ptr)
{
  //<ENTRY Section>
  pthread_mutex_lock(&xmutex);
  arguments* x = static_cast<arguments*>(ptr);
  //cout << "Reader " << x->ID << " locking xmutex in ENTRY" << endl;
  while(x->list->headNode==NULL);
  //cout << "Reader " << x->ID << " unlocking xmutex in ENTRY" << endl;
  pthread_mutex_unlock(&xmutex);
  pthread_mutex_lock(&readTry);
  //cout << "Reader " << x->ID << " locking readtry in ENTRY" << endl;
  pthread_mutex_lock(&rmutex);
  //cout << "Reader " << x->ID << " locking rmutex in ENTRY" << endl;
  readcount++;
  if(readcount == 1)
  {
    pthread_mutex_lock(&resource);
    //cout << "Reader " << x->ID << " locking resource in ENTRY" << endl;
  }
  //cout << "Reader " << x->ID << " unlocking rmutex in ENTRY" << endl;
  pthread_mutex_unlock(&rmutex);
  //cout << "Reader " << x->ID << " unlocking readtry in ENTRY" << endl;
  pthread_mutex_unlock(&readTry);
  
  //<CRITICAL Section>
  while(counter[x->ID-1]<x->random+1){

    traverser[x->ID-1] = x->list->headNode;
      while(traverser[x->ID-1]!=NULL){
      if((traverser[x->ID-1]->element)%10==x->ID)
      {
        //lock
        pthread_mutex_lock(&safe1);
        numcount[x->ID-1]++;
        pthread_mutex_unlock(&safe1);
        //unlock
      }
      traverser[x->ID-1]=traverser[x->ID-1]->next;
    }
    pthread_mutex_lock(&toFile);
    char buffer[50];
    sprintf(buffer, "reader_%d.txt", (x->ID));
    file.open(buffer, fstream::app);
    file << "Reader " << (x->ID) << ": " << "Read " << counter[x->ID-1] << ": " << numcount[x->ID-1] << " ending in " << x->ID << endl; //traverser[x->ID]->element << endl;
    file.close();
    pthread_mutex_unlock(&toFile);

    pthread_mutex_lock(&safe2);
    numcount[x->ID-1]=0;
    pthread_mutex_unlock(&safe2);

    pthread_mutex_lock(&safe3);
    counter[x->ID-1]++;
    pthread_mutex_unlock(&safe3);


    pthread_mutex_lock(&readcountLock);
    readcount--;
    if(readcount==0){
      //cout << "Reader " << x->ID << " unlocking resource in CRITICAL SLEEPY" << endl;
      pthread_mutex_unlock(&resource);
    }
    pthread_mutex_unlock(&readcountLock);

    usleep(10000);
    
    pthread_mutex_lock(&readcountLock);
    readcount++;
    if(readcount==1){
      pthread_mutex_lock(&resource);
      //cout << "Reader " << x->ID << " locking resource in CRITICAL WAKE" << endl;
    }
    pthread_mutex_unlock(&readcountLock);
  }
  
  //<EXIT Section>
  pthread_mutex_lock(&rmutex);
  //cout << "Reader " << x->ID << " locking rmutex in EXIT" << endl;
  if(readcount == 1)
  {
    sleep(1);
    pthread_cond_signal(&listenerCond);
  }
  readcount--;
  if(readcount == 0)
  {
    //cout << "Reader " << x->ID << " unlocking resource in EXIT" << endl;
    pthread_mutex_unlock(&resource);
  }
  //cout << "Reader " << x->ID << " unlocking rmutex in EXIT" << endl;
  pthread_mutex_unlock(&rmutex);
  return NULL;
}

void *write(void* ptr)
{
  //<ENTRY Section>
  pthread_mutex_lock(&wmutex);
  arguments * x = static_cast<arguments*>(ptr);
  //cout << "Writer " << x->ID << " locking wmutex in ENTRY" << endl;
  writecount++;
  //cout << " (" << writecount << ")writers-------------" << endl;
  if(writecount == 1)
  {
    pthread_mutex_lock(&readTry);
    //cout << "Writer " << x->ID << " locking readtry in ENTRY" << endl;
  }
  //cout << "Writer " << x->ID << " unlocking wmutex in ENTRY" << endl;
  pthread_mutex_unlock(&wmutex);
  
  //<CRITICAL Section>
  pthread_mutex_lock(&wmutex);
  //cout << "Writer " << x->ID << " locking wmutex in CRITICAL" << endl;
  pthread_mutex_lock(&resource);
  //cout << "Writer " << x->ID << " locking resource in CRITICAL" << endl;
  int i = 0;
  while(i<x->random){
    int ranNum = rand() % 1000 + 1;
    if(ranNum%10==x->ID)
    {
      x->list->insert(ranNum);
      i++;
      writecount--;
      if(writecount==0){
        //cout << "Writer " << x->ID << " unlocking readtry in CRITICAL SLEEPY" << endl;
        pthread_mutex_unlock(&readTry);
      }
      //cout << "Writer " << x->ID << " (" << writecount << ") unlocking wmutex in CRITICAL SLEEPY" << endl;
      pthread_mutex_unlock(&wmutex);
      //cout << "Writer " << x->ID << " (" << writecount << ") unlocking resource in CRITICAL SLEEPY" << endl;
      pthread_mutex_unlock(&resource);
      usleep(10000);
      pthread_mutex_lock(&wmutex);
      //cout << "Writer " << x->ID << " locking wmutex in CRITICAL SLEEPY" << endl;
      pthread_mutex_lock(&resource);
      //cout << "Writer " << x->ID << " locking resource in CRITICAL WAKE TIME" << endl;
      writecount++;
      if(writecount==1){
        pthread_mutex_lock(&readTry);
        //cout << "Writer " << x->ID << " locking readtry in CRITICAL WAKE TIME" << endl;
      }
    }
  }
  //cout << "Writer " << x->ID << " unlocking wmutex in CRITICAL" << endl;
  pthread_mutex_unlock(&wmutex);
  //cout << "Writer " << x->ID << " unlocking resource in CRITICAL" << endl;
  pthread_mutex_unlock(&resource);
  
  
  //<EXIT Section>
  pthread_mutex_lock(&wmutex);
  //cout << "Writer " << x->ID << " locking wmutex in EXIT" << endl;
  writecount--;
  if(writecount == 0)
  {
    //cout << "Writer " << x->ID << " unlocking readtry in EXIT" << endl;
    pthread_mutex_unlock(&readTry);
  }
  //cout << "Writer " << x->ID << " unlocking wmutex in EXIT" << endl;
  pthread_mutex_unlock(&wmutex);
  return NULL;
}

void createThreads(int num_readers, int num_writers, int num_rands, LLC* list)
{
  pthread_t wt[num_writers];
  pthread_t rt[num_readers];
  pthread_t waiter;
  int i;
  pthread_create(&waiter, NULL, &listenWait, NULL);
  for(i = 0; i < num_readers; i++)
  {
    int* readerID = new int();
    *readerID = i;
    arguments*x = (arguments*)malloc(sizeof(arguments));
    x->random=num_rands;
    x->ID = i+1;
    x->list = list;
    pthread_create(&rt[i], NULL, &read, x);
  }
  for(i = 0; i < num_writers; i++)
  {
    arguments* x = (arguments*)malloc(sizeof(arguments));
    x->random = num_rands;
    x->ID = i;
    x->list = list;
    pthread_create(&wt[i], NULL, &write, x);
  }
  for(i = 0; i < num_writers; i++)
  {
    pthread_join(wt[i], NULL);
  }
  for(i = 0; i < num_readers; i++)
  {
    pthread_join(rt[i], NULL);
  }
  pthread_join(waiter, NULL);
  
  return;
  
}
