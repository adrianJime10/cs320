struct processTree{

	int numLevels;
	int numChildren;
	int sleepTime;
	int opt;

	int uflag;
	int nflag;
	int mflag;
	int sflag;
	int pflag;

};

void run(struct processTree *g, int argc, char **argv, char *envp[]);
//int cmpfunc(const void *a, const void *b);
