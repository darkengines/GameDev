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

using namespace std;

int main(int argc, char** argv) {
	
	TColorRGB<float> color(0.5,0.5,50);
	color.ScaleByMax();

	cout<<"r="<<color.R()<<" g="<<color.G()<<" b="<<color.B()<<endl;


	getchar();
	return 0;
}