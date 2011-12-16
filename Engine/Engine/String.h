#include "System.h"

class String {
private:
	int length;
	char* data;
public:
	String();
	String(char* pcString);
	~String();
	int GetMemoryUsed() const;
	int GetDiskUsed() const;
	String& operator=(const String& rcString);
	bool operator==(const String& rcString) const;
	bool operator!=(const String& rcString) const;
	//operator unsigned int() const;
private:
};