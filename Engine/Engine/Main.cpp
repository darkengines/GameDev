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
	TMatrix3<float> m0(4);

	m0[0][0] = 0.36;
	m0[0][1] = 0.48;
	m0[0][2] = -0.8;
	m0[1][0] = -0.8;
	m0[1][1] = 0.6;
	m0[1][2] = 0;
	m0[2][0] = 0.48;
	m0[2][1] = 0.64;
	m0[2][2] = 0.60;

	float angle;
	TVector3<float> axis;

	m0.ToAxisAngle(axis, angle);

	cout<<"Angle: "<<angle<<endl;
	cout<<"Axis: "<<axis.X()<<" "<<axis.Y()<<" "<<axis.Z()<<endl;

	getchar();
	return 0;
}