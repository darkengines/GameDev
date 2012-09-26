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
#include "TColorRGB.h"
#include "Object.h"
#include "testClasses\ObjectA.h"
#include "testClasses\ObjectB.h"

using namespace std;

int main(int argc, char** argv) {
	
	ObjectA* oa = new ObjectA();
	ObjectB* ob = new ObjectB();
	oa->SetName("objectA");
	ob->SetName("objectB");

	ObjectA::PrintInUse("test", "test");

	getchar();
	return 0;
}