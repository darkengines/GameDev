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
#include "TPointer.h"
#include "testClasses\ObjectA.h"
#include "testClasses\ObjectB.h"

using namespace std;

int main(int argc, char** argv) {
	
	ObjAPt oa(new ObjectA());
	ObjBPt ob(new ObjectB());
	oa->OB = ob;
	oa->SetName("objectA");
	ob->SetName("objectB");

	ObjectA::PrintInUse(stdout, "test");
	bool t = oa->IsExactlyTypeOf(ob);
	oa->OB = 0;
	ob = 0;
	ObjectA::PrintInUse(stdout, "test");
	getchar();
	return 0;
}