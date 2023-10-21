#include "threads.h"
#include <string>


int main(int argc, char *argv[])
{
  
  if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)
  {
    cout << "ERROR: Must have three arguments: Number of random integers, number of readers and number of writers" << endl;
    return 1;
  }
  
  if((argv[1][0] != 0 && !isdigit(argv[1][0])) || (argv[1][1] != 0 && !isdigit(argv[1][1])) || (argv[1][2] != 0 && !isdigit(argv[1][2])))
  {
    cout << "ERROR: Arguments must be digits only" << endl;
    return 1;
  }
  
  if(!isdigit(argv[2][0]))
  {
    cout << "ERROR: Arguments must be digits only" << endl;
    return 1;
  }
  
  if(!isdigit(argv[3][0]))
  {
    cout << "ERROR: Arguments must be digits only" << endl;
    return 1;
  }
  
  int num_rands = stoi(argv[1]);
  int num_readers = stoi(argv[2]);
  int num_writers = stoi(argv[3]);
  
  if(num_rands < 1 || num_rands > 100)
  {
    cout << "ERROR: Number of integers must be between 1 and 100 inclusive" << endl;
    return 1;
  }
  if(num_readers < 1 || num_readers > 9)
  {
    cout << "ERROR: Number of readers must be between 1 and 9 inclusive" << endl;
    return 1;
  }
  if(num_writers < 1 || num_writers > 9)
  {
    cout << "ERROR: Number of writers must be between 1 and 9 inclusive" << endl;
    return 1;
  }
  
  LLC *linkedList = new LLC();
  
  srand(time(NULL));
  
  /*for(int i=0; i<10; i++){
    int ranNum = rand() % 1000 + 1;
    linkedList->insert(ranNum);
  }
  
  Node *n = linkedList->headNode;
  while(n != NULL)
  {
    cout << n->element << endl;
    n = n->next;
  }
  cout << endl;*/
  
  createThreads(num_readers, num_writers, num_rands, linkedList);
  
  
  delete linkedList;
  
	exit(0);
}
