#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "generator.c"

int main(int argc, char **argv, char *envp[]){

	struct generator g = {.RandomNums = 100, .maxNum = 255, .minNum = 1, .seed = 0, .uflag=0, .nflag=0, .mflag=0, .Mflag=0, .sflag=0, .oflag=0};

	run(g, argc, argv, envp);

	return 0;


}
