struct generator{

	int RandomNums;
	int maxNum;
	int minNum;
	unsigned long seed;
	int opt;
	char *filename;
	int uflag;
	int nflag;
	int mflag;
	int Mflag;
	int sflag;
	int oflag;

};

void run(struct generator g, int argc, char **argv, char *envp[]);
