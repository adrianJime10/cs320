#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "processTree.c"

int main(int argc, char **argv, char *envp[]) {

	struct processTree *g;
	g=(struct processTree*)malloc(sizeof(struct processTree));

	g->numLevels=1;
	g->numChildren=1;
	g->sleepTime=1;

	run(g, argc, argv, envp);

	pid_t pid; /* for a child process */
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), "-N %d", g->numLevels-1);
	char buffer2[1024];
	snprintf(buffer2, sizeof(buffer2), "-M %d", g->numChildren);
	char buffer3[1024];
	snprintf(buffer3, sizeof(buffer3), "-s %d", g->sleepTime);
	//printf("hi\n");
	//printf(buffer);
	printf("Alive: Level %d process with pid=%d, child of ppid=%d\n", g->numLevels, getpid(), getppid());

	if(g->numLevels==1){
		if(g->pflag==1){
			pause();
		}else{
			sleep(g->sleepTime);
		}
	}

	if(g->numLevels>1){
		for(int i=0;i<g->numChildren;i++){
			pid = fork();
			if(pid==0){
				break;
			}
		}	
	}
	//for(int i=g->numLevels;i>0;i--){
		if (pid < 0) { /* error */
			fprintf(stderr, "Fork failed.");
			return 1;
		}
		if (pid == 0) { /* child process */
			//printf("Level %d process with pid=%d, child of ppid=%d\n", g->numLevels-1, getpid(), getppid());
			if(g->pflag==0){
				char *args[]={"./prog2tree", buffer, buffer2, buffer3, NULL};
				execv(args[0], args);
				//wait(NULL);
			}else{
				char *args[]={"./prog2tree", buffer, buffer2, "-p", NULL};
				execv(args[0], args);
				//wait(NULL);
				//pause();
			}
		//wait(NULL);
		}else { /* parent process */
				/* parent will wait for the child to complete */
			wait(NULL);
			wait(NULL);
			wait(NULL);
			//printf("Child Complete.\n");
			printf("Exiting: Level %d process with pid=%d, child of ppid=%d\n", g->numLevels, getpid(), getppid());
		}
	//}
	return 0;
}
