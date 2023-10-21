#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "processTree.h"

void run(struct processTree *g, int argc, char **argv, char *envp[]){
	while((g->opt = getopt(argc, argv, "uN:M:ps:")) != -1){
	
		switch(g->opt){
			case 'u':
				fprintf (stderr, "Program must be called as follows --> prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time>]\n");
				exit(1);
				break;
			case 'N':
				if(g->nflag==1){
					fprintf(stderr, "Multiple instances of 'N' found. Exiting.");
					exit(1);
				}
				g->nflag=1;
				if(atoi(optarg) < 1){
					fprintf(stderr, "Total number of levels cannot be less than 1. Exiting.");
					exit(1);
				}
				if(atoi(optarg)>4){
					fprintf(stderr, "Total number of levels cannot be greater than 4. Exiting.");
				}
				g->numLevels = atoi(optarg);
				break;
			case 'M':
				if(g->mflag==1){
					fprintf(stderr, "Multiple instances of 'M' found. Exiting.");
					exit(1);
				}
				if(atoi(optarg)<1){
					fprintf(stderr, "Number of children cannot be less than 1. Exiting.");
					exit(1);
				}
				if(atoi(optarg)>3){
					fprintf(stderr, "Number of children cannot be greater than 3. Exiting.");
				}
				g->mflag=1;
				g->numChildren= atoi(optarg);
				break;
			case 'p':
				if(g->pflag==1){
					fprintf(stderr, "Multiple instances of 'p' found. Exiting.\n");
					exit(1);
				}
				if(g->sflag==1){
					fprintf(stderr, "-s was already specified. Exiting.\n");
					exit(1);
				}
				g->pflag = 1;
				//printf(g.filename);
				break;
			case 's':
				if(g->sflag==1){
					fprintf(stderr, "Multiple instances of 's' found. Exiting.\n");
					exit(1);
				}
				if(g->pflag==1){
					fprintf(stderr, "-p was already specified. Exiting.\n");
					exit(1);
				}
				if(atoi(optarg)<0){
					fprintf(stderr, "Cannot sleep for less than 0 seconds. Exiting.\n");
				}
				g->sflag=1;
				g->sleepTime= atoi(optarg);
				break;
			case '?':
				if(optopt == 'N' || optopt == 'M' || optopt == 's'){
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
					exit(1);
					break;
				}else{
					fprintf(stderr, "Option -%c is unrecognized. Program must be called as follows -> prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time>]\n", optopt);
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
