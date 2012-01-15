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
using namespace std;

int main(int argc, char** argv) {
	TMatrix2<float> m0(4);

	m0.Orthonormalize();

	m0.ToString();

	getchar();
	return 0;
}