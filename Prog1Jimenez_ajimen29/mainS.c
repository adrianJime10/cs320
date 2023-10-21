#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sorter.c"
#include <time.h>
#include <errno.h>

int cmpfunc(const void *a, const void *b){
	return (*(int*)a - *(int*)b);
}

int main(int argc, char **argv, char *envp[]){

	struct sorter *g;

	g=(struct sorter*)malloc(sizeof(struct sorter));
	errno = 0;

	g->minNum=1;
	g->maxNum=255;
	g->uflag=0;
	g->nflag=0;
	g->mflag=0;
	g->cflag=0;
	g->Mflag=0;
	g->iflag=0;
	g->oflag=0;
	g->RandomNums=100;

	run(g, argc, argv, envp);

	double tElapsed;
	clock_t start, end;
	start=clock();

	if(g->iflag==0){
		//scanf("%d", &g->RandomNums);
		g->arr = (int*) malloc (((g->RandomNums)+1) * sizeof(int));
		int n=0;
		
		//for(int i=0;i<g->RandomNums;i++){
		while(n<g->RandomNums && scanf("%d", (g->arr+n))!=EOF){
			if((g->arr[n])<g->minNum || (g->arr[n])>g->maxNum){
				fprintf(stderr,"Value cannot be less than minimum value. Exiting.\n");
				exit(1);
			}
			n++;
		}
		g->arr[g->RandomNums]=-1;
	}else if(g->iflag==1){
		//printf("Made it here.");
		FILE *file = fopen(g->ifile, "r");
		//fscanf(file, "%d", &g->RandomNums);
		g->arr = (int*) malloc (((g->RandomNums)+1) * sizeof(int));
		//for(int i=0;i<g->RandomNums;i++){
		int n=0;
		while(n<g->RandomNums && fscanf(file,"%d", (g->arr+n))!=EOF){
			//fscanf(file, "%d", &(g->arr[n]));
			if((g->arr[n])<g->minNum || (g->arr[n])>g->maxNum){
				printf("%d",g->arr[n]);
				fprintf(stderr,"Value cannot be less than minimum value or greater than the maximum value. Exiting.\n");
				exit(1);
			}
			n++;
		}
		fclose(file);
		//printf("And then here.");
		g->arr[g->RandomNums]=-1;
	}
	
	qsort(g->arr, g->RandomNums, sizeof(int), cmpfunc);


	if(g->oflag==0){
		int h=0;
		//printf("\n");
		//printf("%d\n",g->arr[10]);
		while(g->arr[h]!=-1){
			if(g->arr[h]>0){
				printf("%d\n",g->arr[h]);
			}			
			//printf("\t%d\n",h);
			h++;
		}
	}else if(g->oflag==1){
		int h=0;
		FILE *file = fopen(g->filename, "w+");
		if(file == NULL){
			fprintf(stderr, "Error opening file.\n");
			exit(1);
		}
		while(g->arr[h]!=-1){
			if(g->arr[h]>0){
				fprintf(file, "%d\n", g->arr[h]);
			}
			h++;
		}
		fclose(file);
		//free(file);
	}

	int userLength = strlen(envp[9])-5;
	int *carr;
	carr = (int*) calloc(userLength+1, sizeof(int));
	carr[userLength]=-1;
	

	if(g->cflag==0){
		//printf("%d\n", print);
		for(int i=0;i<g->RandomNums;i++){
			for(int j=0;j<userLength;j++){
				if((int)envp[9][j+5]==g->arr[i]){
					carr[j]+=1;
				}
			}
		}
		int k=0;
		while(carr[k]!=-1){
			printf("%c\t%d\t%d\n",envp[9][k+5],envp[9][k+5],carr[k]);
			k++;
		}
	}else if(g->cflag==1){
		FILE *file=fopen(g->cfile,"w+");
		for(int i=0;i<g->RandomNums;i++){
			for(int j=0;j<userLength;j++){
				if((int)envp[9][j+5]==g->arr[i]){
					carr[j]+=1;
				}
			}
		}
		int k=0;
		while(carr[k]!=-1){
			fprintf(file,"%c\t%d\t%d\n",envp[9][k+5],envp[9][k+5],carr[k]);
			k++;
		}
		fclose(file);
		//free(file);
	}
	
	end = clock();
	tElapsed = ((double)(end-start))/CLOCKS_PER_SEC;
	printf("Took ");
	printf("%f",tElapsed);
	printf(" seconds.\n");

	if(errno!=0){
		fprintf(stderr,"Error occured");
	}
		
	/*int h=0;
	while(g->arr[h]!=-1){
		printf("-%d\n",g->arr[h]);
		h++;
	}*/
	return 0;
}
