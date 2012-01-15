////////////////////////////////////////////////////
// File name: Main.cpp
////////////////////////////////////////////////////

#include <stdio.h>
#include "ObjectModelConverter.h"

int main(int argc, char** argv) {
	ObjectModelConverter* mc = new ObjectModelConverter();
	mc->Convert("dragon.obj", "dragon.mod");
	getchar();
	return 0;
}