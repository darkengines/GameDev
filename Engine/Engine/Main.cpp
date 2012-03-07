#include "System.h"
#include "THashTable.h"
#include "TArray.h"
#include "THashSet.h"
#include "TList.h"
#include "String.h"
#include <iostream>
#include "TVector2.h"
#include "TVector3.h"
#include "TMatrixN.h"
#include "TMatrix2.h"
#include "TMatrix3.h"
using namespace std;

int main(int argc, char** argv) {
	TMatrix3<float> m0(0);
	m0.Identity();

	TVector3<float> a;
	a.X() = 1;
	a.Y() = 0;
	a.Z() = 0;
	float an;
	an = -M_PI/6;
	float angle;
	TVector3<float> axis;
	m0.FromAxisAngle(a, an);
	m0.ToAxisAngle(axis, angle);

	cout<<"Angle: "<<angle<<endl;
	cout<<"Axis: "<<axis.X()<<" "<<axis.Y()<<" "<<axis.Z()<<endl;

	getchar();
	return 0;
}