#include "setup.h"
#include "functions.h"
#include <sstream>

int main(int argc, char *argv[])
{
  createdrive();
  setup();
  string userinput;
  string arg1;
  string arg2;
  string arg3;
  string delimiter;
  vector<string> parsee;
  string token;
  cout << "Hello, welcome to our Log structured file system. \nPlease type 'import filename desiredfilename' in order to import a file saved with your desired name. \nPlease type 'remove filename' to remove the desired file from the drive. \nPlease type 'list' to list all the files and their respective inodes. \nPlease type 'shutdown' to shutdown the filesystem." << endl;
  while(true){
    parsee.clear();
    cout << "Please input a command: ";
    //cin >> userinput;
    /*scanf(" %[^\n]s",userinput);
    stringstream ss(userinput);
    string filler;
    if(getline(ss,filler,' ')){
      parsee.push_back(filler);
    }*/
    getline(cin, userinput);
    //cout << userinput << endl;
    size_t pos = 0;
    while((pos = userinput.find(" ")) != std::string::npos)
    {
      token = userinput.substr(0, pos);
      parsee.push_back(token);
      userinput.erase(0, pos+1);
    }
    parsee.push_back(userinput);

    /*for(int i = 0; i < parsee.size(); i++)
    {
      cout << parsee[i] << endl;
    }*/

    /*arg1 = strtok(userinput," ");
    if(arg1!=NULL){
      arg2 = strtok(NULL," ");
    }
    if(arg2!=NULL){
      arg3 = strtok(NULL, " ");
    }
    /*while (pch != NULL)
    {
      printf ("%s\n",pch);
      pch = strtok (NULL, " ");
    }*/
    /*for(int i=0;i<parsee.size();i++){
      parsee[i];
    }*/
    //cin >> arg1;
    if(parsee[0]=="import"){
      import(parsee[1], parsee[2]);
    }else if(parsee[0]=="remove"){
      remove1(arg1);
    }else if(parsee[0]=="list"){
      list();
    }else if(parsee[0]=="shutdown"){
      shutdown();
      exit(0);
    }else{
      cout << "Input unrecognized" << endl;
    }
  }

  /*for(int i = 0; i < 300; i++)
  {
    import(&outfile, "sample (copy 9).txt", "sampsse934.txt");
  }*/

  //shutdown();

  /*int filedesc = open("DRIVE/CHECKPOINT_REGION", O_RDWR, 0777);
  if(filedesc<0){
    cout << "ERROR OPENING CHECKPOINT REGION CLOSING" << endl;
    exit(1);
  }

  //write(filedescw2, &live_segments, sizeof(live_segments));
  lseek(filedesc, 68, SEEK_CUR);
  int rd = 0;
  read(filedesc, &rd, sizeof(rd));
  //cout << rd << endl;
  close(filedesc);
  //remove("sampss.txt");*/

  //write(filedescw2, &live_segments, sizeof(live_segments));

  shutdown();

  //ifstream infile;
  //infile.open("DRIVE/FILEMAP
  //list();
  //list();

  exit(0);
}
