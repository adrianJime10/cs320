#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sorter.h"

void run(struct sorter *g, int argc, char **argv, char *envp[]){
	while((g->opt = getopt(argc, argv, "un:m:M:c:o:i:")) != -1){
	
		switch(g->opt){
			case 'u':
				fprintf (stderr, "Program must be called as follows --> prog1sorter [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-i <intput-file-name>] [-o <output-file-name>] [-c <count-file-name>]\n");
				exit(1);
				break;
			case 'n':
				if(g->nflag==1){
					fprintf(stderr, "Multiple instances of 'n' found. Exiting.");
					exit(1);
				}
				g->nflag=1;
				if(atoi(optarg) < 0){
					fprintf(stderr, "Total number of integers cannot be less than 0. Exiting.");
					exit(1);
				}
				g->RandomNums = atoi(optarg);
				break;
			case 'm':
				if(g->mflag==1){
					fprintf(stderr, "Multiple instances of 'm' found. Exiting.");
					exit(1);
				}
				if(atoi(optarg)<1){
					fprintf(stderr, "Minimum integer cannot be less than 1. Exiting.");
					exit(1);
				}
				g->mflag=1;
				g->minNum= atoi(optarg);
				break;
			case 'M':
				if(g->Mflag==1){
					fprintf(stderr, "Multiple instances of 'M' found. Exiting.");
					exit(1);
				}
				if(atoi(optarg) < g->minNum || atoi(optarg) > g->maxNum){
					fprintf(stderr, "Max integer cannot be smaller than the minimum nor can it be larger than 1,000,000. Exiting.");
					exit(1);
				}
				g->Mflag=1;
				g->maxNum= atoi(optarg);
				break;
			case 'c':
				if(g->cflag==1){
					fprintf(stderr, "Multiple instances of 'c' found. Exiting.\n");
					exit(1);
				}
				g->cfile = optarg;
				g->cflag = 1;
				//g.seed = strtoul(optarg,NULL,10);
				break;
			case 'o':
				if(g->oflag==1){
					fprintf(stderr, "Multiple instances of 'o' found. Exiting.\n");
					exit(1);
				}
				g->filename = optarg;
				g->oflag = 1;
				//printf(g.filename);
				break;
			case 'i':
				if(g->iflag==1){
					fprintf(stderr, "Multiple instances of 'i' found. Exiting.\n");
					exit(1);
				}
				g->ifile=optarg;
				g->iflag=1;
				break;
			case '?':
				if(optopt == 'n' || optopt == 'm' || optopt == 'M' || optopt == 'c' || optopt == 'o' || optopt == 'i'){
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
					exit(1);
					break;
				}else{
					fprintf(stderr, "Option -%c is unrecognized. Program must be called as follows --> prog1sorter [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-c <count-file-name>] [-i <input-file-name] [-o <output-file-name>]", optopt);
					exit(1);
					break;
				}
				
		}
				
	}

/*	if(g->iflag==0){
		scanf("%d", &g->RandomNums);
		//malloc1(&g);
		g->arr = (int*) malloc (g->RandomNums * sizeof(int));
		int n;
		
		for(int i=0;i<g->RandomNums;i++){
			scanf("%d", (g->arr + i));
		}
	}else if(g->iflag==1){
		FILE *file = fopen(g->ifile, "r");
		fscanf(file, "%d", &g->RandomNums);
		//malloc1(&g);
		g->arr = (int*) malloc (g->RandomNums * sizeof(int));
		for(int i=0;i<g->RandomNums;i++){
			fscanf(file, "%d", (g->arr + i));
		}
		fclose(file);
	}
	
	//qsort(g.arr, g.RandomNums, sizeof(int), cmpfunc);
/*
	for(int i=0;i<(sizeof(g.arr)/sizeof(g.arr[0]));i++){
		printf("-%d\n",g.arr[i]);
	}

	printf("-%d\n",sizeof(g->arr));
		

/*
	if(g.oflag==1){
		FILE *file = fopen(g.filename, "w+");
		if(file == NULL){
			fprintf(stderr, "Error opening file.\n");
			exit(1);
		}
		fprintf(file, "%d\n", g.RandomNums);
		for(int i=0;i<g.RandomNums;i++){
			fprintf(file, "%d\n", (rand() % (g.maxNum-g.minNum))+g.minNum);
		}
		fclose(file);
	}else{

		printf("%d\n", g.RandomNums);
		//printf("%d\n", minNum);
		//printf("%d\n", maxNum);

		for(int i=0;i<g.RandomNums;i++){
			printf("%d\n", (rand() % (g.maxNum-g.minNum))+g.minNum);
		}
	}*/


	//PRINTS USER
	/*for(int i=5;i<strlen(envp[9]);i++){
		printf("%c", envp[9][i]);
	}
	printf("\n");
	*/

	//return 0;
}
