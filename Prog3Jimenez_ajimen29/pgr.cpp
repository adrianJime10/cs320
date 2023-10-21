#include "pgr.h"
#include <queue>
#include <iomanip>
#include <fstream>

using namespace std;

vector<double> opt(int* trace)
{
    vector<vector<int>> frames = create_frames();
    
    int frameCounter = 0;
    int pageFaults = 0;
    int furthest_page = 0;
    int totalPages = 0;
    double pageHit = 0;
    int ind = 0;
    vector<double> hitRates(20,0);
    
    while(frameCounter < 20)
    {
        vector<int> array(frames[frameCounter].size(), 0);
        furthest_page = 0;
        pageHit = 0;
        for(int i = 0; i < 10000; i++)
        {
            totalPages++;
            
            //Check each frame for the page we want to access
            for(int j = 0; j < frames[frameCounter].size(); j++)
            {
                if(trace[i] == frames[frameCounter][j])
                {
                    pageHit++;
                    break;
                }
                else if(frames[frameCounter][j] == -1)
                {
                    frames[frameCounter][j] = trace[i];
                    pageFaults++;
                    break;
                }
                
                //If we reach the end of the cache and havent found the page, it isnt                     present, increment page fault, choose victim, and replace page
                else if(j == (frames[frameCounter].size() - 1))
                {
                    for(ind = 0; ind < frames[frameCounter].size(); ind++)
                    {
                        for(int k = i; k < 10000; k++)
                        {
                            if(trace[k] == frames[frameCounter][ind])
                            {
                                array[ind]=k;
                                break;
                            }
                        }
                    }
                    int page = 0;
                    int max=0;
                    for(int h=0;h<array.size();h++){
                        if(array[h]>max){
                            page=h;
                            max=array[h];
                        }
                    }
                    pageFaults++;
                    frames[frameCounter][page] = trace[i];
                }
            }
        }
        hitRates[frameCounter] = (pageHit/10000) * 100;
        frameCounter++;
    }
    return hitRates;
}

vector<double> lru(int* trace)
{
    vector<deque<int> > frames(20);
    
    deque<int> frames5(5,-1);
    deque<int> frames10(10,-1);
    deque<int> frames15(15,-1);
    deque<int> frames20(20,-1);
    deque<int> frames25(25,-1);
    deque<int> frames30(30,-1);
    deque<int> frames35(35,-1);
    deque<int> frames40(40,-1);
    deque<int> frames45(45,-1);
    deque<int> frames50(50,-1);
    deque<int> frames55(55,-1);
    deque<int> frames60(60,-1);
    deque<int> frames65(65,-1);
    deque<int> frames70(70,-1);
    deque<int> frames75(75,-1);
    deque<int> frames80(80,-1);
    deque<int> frames85(85,-1);
    deque<int> frames90(90,-1);
    deque<int> frames95(95,-1);
    deque<int> frames100(100,-1);
    
    frames[0]=frames5;
    frames[1]=frames10;
    frames[2]=frames15;
    frames[3]=frames20;
    frames[4]=frames25;
    frames[5]=frames30;
    frames[6]=frames35;
    frames[7]=frames40;
    frames[8]=frames45;
    frames[9]=frames50;
    frames[10]=frames55;
    frames[11]=frames60;
    frames[12]=frames65;
    frames[13]=frames70;
    frames[14]=frames75;
    frames[15]=frames80;
    frames[16]=frames85;
    frames[17]=frames90;
    frames[18]=frames95;
    frames[19]=frames100;
    
    int frameCounter = 0;
    int pageFaults = 0;
    int totalPages = 0;
    double pageHit = 0;
    vector<double> hitRates(20,0);
    
    while(frameCounter < 20)
    {
        pageHit = 0;
	pageFaults = 0;
	totalPages = 0;
        for(int i = 0; i < 10000; i++)
        {
            totalPages++;
            
            //Check each frame for the page we want to access
            for(int j = 0; j < frames[frameCounter].size(); j++)
            {
                if(trace[i] == frames[frameCounter][j])
                {
                    pageHit++;
		    int temp = frames[frameCounter][j];
		    frames[frameCounter].erase(frames[frameCounter].begin() + j);
		    frames[frameCounter].push_front(temp);
                    break;
                }
                else if(frames[frameCounter][j] == -1)
                {
                    frames[frameCounter].pop_back();
                    frames[frameCounter].push_front(trace[i]);
                    pageFaults++;
                    break;
                }
                
                //If we reach the end of the cache and havent found the page, it isnt                     present, increment page fault, choose victim, and replace page
                else if(j == (frames[frameCounter].size() - 1))
                {
                    pageFaults++;
                    frames[frameCounter].pop_back();
                    frames[frameCounter].push_front(trace[i]);
                }
            }
        }
        hitRates[frameCounter] = (pageHit/10000) * 100;
	cout << "LRU" <<(pageHit/10000)*100 << endl;
        frameCounter++;
    }
    return hitRates;
}

