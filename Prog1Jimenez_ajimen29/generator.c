#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "generator.h"

//int main(int argc, char **argv, char *envp[]){


/*generator::generator(){
	int RandomNums = 100;
	int maxNum = 255;
	int minNum = 1;
	unsigned long seed = 0;
	//int opt;
	//char *filename;

	int uflag=0;
	int nflag=0;
	int mflag=0;
	int Mflag=0;
	int sflag=0;
	int oflag=0;
}*/

void run(struct generator g, int argc, char **argv, char *envp[]){
	srand(time(NULL));
	while((g.opt = getopt(argc, argv, "un:m:M:s:o:")) != -1){
	
		switch(g.opt){
			case 'u':
				fprintf (stderr, "Program must be called as follows --> prog1generator [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>] \n");
				return;
				break;
			case 'n':
				if(g.nflag==1){
					fprintf(stderr, "Multiple instances of 'n' found. Exiting.");
					return;
				}
				g.nflag=1;
				if(atoi(optarg) < 0){
					fprintf(stderr, "Total number of integers cannot be less than 0. Exiting.");
					return;
				}
				g.RandomNums = atoi(optarg);
				break;
			case 'm':
				if(g.mflag==1){
					fprintf(stderr, "Multiple instances of 'm' found. Exiting.");
					return;
				}
				if(atoi(optarg)<1){
					fprintf(stderr, "Minimum integer cannot be less than 1. Exiting.");
					return;
				}
				g.mflag=1;
				g.minNum= atoi(optarg);
				break;
			case 'M':
				if(g.Mflag==1){
					fprintf(stderr, "Multiple instances of 'M' found. Exiting.");
					return;
				}
				if(atoi(optarg) < g.minNum || atoi(optarg) > g.maxNum){
					fprintf(stderr, "Max integer cannot be smaller than the minimum nor can it be larger than 1,000,000. Exiting.");
					return;
				}
				g.Mflag=1;
				g.maxNum= atoi(optarg);
				break;
			case 's':
				if(g.sflag==1){
					fprintf(stderr, "Multiple instances of 's' found. Exiting.\n");
					return;
				}
				g.sflag=1;
				g.seed = strtoul(optarg,NULL,10);
				break;
			case 'o':
				if(g.oflag==1){
					fprintf(stderr, "Multiple instances of 'o' found. Exiting.\n");
					return;
				}
				g.oflag=1;
				g.filename = optarg;
				//printf(g.filename);
				break;
			case '?':
				if(optopt == 'n' || optopt == 'm' || optopt == 'M' || optopt == 's' || optopt == 'o'){
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
					return;
					break;
				}else{
					fprintf(stderr, "Option -%c is unrecognized. Program must be called as follows --> prog1generator [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>]", optopt);
					return;
					break;
				}
				
		}
				
	}

	if(g.sflag==1){
		srand(g.seed);
	}

	if(g.oflag==1){
		FILE *file = fopen(g.filename, "w+");
		if(file == NULL){
			fprintf(stderr, "Error opening file.\n");
			exit(1);
		}
		//fprintf(file, "%d\n", g.RandomNums);
		for(int i=0;i<g.RandomNums;i++){
			fprintf(file, "%d\n", (rand() % (g.maxNum-g.minNum))+g.minNum);
		}
		fclose(file);
	}else{

		//printf("%d\n", g.RandomNums);
		//printf("%d\n", minNum);
		//printf("%d\n", maxNum);

		for(int i=0;i<g.RandomNums;i++){
			printf("%d\n", (rand() % (g.maxNum-g.minNum))+g.minNum);
		}
	}




	//return 0;
}
