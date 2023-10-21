#include <string>
#include <iostream>
#include <stdlib.h>
//#include <typeinfo>
//#include "llc.h"
//#include <cmath>
//#include <ctgmath>
#include "llc.h"

using namespace std;

LLC::LLC(){
  tailNode = NULL;
	headNode = NULL;
}

LLC::~LLC(){
	Node *current = headNode;
	while(current!=NULL){
		Node *next = current->next;
		delete current;
		current = next;
	}
}

/*template <class Type>
LLC<Type>::LLC(const LLC &obj){
	tailNode=NULL;
	headNode=NULL;
	Node<Type> *traverser = obj.headNode;
	while(traverser!=NULL){
		Type el = traverser->element;
		insert(el);
		traverser=traverser->next;
	}
}*/

bool LLC::insert(int data){
	bool tf=false;
	Node *temp= new Node();
	temp->element=data;
	if(tailNode==NULL){
		headNode=temp;
		tf=true;
	}else{
		tailNode->next=temp;
		tf=true;
	}
	tailNode=temp;
	return tf;
}

/*
template <class Type>
ostream & operator<<(ostream &out, const LLC<Type> &obj){
	Node *temp = obj.headNode;
	if(obj.headNode==NULL){
		out << "This list is empty!";
		return out;
	}
	out << "[";
	while(temp!=NULL){
		out << temp->element << ", ";
		temp = temp->next;
	}
	out << "]";
	return out;
}*/

int LLC::len(){
	Node *traverser = headNode;
	int size=0;
	while(traverser!=NULL){
		size++;
		traverser=traverser->next;
	}
	return size;
}
