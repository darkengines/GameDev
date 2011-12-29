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

using namespace std;

int main(int argc, char** argv) {
	TMatrixN<float, 4> m0(0.0f);
	TMatrixN<float, 4> m1(5.0f);
	m0.Identity();
	m0.ToString();printf("\n");
	m1.ToString();

	m0*=m1;
	printf("\n");
	m0.ToString();

	getchar();
	return 0;
}