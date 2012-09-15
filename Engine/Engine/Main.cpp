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
	
	Quaternion<float> q1 = Quaternion<float>();
	
	q0.Dot(q1);
	q0.Slerp(0.2, q0, q1);

	getchar();
	return 0;
}