#include <iostream>
#include "node.h"
#include <string>

using namespace std;

class LLC{
	public:
	LLC();
	//LLC(const LLC &copy);

	bool contains(int check);

 	bool insert(int data);

	int len();

	~LLC();

	Node *headNode;
	Node *tailNode;

	private:

};

