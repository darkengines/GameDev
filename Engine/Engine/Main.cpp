#include "System.h"
#include "THashTable.h"
#include "TArray.h"
#include "THashSet.h"
#include "TList.h"
#include "String.h"
#include <iostream>
#include "TVector2.h"

using namespace std;

int main(int argc, char** argv) {
	TVector2<float> v = TVector2<float>();
	v[0]=2;
	v[1]=1;
	cout<<v[0]<<","<<v[1]<<endl;
	TVector2<float> v1 = TVector2<float>();
	v1.X() = 10;
	v1.Y() = 15;
	float r = v.DotPerp(v1);
	cout<<r<<endl;
	getchar();
	return 0;
}