vector<double> fifo(int* pagesAccessed)
{
	//Each 'cache size' initialized to empty caches
	vector<int> frames5(5,-1);
	vector<int> frames10(10,-1);
	vector<int> frames15(15,-1);
	vector<int> frames20(20,-1);
	vector<int> frames25(25,-1);
	vector<int> frames30(30,-1);
	vector<int> frames35(35,-1);
	vector<int> frames40(40,-1);
	vector<int> frames45(45,-1);
	vector<int> frames50(50,-1);
	vector<int> frames55(55,-1);
	vector<int> frames60(60,-1);
	vector<int> frames65(65,-1);
	vector<int> frames70(70,-1);
	vector<int> frames75(75,-1);
	vector<int> frames80(80,-1);
	vector<int> frames85(85,-1);
	vector<int> frames90(90,-1);
	vector<int> frames95(95,-1);
	vector<int> frames100(100,-1);

	vector<vector<int> > frames(20);
	frames[0]=frames5;
	frames[1]=frames10;
	frames[2]=frames15;
	frames[3]=frames20;
	frames[4]=frames25;
	frames[5]=frames30;
	frames[6]=frames35;
	frames[7]=frames40;
	frames[8]=frames45;
	frames[9]=frames50;
	frames[10]=frames55;
	frames[11]=frames60;
	frames[12]=frames65;
	frames[13]=frames70;
	frames[14]=frames75;
	frames[15]=frames80;
	frames[16]=frames85;
	frames[17]=frames90;
	frames[18]=frames95;
	frames[19]=frames100;

	//Counter to choose which cache we are currently simulating
        vector<double> hitRates(20,0);

	int frameCounter=0;
	int pageFaults=0;
	int firstIn=0;
	int totalPages=0;
	double pageHit=0;
	//int counter;

	/*for(int i =0; i<20;i++){
		//counter = 0;
		for(int j=0;j<frames[i].size();j++){
			cout << frames[i][j] << endl;
			//counter++;
		}
	}*/
	
	//Simulate each cache size
	while(frameCounter<20){
		firstIn=0;
		pageHit=0;
		for(int i=0; i<10000; i++){
			totalPages++;
			//cout << "--------" << totalPages << endl;
			//cout << pagesAccessed[i] << endl;

			//Check each frame for the page we want to access
			for(int j=0; j<frames[frameCounter].size();j++){
				//cout << j << endl;
				if(pagesAccessed[i]==frames[frameCounter][j]){
					pageHit++;
					break;
				}
				else if(frames[frameCounter][j]==-1){
					frames[frameCounter][j]=pagesAccessed[i];
					pageFaults++;
					break;
				}

				//If we reach the end of the cache and havent found the page, it isnt 					present, increment page fault, choose victim, and replace page
				else if(j==(frames[frameCounter].size()-1)){
					if(firstIn>(frames[frameCounter].size()-1)){
						firstIn=0;
					}
					pageFaults++;
					frames[frameCounter][firstIn]=pagesAccessed[i];
					//cout << firstIn << " vicPag/ " << frames[frameCounter].size() << " size/ " << frames[frameCounter][j] << " currentPage/ " << pagesAccessed[i] << " pageAc/ " << j << endl;
					firstIn++;
				}
			}
		}
	hitRates[frameCounter] = (pageHit/10000) * 100;
	frameCounter++;
	}
	return hitRates;
	//cout << pageFaults << endl;
	//cout << totalPages << endl;
    
}

vector<double> random_pgr(int* trace)
{
    vector<vector<int> > frames = create_frames();

    vector<double> hitRates(20,0);
    
    int frameCounter = 0;
    int pageFaults = 0;
    int randPage = 0;
    int totalPages = 0;
    double pageHit = 0;
    
    while(frameCounter < 20)
    {
        randPage = 0;
        pageHit = 0;
        for(int i = 0; i < 10000; i++)
        {
            totalPages++;
            
            //Check each frame for the page we want to access
            for(int j = 0; j < frames[frameCounter].size(); j++)
            {
                if(trace[i] == frames[frameCounter][j])
                {
                    pageHit++;
                    break;
                }
                else if(frames[frameCounter][j] == -1)
                {
                    frames[frameCounter][j] = trace[i];
                    pageFaults++;
                    break;
                }
                
                //If we reach the end of the cache and havent found the page, it isnt                     present, increment page fault, choose victim, and replace page
                else if(j == (frames[frameCounter].size() - 1))
                {
                    randPage = rand() % frames[frameCounter].size();
                    pageFaults++;
                    frames[frameCounter][randPage] = trace[i];
                }
            }
        }
        hitRates[frameCounter] = (pageHit/10000) * 100;
        frameCounter++;
	cout << "RAND" << (pageHit/10000)*100 << endl;
    }
    return hitRates;
}

