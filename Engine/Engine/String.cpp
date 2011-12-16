#include "String.h"

String::String() {length = 0;data = 0;}

String::String(char* pcString) {
		length = strlen(pcString);
		data = pcString;
}
int String::GetMemoryUsed() const {
	return length;
}
int String::GetDiskUsed() const {
	return length+sizeof(length);
}
String& String::operator=(const String& rString) {
	String result = String();
	result.length = rString.length;
	result.data = (char*)malloc(rString.GetMemoryUsed());
	memcpy(result.data, rString.data, result.length);
	return result;
}
bool String::operator==(const String& rString) const {
	if (rString.length == length) {
		return !strcmp(data, rString.data);
	}
	return false;
}
bool String::operator!=(const String& rString) const {
	return !this->operator==(rString);
}
String::~String() {
	if (data) {
		free(data);
	}
}