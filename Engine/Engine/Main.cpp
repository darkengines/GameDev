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
#include "Quaternion.h"
using namespace std;

int main(int argc, char** argv) {
	Quaternion<float> q0 = Quaternion<float>();
	q0[0] = 0;
	q0[1] = 1;
	q0[2] = 0;
	q0[3] = M_PI/2;

	Quaternion<float> q1 = Quaternion<float>();
	
	q1[0] = 1;
	q1[1] = 1;
	q1[2] = 1;
	q1[3] = M_PI/4;

	q0.Dot(q1);

	float i = 0.0f;
	while (i<1) {
		Quaternion<float> q = Quaternion<float>::Slerp(i, q0, q1);
		printf("[t=%3.4f] %3.4f %3.4f %3.4f %3.4f\n", i, q[0], q[1], q[2], q[3]);
		i+=0.0001;
	}

	q0.Slerp(0.2, q0, q1);

	getchar();
	return 0;
}