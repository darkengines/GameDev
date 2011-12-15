#include "System.h"
#include "THashTable.h"
#include "TArray.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

	TArray<int> a(128, 1);

	int i = 0;
	while (i<a.GetSize()) {
		a[i] = i;
		i++;
	}
	i = 28;
	while (i<a.GetSize()) {
		a.Remove(i);
	}
	i = 28;
	while (i<256) {
		a.Append(i);
		i++;
	}
	a.Insert(512, 512);
	i = 0;
	while (i<a.GetSize()) {
		cout<<a[i]<<endl;
		i++;
	}
	cout<<a.GetSize()<<endl;
	cout<<a.GetMaxSize()<<endl;

	getchar();
	return 0;
}