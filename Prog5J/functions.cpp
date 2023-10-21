#include "functions.h"
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string.h>

vector<block> virtual_segment;
vector<char> segment_type;
vector<int> imap_part(10240,-1);
char live_segments[64]={'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
int segment = 0;
int counter = 0;
int inodecounter=0;
int counterx= 0;
int counterimap=0;
int k =0;
int checkpoint[40]={-1, -1,-1, -1,-1, -1,-1, -1,-1, -1,-1, -1,-1, -1,-1, -1,-1, -1,-1, -1,-1, -1,-1, -1,-1, -1,-1, -1,-1, -1,-1, -1,-1, -1,-1, -1,-1, -1,-1, -1};

void import(string filename, string newname)
{
  ofstream outfile;
  outfile.open("DRIVE/FILEMAP.txt", std::ios_base::app);
  inode* newNode = new inode();
  block* newBlock = new block();
  block* newerBlock = new block();
  
  //counter+=1;
  
  //vector<char> writable(newname.begin(), newname.end());
  const char * name = newname.c_str();
  strcpy(newNode->name, name);
  //writable.push_back('\0');
  int i = 0;
  int j = 0;
  //while(writable[i] != '\0')
  //{
   // newNode->name[i] = writable[i];
   // i++;
  //}
  //cout << newNode->name << endl;
  int file_name_length = 0;
  int name_remainder;
  while(newNode->name[file_name_length] != '\0')
  {
    file_name_length++;
  }
  name_remainder = 128 - file_name_length;
  //cout << file_name_length << endl;
  //cout << name_remainder << endl;
  newNode->size = getfilesize(filename);
  
  const char * c = filename.c_str();

  int filedescr = open(c, O_RDONLY);

  if(filedescr<0){
    cout << "ERROR IN OPEN IN IMPORT" << endl;
    exit(1);
  }
  
  //cout << "file size " << newNode->size << endl;
  
  int data_size = newNode->size;
  int num_blocks = ceil(((double)data_size)/(double)1024);

  int inodelocc=0;
  newBlock->virtual_inode = *newNode;
  virtual_segment.push_back(*newBlock);
  for(int b =0; b<10240;b++){
    if(imap_part[b]==-1){
    imap_part[b]=counter;
    inodelocc=b;
    cout << inodelocc << endl;
    break;
    }
  }
  //imap_part[inodecounter] = counter;
  block *imapblock = new block();
  for(i = (inodecounter/256)*256; i < ((inodecounter/256)*256)+256; i++){
      imapblock->virtual_imap_block.imap_part[i] = imap_part[i];
  }
  counter++;
  counterx++;
  segment_type.push_back('i');

  virtual_segment.push_back(*imapblock);
  counterimap=counter;

  int checkpointImap = (inodelocc/256);
  checkpoint[checkpointImap]= counterimap;
  cout << checkpointImap << "=====================" << endl;
  cout << checkpoint[checkpointImap] << "------------------" << endl;

  counter++;
  counterx++;
  segment_type.push_back('m');

  /*int filedescF = open("DRIVE/FILEMAP.txt", O_WRONLY | O_APPEND, 0777);
  if(filedescF<0){
	cout << "ERROR OPENING FILEMAP" << endl;
    exit(1);
  }*/
  char null_byte = '\0';
  char newline[1] = {'\n'};
  char tabline[1] = {'\t'};

  //for(i = 0; i < file_name_length; i++)
  //{
    outfile << newBlock->virtual_inode.name;
  //}
  outfile << endl;
  outfile << inodelocc << endl;
  inodecounter++;

  //outfile.close();
  /*write(filedescF, &newBlock->virtual_inode.name,file_name_length);
  //write(filedescF, &newline, 1);
  write(filedescF, &null_byte ,name_remainder);
  //write(filedescF, &newline, 1);

  //int please = ((virtual_segment.size()-1)+(1024 * segment));
  int please = counter;
  write(filedescF, &please,4);*/

  //close(filedescF);
  
  if(virtual_segment.size()>1023){
    //write segment to disk
    live_segments[segment]='1';
    char x;
    int y;
    unsigned int z;
    string seg_name = "SEGMENT" + to_string(segment);
    const char * c = seg_name.c_str();
    int filedesc3 = open(c, O_WRONLY, 0777);
    if(filedesc3 < 0)
    {
      cout << "ERROR2" << endl;
      exit(1);
    }
    for(int k = 0; k < 1024; k++)
    {
      if(segment_type.at(k) == 'i')
      {
        for(j = 0; j < 128; j++)
        {
          x = virtual_segment[k].virtual_inode.name[j];
          write(filedesc3, &x, sizeof(x));
        }
        z = virtual_segment[k].virtual_inode.size;
        write(filedesc3, &z, sizeof(z));
        for(j = 0; j < 128; j++)
        {
          y = virtual_segment[k].virtual_inode.dblock[j];
          write(filedesc3, &y, sizeof(y));
        }
        for(j = 0; j < 380; j++)
        {
          x = virtual_segment[k].virtual_inode.dummy[j];
          write(filedesc3, &x, sizeof(x));
        }
      }
      if(segment_type.at(k) == 'd')
      {
        for(j = 0; j < 1024; j++)
        {
          x = virtual_segment[k].virtual_datablock.dataC[j];
          write(filedesc3, &x, sizeof(x));
        }
      }
      if(segment_type.at(k) == 'm')
      {
        for(j = 0; j < 256; j++)
        {
          y = virtual_segment[k].virtual_imap_block.imap_part[j];
          write(filedesc3, &y, sizeof(y));
        }
      }
    }
    close(filedesc3);
    virtual_segment.clear();
    segment_type.clear();
    segment++;
    if(segment==64){
      segment=0;
    }
  }
  
  /*imap_part[counterimap]= ((virtual_segment.size()-1)+(1024*segment));
  counterimap++;
  //imap_part.push_back((virtual_segment.size()-1)+(1024 * segment));
  
  if(counterimap==256){
    newBlock = new block();
    for(i = 0; i < 256; i++)
    {
      newBlock->virtual_imap_block.imap_part[i] = imap_part[i];
    }
    for(i=0;i<256;i++){
      imap_part[i]=-1;
    }
    //imap_part.clear();
    virtual_segment.push_back(*newBlock);
    cout << "Imap part at block " << counter << endl;
    int imapblock = counter;
    counter++;
    counterx++;
    int num = (virtual_segment.size()-1)+(1024 * segment);
    int filedesc2 = open("DRIVE/CHECKPOINT_REGION", O_WRONLY, 0777);
    if(filedesc2 < 0)
    {
      cout << "ERROR1" << endl;
      perror("ERROR");
      exit(1);
    }

    lseek(filedesc2, sizeof(live_segments), SEEK_CUR);
    write(filedesc2, &num, sizeof(num));
    lseek(filedesc2, 0, SEEK_END);
    write(filedesc2, &imapblock, sizeof(imapblock));
    close(filedesc2);

    segment_type.push_back('m');
    //imap_part.clear();
    counterimap=0;
  }*/

  for(int l=0;l<num_blocks;l++){
    newNode->dblock[l]=counterx;
    //counter++;
    //cout << "DBlock here!" << counterx << endl;
    counterx++;
    //if(counter>1023){
    //  counter=0;
    //}
  }
  
  if(virtual_segment.size()==1024){
    //write segment to disk
    live_segments[segment]='1';
    char x;
    int y;
    unsigned int z;
    string seg_name = "DRIVE/SEGMENT" + to_string(segment);
    const char * c = seg_name.c_str();
    int filedesc3 = open(c, O_WRONLY, 0777);
    if(filedesc3 < 0)
    {
      cout << "ERROR2" << endl;
      exit(1);
    }
    for(int k = 0; k < 1024; k++)
    {
      if(segment_type.at(k) == 'i')
      {
        for(j = 0; j < 128; j++)
        {
          x = virtual_segment[k].virtual_inode.name[j];
          write(filedesc3, &x, sizeof(x));
        }
        z = virtual_segment[k].virtual_inode.size;
        write(filedesc3, &z, sizeof(z));
        for(j = 0; j < 128; j++)
        {
          y = virtual_segment[k].virtual_inode.dblock[j];
          write(filedesc3, &y, sizeof(y));
        }
        for(j = 0; j < 380; j++)
        {
          x = virtual_segment[k].virtual_inode.dummy[j];
          write(filedesc3, &x, sizeof(x));
        }
      }
      if(segment_type.at(k) == 'd')
      {
        for(j = 0; j < 1024; j++)
        {
          x = virtual_segment[k].virtual_datablock.dataC[j];
          write(filedesc3, &x, sizeof(x));
        }
      }
      if(segment_type.at(k) == 'm')
      {
        for(j = 0; j < 256; j++)
        {
          y = virtual_segment[k].virtual_imap_block.imap_part[j];
          write(filedesc3, &y, sizeof(y));
        }
      }
    }
    close(filedesc3);
    virtual_segment.clear();
    segment_type.clear();
    segment++;
    if(segment==64){
      segment=0;
    }
  }
  
  //cout << "Num blocks: " << num_blocks << endl;
  int last_block_length = data_size % 1024;
  if(data_size == 0)
  {
    return;
  }
  if(last_block_length == 0)
  {
    last_block_length = 1024;
  }
  //cout << "Last block length: " << last_block_length << endl;

  datablock* data;
  
  vector<datablock*> blocks;

  
  for(i = 0; i < num_blocks-1; i++)
  {
    data = new datablock();
    blocks.push_back(data);
    read(filedescr, data->dataC, 1024);
    
    newerBlock = new block();
    newerBlock->virtual_datablock = *data;
    virtual_segment.push_back(*newerBlock);
    counter++;
    segment_type.push_back('d');
    
    if(virtual_segment.size()==1024){
      //write segment out to disk
      live_segments[segment]='1';
      char x;
      int y;
      unsigned int z;
      string seg_name = "DRIVE/SEGMENT" + to_string(segment);
      const char * c = seg_name.c_str();
      int filedesc3 = open(c, O_WRONLY, 0777);
      if(filedesc3 < 0)
      {
        cout << "ERROR3" << endl;
        exit(1);
      }
      for(int k = 0; k < 1024; k++)
      {
        if(segment_type.at(k) == 'i')
        {
          for(j = 0; j < 128; j++)
          {
            x = virtual_segment[k].virtual_inode.name[j];
            write(filedesc3, &x, sizeof(x));
          }
          z = virtual_segment[k].virtual_inode.size;
          write(filedesc3, &z, sizeof(z));
          for(j = 0; j < 128; j++)
          {
            y = virtual_segment[k].virtual_inode.dblock[j];
            write(filedesc3, &y, sizeof(y));
          }
          for(j = 0; j < 380; j++)
          {
            x = virtual_segment[k].virtual_inode.dummy[j];
            write(filedesc3, &x, sizeof(x));
          }
        }
        if(segment_type.at(k) == 'd')
        {
          for(j = 0; j < 1024; j++)
          {
            x = virtual_segment[k].virtual_datablock.dataC[j];
            write(filedesc3, &x, sizeof(x));
          }
        }
        if(segment_type.at(k) == 'm')
        {
          for(j = 0; j < 256; j++)
          {
            y = virtual_segment[k].virtual_imap_block.imap_part[j];
            write(filedesc3, &y, sizeof(y));
          }
        }
      }
      close(filedesc3);
      virtual_segment.clear();
      segment_type.clear();
      segment++;
      //cout << "yupppppp" << counter << endl;
      if(segment==64){
        segment=0;
      }
    }
    //cout << counter << "-------------" << i << "->>" << num_blocks << endl;
    
  }
  if(last_block_length > 0)
  {
    data = new datablock();
    read(filedescr, data->dataC, last_block_length);
    blocks.push_back(data);
    
    newerBlock = new block();
    newerBlock->virtual_datablock = *data;
    virtual_segment.push_back(*newerBlock);
    counter++;
    segment_type.push_back('d');
    
    if(virtual_segment.size()==1024){
    //write segment out to disk
      live_segments[segment]='1';
      char x;
      int y;
      unsigned int z;
      string seg_name = "DRIVE/SEGMENT" + to_string(segment);
      const char * c = seg_name.c_str();
      int filedesc3 = open(c, O_WRONLY, 0777);
      if(filedesc3 < 0)
      {
        cout << "ERROR4" << endl;
        exit(1);
      }
      for(int k = 0; k < 1024; k++)
      {
        if(segment_type.at(k) == 'i')
        {
          for(j = 0; j < 128; j++)
          {
            x = virtual_segment[k].virtual_inode.name[j];
            write(filedesc3, &x, sizeof(x));
          }
          z = virtual_segment[k].virtual_inode.size;
          write(filedesc3, &z, sizeof(z));
          for(j = 0; j < 128; j++)
          {
            y = virtual_segment[k].virtual_inode.dblock[j];
            write(filedesc3, &y, sizeof(y));
          }
          for(j = 0; j < 380; j++)
          {
            x = virtual_segment[k].virtual_inode.dummy[j];
            write(filedesc3, &x, sizeof(x));
          }
        }
        if(segment_type.at(k) == 'd')
        {
          for(j = 0; j < 1024; j++)
          {
            x = virtual_segment[k].virtual_datablock.dataC[j];
            write(filedesc3, &x, sizeof(x));
          }
        }
        if(segment_type.at(k) == 'm')
        {
          for(j = 0; j < 256; j++)
          {
            y = virtual_segment[k].virtual_imap_block.imap_part[j];
            write(filedesc3, &y, sizeof(y));
          }
        }
      }
      close(filedesc3);
      virtual_segment.clear();
      segment_type.clear();
      segment++;
    }
  }
  
  int counterd;
  /*for(i = 0; i < blocks.size(); i++)
  {
    counterd = 0;
    cout << "Block " << i << ": " << endl;
    while(counterd < 1024)
    {
      cout << blocks[i]->dataC[counterd];
      counterd++;
    }
    cout << endl;
  }*/
  close(filedescr);
  //cout << virtual_segment.size();
  
  /*for(int m=0;m<virtual_segment.size();m++){
    /*if(segment_type[m]=='d'){
      cout<<"Block at pos "<< m << endl;
      for(int u=0;u<1024;u++){
        cout << virtual_segment[m].virtual_datablock.dataC[u];
      }
      cout << endl;
    }
    if(segment_type[m]=='i'){
      //cout << "inode at pos " << m << endl;
      //printf("%s\n", virtual_segment[m].virtual_inode.name);
      for(int u = 0; u < 128; u++)
      {
        //cout << virtual_segment[m].virtual_inode.dblock[u] << endl;
      }
    }
    if(segment_type[m]=='m'){
      //cout << "map part at pos " << m << endl;
    }
  }*/
  outfile.close();
}


void list()
{
  int i;

  for(i = 0; i < segment_type.size(); i++)
  {
    if(segment_type[i] == 'i')
    {
      cout << virtual_segment[i].virtual_inode.name << endl;
      cout << virtual_segment[i].virtual_inode.size << endl;
    }
  }

  string filename;
  int readLocation;
  string line;

  ifstream infile;
  infile.open("DRIVE/FILEMAP.txt");
  while(getline(infile, line)){

    filename += line + ",";
    
  }
  infile.close();
  cout << filename << endl;
  vector<string> vect;

  stringstream ss(filename);
  string h;

  while(getline(ss,h,',')){
    vect.push_back(h);
  }

  int filedescr2;

  while(k<vect.size()){
	cout << "K: " << k << " " << vect.size() << endl;
    cout << vect[k] << endl;
    k++;
    int yo;
    //cout << k << "yo" << endl;
    if(k%2==1){
      yo = stoi(vect[k]);
    }
    int inodeLocation=imap_part[yo];
    cout << inodeLocation << endl;
    int segmentNum = (inodeLocation)/1024;
    cout << "Segment num: " <<  segmentNum << endl;
    int relInodeNum = (inodeLocation) % 1024;
    cout << "Inode num in segment: " << relInodeNum << " " << inodeLocation << endl;
    string seg_name = "DRIVE/SEGMENT" + to_string(segmentNum);

    const char * c = seg_name.c_str();

    //cout << "yo" << endl;

    cout << c << endl;

    filedescr2 = open(c, O_RDONLY, 0777);

    if(filedescr2 < 0){

      cout << "ERROR OPENING SEGMENT" << segmentNum << " FOR READ" << endl;

      exit(1);

    }

    char* useless;
	//char *useless2;
    int filesize;

    lseek(filedescr2, (relInodeNum*1024 + 128), SEEK_CUR);
	//read(filedescr2, &useless2, 128);
    int readMAYBE = read(filedescr2, &filesize, 4);
    if(readMAYBE<0){
      //char *errorsum;
      cout << "ERROR READING FILESIZE FROM SEGMENT" << segmentNum << " CLOSING" << endl;
      perror("THE FOLLOWING ERROR OCCURRED");
      exit(1);
    }
    cout << "FILE SIZE: " << filesize << endl;
    close(filedescr2);
    //cout << "K: " << k << " " << vect.size() <<  endl;*/
    k++;
  }
}

void shutdown()
{
  /*block *newBlock = new block();
  for(int i = 0; i < 256; i++)
  {
    newBlock->virtual_imap_block.imap_part[i] = imap_part[i];
  }
  for(int i=0;i<256;i++){
    imap_part[i]=-1;
  }
  virtual_segment.push_back(*newBlock);
  segment_type.push_back('m');*/
  int imapblock = counter;
  //counter++;
  //counterx++;
  //cout << virtual_segment.size() << endl;
  while(virtual_segment.size() < 1024){
    block* dummyBlock = new block();
    virtual_segment.push_back(*dummyBlock);
    counter++;
    segment_type.push_back('d');
    //cout << virtual_segment.size() << endl;
  }
  string str = "DRIVE/SEGMENT" + to_string(segment);
  int filedescw1 = open(str.c_str(), O_WRONLY, 0777);
  if(filedescw1<0){
    cout << "ERROR OCCURRED OPENING SEGMENT" << segment << endl;
    exit(1);
  }

  int j=0;
  int y=0;
  char x;
  unsigned int z=0;

  live_segments[segment]='1';

  //cout << virtual_segment.size() << "yo" << endl;

  for(int k = 0; k < 1024; k++)
      {

        if(segment_type.at(k) == 'i')
        {
          for(j = 0; j < 128; j++)
          {
            x = virtual_segment[k].virtual_inode.name[j];
            write(filedescw1, &x, sizeof(x));
          }
          z = virtual_segment[k].virtual_inode.size;
          write(filedescw1, &z, sizeof(z));
          for(j = 0; j < 128; j++)
          {
            y = virtual_segment[k].virtual_inode.dblock[j];
            write(filedescw1, &y, sizeof(y));
          }
          for(j = 0; j < 380; j++)
          {
            x = virtual_segment[k].virtual_inode.dummy[j];
            write(filedescw1, &x, sizeof(x));
          }
        }
        if(segment_type.at(k) == 'd')
        {
          for(j = 0; j < 1024; j++)
          {
	    //cout << "made it" << j << endl;
            x = virtual_segment[k].virtual_datablock.dataC[j];
            write(filedescw1, &x, sizeof(x));
          }
        }
        if(segment_type.at(k) == 'm')
        {
          for(j = 0; j < 256; j++)
          {
            y = virtual_segment[k].virtual_imap_block.imap_part[j];
            write(filedescw1, &y, sizeof(y));
          }
        }
      }
  close(filedescw1);
  virtual_segment.clear();
  segment_type.clear();
  segment++;

  int filedescw3 = open("DRIVE/CHECKPOINT_REGION", O_WRONLY, 0777);
  if(filedescw3<0){
    cout << "ERROR OPENING CHECKPOINT REGION CLOSING 1" << endl;
    exit(1);
  }
  write(filedescw3, &segment, sizeof(segment));
  close(filedescw3);

  int filedescw2 = open("DRIVE/CHECKPOINT_REGION", O_WRONLY, 0777);
  if(filedescw2<0){
    cout << "ERROR OPENING CHECKPOINT REGION CLOSING 1" << endl;
    exit(1);
  }

  lseek(filedescw2, 4, SEEK_CUR);
  write(filedescw2, &live_segments, sizeof(live_segments));
  for(int y=0;y<64;y++){
    cout << live_segments[y];
  }
  cout << endl;
  close(filedescw2);

  for(int p=0;p<40;p++){
    filedescw2 = open("DRIVE/CHECKPOINT_REGION", O_WRONLY, 0777);
    if(filedescw2<0){
      cout << "ERROR OPENING CHECKPOINT REGION CLOSING 2" << endl;
      exit(1);
    } 
    lseek(filedescw2, 68+(p*4), SEEK_CUR);
    cout << checkpoint[p] << endl;
    write(filedescw2, &checkpoint[p], sizeof(checkpoint[p]));
    close(filedescw2);
  }

  //exit(1);
}

void remove1(string filename)
{

  cout << "start of remove" << endl;
  
  int inode_num=0;
  bool next = 0;
  string line;
  ifstream file;
  file.open("DRIVE/FILEMAP.txt");
  if(file.is_open())
  {
    while(getline(file, line))
    {
      if(line == filename)
      {
        next = 1;
        continue;
      }
      if(next)
      {
        inode_num = stoi(line);
        break;
      }
    }
    file.close();
  }
  else
  {
    cout << "Unable to open FILEMAP.txt" << endl;
  }

  imap_part[inode_num] = -1;

  
  /*cout << "Inode number = " << inode_num << endl;
  int filedesc = open("DRIVE/CHECKPOINT_REGION", O_RDONLY, 0777);
  if(filedesc<0){
    cout << "ERROR OPENING CHECKPOINT REGION IN REMOVE" << endl;
    exit(1);
  }
  int imap_part_location = 0;
  int inode_offset = inode_num % 256;
  lseek(filedesc, 68+(4*(inode_num/256)), SEEK_CUR);
  read(filedesc, &imap_part_location, sizeof(imap_part_location));
  int segment_num = imap_part_location/1024;
  int offset_num = imap_part_location % 1024;
  close(filedesc);

  string seg = "DRIVE/SEGMENT" + to_string(segment_num);
  const char *c = seg.c_str();

  int filedescr = open(c, O_RDONLY, 0777);
  if(filedescr<0){
    cout << "ERROR OPENING SEGMENT" << segment_num << " IN REMOVE" << endl;
    exit(1);
  }
  int inode_location = 0;
  lseek(filedescr, offset_num+(inode_offset*4), SEEK_CUR);
  read(filedescr, &inode_location, sizeof(inode_location));
  close(filedescr);

  int filedescr1 = open(c, O_WRONLY, 0777);
  if(filedescr1<0){
    cout << "ERROR OPENING SEGMENT" << segment_num << " IN REMOVE" << endl;
    exit(1);
  }
  int negativeOne = -1;
  lseek(filedescr1, offset_num+(inode_offset*4), SEEK_CUR);
  write(filedescr1, &negativeOne, sizeof(negativeOne));
  close(filedescr1);

  filedescr1 = open(c, O_RDONLY, 0777);
  if(filedescr1<0){
    cout << "ERROR OPENING SEGMENT" << segment_num << " IN REMOVE" << endl;
    exit(1);
  }

 
  int aoibf;
  lseek(filedescr1, offset_num+(inode_offset*4), SEEK_CUR);
  read(filedescr1, &aoibf, sizeof(aoibf));
  close(filedescr1);
  cout << aoibf << endl;*/

  ofstream temp;
  file.open("DRIVE/FILEMAP.txt");
  temp.open("DRIVE/temp.txt");
  string line1;
  while(getline(file, line))
  {
    if(line != filename)
    {
      temp << line << endl;
    }
    else
    {
      getline(file, line);
    }
  }

  remove("DRIVE/FILEMAP.txt");
  rename("DRIVE/temp.txt", "DRIVE/FILEMAP.txt");
  
  return;
}

void setup(){
  int filedescr = open("DRIVE/CHECKPOINT_REGION", O_RDONLY, 0777);
  if(filedescr<0){

    cout << "ERROR OPENING CHECKPOINT REGION IN REMOVE" << endl;
    exit(1);
  }
  int segment_num=0;
  read(filedescr, &segment_num, sizeof(segment_num));
  segment=segment_num;
  close(filedescr);
}

long getfilesize(string filename)
{
  const char * file_name = filename.c_str();
  struct stat st;
  if(stat(file_name,&st)==0)
    return (st.st_size);
  else
    return -1;
}
