#include "System.h"
#include "THashTable.h"
#include "TArray.h"
#include "THashSet.h"
#include "TList.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	TList<int> l[50];
	for (int i=0;i<50;i++) {
		l[i].SetItem(i);
		l[i].SetNext(&l[(i+1)%50]);
	}
	cout<<l->GetQuantity()<<endl;
	getchar();
	return 0;
}