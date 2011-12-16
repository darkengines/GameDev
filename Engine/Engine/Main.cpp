#include "System.h"
#include "THashTable.h"
#include "TArray.h"
#include "THashSet.h"
#include "TList.h"
#include "String.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	String s("caca boudin");
	s = "merde";
	String b;
	b=s;
	b="pipi";
	cout<<System::GetTime()<<endl;
	getchar();
	return 0;
}