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

	m0.FromEulerAngles(-M_PI/6, 0, 0);
	TVector3<float> axis;
	float angle;
	m0.ToAxisAngle(axis, angle);

	cout<<"Angle: "<<angle<<endl;
	cout<<"Axis: "<<axis.X()<<" "<<axis.Y()<<" "<<axis.Z()<<endl;

	float x, y, z;
	m0.ToEulerAnglesXYZ(x, y, z);
	cout<<"EulerXYZ: "<<x<<", "<<y<<", "<<z<<endl;

	getchar();
	return 0;
}