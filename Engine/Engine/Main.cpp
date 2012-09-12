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
#include "TMatrix4.h"
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

	TMatrix4<float> proj = TMatrix4<float>();
	
	TVector3<float> n = TVector3<float>();
	TVector3<float> p = TVector3<float>();
	TVector3<float> d = TVector3<float>();

	n[0] = 0;
	n[1] = 1;
	n[2] = 0;

	p[0] = 0;
	p[1] = 1;
	p[2] = 0;

	d[0] = 0;
	d[1] = -1;
	d[2] = 0;

	proj.MakeObliqueProjection(n, p, d);
	proj.ToString();

	TVector4<float> v = TVector4<float>();
	v[0] = 0.0f;
	v[1] = 2.0f;
	v[2] = 0.0f;
	v[3] = 1.0f;

	v = proj*v;
	cout<<"projected: "<<v.X()<<", "<<v.Y()<<", "<<v.Z()<<", "<<v.W()<<endl;

	getchar();
	return 0;
}