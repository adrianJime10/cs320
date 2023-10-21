#include "setup.h"
#include <iostream>
#include <fstream>

void createdrive()
{
  if (mkdir("DRIVE", 0777) == -1)
  {
    cerr << "Error :  " << strerror(errno) << endl;
  }
  else
  {
    createsegments();
 	createfilemap();
    createcheckpointregion();
  }
}

void createfilemap()
{

    ofstream outfile;
    outfile.open("DRIVE/FILEMAP.txt");
    outfile.close();
	/*string filename = "DRIVE/FILEMAP.txt";
	const char * c = filename.c_str();
	int filedesc = open(c, O_CREAT | O_WRONLY, 0777);
	if(filedesc<0){
		cout << "ERROR" << endl;
		exit(1);
	}
	close(filedesc);*/
}

void createsegments()
{
  int i;
  int j;
  for(i = 0; i < 64; i++)
  {
    string filename = "DRIVE/SEGMENT" + to_string(i);
    const char * c = filename.c_str();
    int filedesc = open(c, O_CREAT | O_WRONLY, 0777);
    if(filedesc < 0)
    {
      cout << "ERROR" << endl;
      exit(1);
    }
    
    char zero = '0';
    for(j = 0; j < 10/*48576*/; j++)
    {
      write(filedesc, &zero, sizeof(zero));
    }
    close(filedesc);
  }
}

void createcheckpointregion()
{
  const char * c = "DRIVE/CHECKPOINT_REGION";
  int filedesc = open(c, O_CREAT | O_RDWR, 0777);
  if(filedesc < 0)
  {
    cout << "ERROR" << endl;
    exit(1);
  }
  
}
