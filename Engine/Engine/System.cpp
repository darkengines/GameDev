#include "System.h"

void System::SwapBytes(int iSize, void* pvData) {
	int i = 0;
	int l = iSize/2;
	char tmp;
	while (i<l) {
		tmp = ((char*)pvData)[i];
		((char*)pvData)[i] = ((char*)pvData)[iSize-i];
		((char*)pvData)[iSize-i] = tmp;
		i++;
	}
}

void System::SwapBytes(int iSize, int iQuantity, void* pvData) {
	assert(iSize % iQuantity == 0);
	int i = 0;
	int offset = iSize/iQuantity;
	while (i<iSize) {
		SwapBytes(offset, (char*)pvData+i);
		i+=offset;
	}
}

void System::EndianCopy(int iSize, void* pvData) {
	if (TestByteOrder() == BIG_ENDIAN) SwapBytes(iSize, (char*)pvData);
}

void System::EndianCopy(int iSize, int iQuantity, void* pvData) {
	if (TestByteOrder() == BIG_ENDIAN) SwapBytes(iSize, iQuantity, (char*)pvData);
}

int System::TestByteOrder()
{
   short int word = 0x0001;
   char *byte = (char *) &word;
   return(byte[0] ? LITTLE_ENDIAN : BIG_ENDIAN);
}

double System::GetTime() {
#if defined(WIN32)
	LARGE_INTEGER frequency, count;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&count);
	return count.QuadPart/frequency.QuadPart;
#endif
}

bool System::Load(const char* pcFileName, char*& rpcBuffer, int& iSize) {
	FILE* file = 0;
	file = fopen(pcFileName, "rb");
	if (!file) return false;
	int result = 0;
	fseek(file, 0, SEEK_END);
	iSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	rpcBuffer = (char*)malloc(iSize);
	result = fread(rpcBuffer, 1, iSize, file);
	fclose(file);
	EndianCopy(iSize, rpcBuffer);
	return result == iSize;
}

bool System::Save(const char* pcFileName, const char* pcBuffer, int iSize) {
	FILE* file = 0;
	file = fopen(pcFileName, "wb");
	if (!file) return false;
	int result;
	result = fwrite(pcBuffer, 1, iSize, file);
	fclose(file);
	return result == iSize;
}

bool System::Append(const char* pcFileName, const char* pcBuffer, int iSize) {
	FILE* file = 0;
	fopen(pcFileName, "wb");
	if (!file) return false;
	int result = 0;
	fseek(file, 0, SEEK_END);
	result = fwrite(pcBuffer, 1, iSize, file);
	return result == iSize;
}