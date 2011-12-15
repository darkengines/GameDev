#include "System.h"
#include "THashTable.h"
#include "TArray.h"
#include "THashSet.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

	THashSet<int>* s = new THashSet<int>(10, 0);
	int i = 1;
	s->Insert(1);
	s->Insert(2);
	s->Insert(3);
	s->Insert(4);
	s->Insert(5);
	s->Insert(6);
	s->Insert(7);
	s->Insert(8);
	s->Insert(9);
	s->Insert(10);
	s->Insert(11);
	const int* k = s->GetFirst();
	cout<<*k<<endl;
	while (k=s->GetNext()) {
		cout<<*k<<endl;
	}
	getchar();
	return 0;
}