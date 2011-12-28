#include "System.h"
#include "THashTable.h"
#include "TArray.h"
#include "THashSet.h"
#include "TList.h"
#include "String.h"
#include <iostream>
#include "TVector2.h"
#include "TVector3.h"

using namespace std;

int main(int argc, char** argv) {
	TVector3<float> v0 = TVector3<float>();
	v0[0]=1;
	v0[1]=2;
	v0[2]=3;
	cout<<v0[0]<<","<<v0[1]<<endl;
	TVector3<float> v1 = TVector3<float>();
	v1.X() = 10;
	v1.Y() = 15;
	v1.Z() = 20;
	TVector3<float> v2 = TVector3<float>();
	v1.X() = 16;
	v1.Y() = 187;
	v1.Z() = 23;
	TVector3<float>::Orthonormalize(v0, v1, v2);
	cout<<"v1 "<<v0[0]<<","<<v0[1]<<","<<v0[2]<<endl;
	cout<<"v2 "<<v1[0]<<","<<v1[1]<<","<<v1[2]<<endl;
	cout<<"v2 "<<v1[0]<<","<<v1[1]<<","<<v2[2]<<endl;
	cout<<"v0 x v1 ="<<v0*v1<<endl;
	cout<<"v0 x v2 ="<<v0*v2<<endl;
	cout<<"v1 x v2 ="<<v1*v2<<endl;
	getchar();
	return 0;
}