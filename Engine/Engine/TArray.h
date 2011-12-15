#include "System.h"

template <class T>
class TArray {
private:
	int maxSize;
	int size;
	int growBy;
	T* data;
public:
	TArray(int iSize, int iGrowBy) {
		assert(iSize >= 0 && iGrowBy >= 0);
		size = iSize;
		maxSize = size;
		growBy = iGrowBy;
		data = (T*)malloc(sizeof(T)*size);
	}
	~TArray() {
		free(data);
	}
	const T& operator[](int iIndex) const {
		assert(iIndex >=0 && iIndex < size);
		return *(data+iIndex);
	}
	T& operator[](int iIndex) {
		assert(iIndex >=0 && iIndex < size);
		return *(data+iIndex);
	}
	const T* GetData() const {
		return data;
	}
	T* GetData() {
		return data;
	}
	void Append(const T& rtValue) {
		if (size == maxSize) {
			data = (T*)realloc(data, sizeof(T)*(maxSize+growBy));
			maxSize++;
		}
		*(data+size) = rtValue;
		size++;
	}
	void Insert(const T& rtValue, int iIndex) {
		assert(iIndex >= 0);
		if (iIndex >= maxSize) {
			int newSize = iIndex+1;
			data = (T*)realloc(data, sizeof(T)*(newSize+1));
			maxSize = newSize;
			*(data+iIndex) = rtValue;
			size = maxSize;
		} else {
			*(data+iIndex) = rtValue;
		}
	}
	void Remove(int iIndex) {
		assert(iIndex >= 0 && iIndex < size);
		int i = iIndex+1;
		while (i<size) {
			*(data+i-1) = *(data+i);
			i++;
		}
		size--;
	}
	void RemoveAll() {
		size = 0;
	}
	int GetSize() {
		return size;
	}
	int GetMaxSize() {
		return maxSize;
	}
	void SetMaxSize(int iMaxSize) {
		assert(iMaxSize >= 0);
		if (iMaxSize != maxSize) {
			data = (T*)realloc(data, sizeof(T)*(iMaxSize));
			maxSize = iMaxSize;
		}
	}
private:
};