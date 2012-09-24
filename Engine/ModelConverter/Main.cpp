////////////////////////////////////////////////////
// File name: Main.cpp
////////////////////////////////////////////////////

#include <stdio.h>
#include "ObjectModelConverter.h"

int main(int argc, char** argv) {
	ObjectModelConverter* mc = new ObjectModelConverter();
	mc->Convert("C:\\Users\\Quicksort\\Desktop\\test.obj", "test.mod");
	getchar();
	return 0;
}