vector<double> clock_pgr(int* trace)
{
    vector<vector<int> > frames = create_frames();

    vector<double> hitRates(20,0);
    
    int frameCounter = 0;
    int pageFaults = 0;
    int totalPages = 0;
    double pageHit = 0;
    
    while(frameCounter < 20)
    {
        int i;
        int bits[frameCounter * 5];
        for(i = 0; i < frameCounter*5; i++)
        {
            bits[i] = 0;
        }
        
        int clock_hand = 0;
        
        pageHit = 0;
        for(i = 0; i < 10000; i++)
        {
            totalPages++;
            
            //Check each frame for the page we want to access
            for(int j = 0; j < frames[frameCounter].size(); j++)
            {
                if(trace[i] == frames[frameCounter][j])
                {
		    bits[j]=1;
                    pageHit++;
                    break;
                }
                else if(frames[frameCounter][j] == -1)
                {
                    bits[j] = 1;
                    frames[frameCounter][j] = trace[i];
                    pageFaults++;
                    break;
                }
                
                //If we reach the end of the cache and havent found the page, it isnt                     present, increment page fault, choose victim, and replace page
                else if(j == (frames[frameCounter].size() - 1))
                {
                    while(bits[clock_hand] == 1)
                    {
                        bits[clock_hand] = 0;
                        clock_hand++;
                        if(clock_hand > frames[frameCounter].size()-1)
                        {
                            clock_hand = 0;
                        }
                    }
                    frames[frameCounter][clock_hand] = trace[i];
                    bits[clock_hand] = 1;
                    pageFaults++;
                }
            }
        }
        hitRates[frameCounter] = (pageHit/10000) * 100;
	
        frameCounter++;
	cout << "CLOCK" << (pageHit/10000)*100 << endl;
    }
    return hitRates;
}

vector<vector<int> > create_frames()
{
    vector<int> frames5(5,-1);
    vector<int> frames10(10,-1);
    vector<int> frames15(15,-1);
    vector<int> frames20(20,-1);
    vector<int> frames25(25,-1);
    vector<int> frames30(30,-1);
    vector<int> frames35(35,-1);
    vector<int> frames40(40,-1);
    vector<int> frames45(45,-1);
    vector<int> frames50(50,-1);
    vector<int> frames55(55,-1);
    vector<int> frames60(60,-1);
    vector<int> frames65(65,-1);
    vector<int> frames70(70,-1);
    vector<int> frames75(75,-1);
    vector<int> frames80(80,-1);
    vector<int> frames85(85,-1);
    vector<int> frames90(90,-1);
    vector<int> frames95(95,-1);
    vector<int> frames100(100,-1);
    
    vector<vector<int> > frames(20);
    frames[0]=frames5;
    frames[1]=frames10;
    frames[2]=frames15;
    frames[3]=frames20;
    frames[4]=frames25;
    frames[5]=frames30;
    frames[6]=frames35;
    frames[7]=frames40;
    frames[8]=frames45;
    frames[9]=frames50;
    frames[10]=frames55;
    frames[11]=frames60;
    frames[12]=frames65;
    frames[13]=frames70;
    frames[14]=frames75;
    frames[15]=frames80;
    frames[16]=frames85;
    frames[17]=frames90;
    frames[18]=frames95;
    frames[19]=frames100;
    
    return frames;
}

void writeNoLocal(int* nums, vector<double> opt, vector<double> lru, vector<double> fifo, vector<double> random, vector<double> clock){
	ofstream myfile;
	myfile.open("noLocal.csv");
	myfile << "#cache,OPT,LRU,FIFO,RAND,CLOCK" << endl;
	myfile << "0,0,0,0,0,0" << endl;
	for(int i=1;i<21;i++){
	myfile << i*5 << "," << opt[i-1] << "," << lru[i-1] << "," << fifo[i-1] << "," << random[i-1] << "," << clock[i-1] << endl;
}
	myfile.close();
}

void write8020(int* nums, vector<double> opt, vector<double> lru, vector<double> fifo, vector<double> random, vector<double> clock){
	ofstream myfile;
	myfile.open("eightytwenty.csv");
	myfile << "#cache,OPT,LRU,FIFO,RAND,CLOCK" << endl;
	myfile << "0,0,0,0,0,0" << endl;
	for(int i=1;i<21;i++){
	myfile << i*5 << "," << opt[i-1] << "," << lru[i-1] << "," << fifo[i-1] << "," << random[i-1] << "," << clock[i-1] << endl;
}
	myfile.close();
}

void writeLooping(int* nums, vector<double> opt, vector<double> lru, vector<double> fifo, vector<double> random, vector<double> clock){
	ofstream myfile;
	myfile.open("looping.csv");
	myfile << "#cache,OPT,LRU,FIFO,RAND,CLOCK" << endl;
	myfile << "0,0,0,0,0,0" << endl;
	for(int i=1;i<21;i++){
	myfile << i*5 << "," << opt[i-1] << "," << lru[i-1] << "," << fifo[i-1] << "," << random[i-1] << "," << clock[i-1] << endl;
}
	myfile.close();
}
