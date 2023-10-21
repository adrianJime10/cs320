struct sorter{

	int RandomNums;
	int maxNum;
	int minNum;
	int opt;
	char *filename;
	char *cfile;
	char *ifile;

	int iflag;
	int uflag;
	int nflag;
	int mflag;
	int Mflag;
	int oflag;
	int cflag;
	int *arr;

};

void run(struct sorter *g, int argc, char **argv, char *envp[]);
//int cmpfunc(const void *a, const void *b);
