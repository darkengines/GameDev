#include "System.h"
#include "THashTable.h"
#include "TArray.h"
#include "THashSet.h"
#include "TList.h"
#include "String.h"
#include <iostream>
#include "Vector2.h"

using namespace std;

int main(int argc, char** argv) {
	Vector2<int> v = Vector2<int>();
	v[0]=0;
	v[1]=1;
	cout<<v[0]<<","<<v[1]<<endl;
	Vector2<int> v1 = Vector2<int>();
	v1.X() = 10;
	v1.Y() = 15;
	v = v + v1;
	cout<<v[0]<<","<<v[1]<<endl;
	getchar();
	return 0;
}