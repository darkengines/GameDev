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
#include "TLine.h"
using namespace std;

int main(int argc, char** argv) {
	TVector3<float> point;	
	point[0] = 0;
	point[1] = 0;
	point[2] = 0;

	TVector3<float> direction;
	direction[0] = 1;
	direction[1] = 1;
	direction[2] = 1;

	direction.Normalize();

	TVector3<float> anOtherPoint;
	anOtherPoint[0] = 10;
	anOtherPoint[1] = 5;
	anOtherPoint[2] = 7;

	TLine<float> line(point, direction);

	float distance = line.DistanceTo(anOtherPoint);

	printf("distance=%f\n", distance);

	getchar();
	return 0;
}