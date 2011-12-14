#include "System.h"
#include "HashTable.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

	HashTable<int, int*>* t = new HashTable<int, int*>(10, 0);
	int k = 69;
	int v = 12345;
	t->Insert(k, &v);
	k = 79;
	t->Insert(k, &v);
	t->Remove(k);
	k = 69;
	int* f = *t->Find(k);
	
	int k1;
	int* v1;
	v1 = *t->GetFirst(&k1);
	cout<<k1<<" "<<*v1<<endl;
	v1 = *t->GetNext(&k1);
	cout<<k1<<" "<<*v1<<endl;
	getchar();
	return 0;
}