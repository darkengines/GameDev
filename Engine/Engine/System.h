#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#define BIG_ENDIAN      0
#define LITTLE_ENDIAN   1

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cfloat>
#include <ctype.h>
#include <cmath>
#include <ctime>

#if defined(WIN32)
#include <Windows.h>
#endif

class System {
private:
public:
	static void SwapBytes(int iSize, void* pvData);
	static void SwapBytes(int iSize, int iQuantity, void* pvData);
	static void EndianCopy(int iSize, void* pvData);
	static void EndianCopy(int iSize, int iQuantity, void* pvData);
	static int TestByteOrder();

	static double GetTime();

	static bool Load(const char* pcFileName, char*& pcBuffer, int& riSize);
	static bool Save(const char* pcFileName, const char* pcBuffer, int iSize);
	static bool Append(const char* pcFileName, const char* pcBuffer, int iSize);
private:
};

#endif