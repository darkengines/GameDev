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
	

	m0[0][0] = 4;
	m0[0][1] = -30;
	m0[0][2] = 60;
	m0[0][3] = -35;

	m0[1][0] = -30;
	m0[1][1] = 300;
	m0[1][2] = -675;
	m0[1][3] = 420;

	m0[2][0] = 60;
	m0[2][1] = -675;
	m0[2][2] = 1620;
	m0[2][3] = -1050;

	m0[3][0] = -35;
	m0[3][1] = 420;
	m0[3][2] = -1050;
	m0[3][3] = 700;

	TMatrixN<float, 4> EV;
	TVector<float, 4> Ev;

	cout<<FLT_EPSILON<<endl;
	
	m0.Jacobi(EV, Ev);

	EV.ToString();
	cout<<endl;
	cout<<Ev[0]<<";"<<Ev[1]<<";"<<Ev[2]<<";"<<Ev[3]<<endl;

	getchar();
	return 0;
}