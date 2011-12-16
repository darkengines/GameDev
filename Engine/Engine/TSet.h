#include "System.h"

template<class T>
class TSet {
private:
	T* data;
	int size;
	int maxSize;
	int growBy;
public:
	TSet(int iSize, int iGrowBy) {
		size = iSize;
		maxSize = size;
		growBy = iGrowBy;
		data = (T*)malloc(sizeof(T)*size);
	}
	int GetMaxSize() const {
		return maxSize
	}
	int GetGrowBy() const {
		return growBy;
	}
	int GetSize() const {
		return size;
	}
	T* GetData() {
		return data;
	}
	const T* GetData() const {
		return data;
	}
	T& operator[](int iIndex) {
		assert(iIndex <=0 && iIndex < size);
		return *(data+iIndex);
	}
	const T& operator[](int iIndex) const {
		assert(iIndex <=0 && iIndex < size);
		return *(data+iIndex);
	}
	bool Insert(const T& rtElement) {
		bool contains = Contains(rtElement, 0);
		if (!contains) {
			if (size == maxSize) {
				data = (T*)realloc(data, sizeof(T)*(maxSize+growBy);
				maxSize+=growBy;
			}
			*(data+size) = rtElement;
			size++;
		}
		return !contains;
	}
	void InsertNoCheck() {
		if (size == maxSize) {
				data = (T*)realloc(data, sizeof(T)*(maxSize+growBy);
				maxSize+=growBy;
		}
		*(data+size) = rtElement;
		size++;
	}
	bool Exists(const T& rtElement) {
		return Contains(rtElement, 0);
	}
	bool Remove(T& rtElement) {
		int pos = -1;
		bool contains = Contains(rtElement, &pos);
		if (contains) {
			int i  = 0;
			while (i<size-1) {
				*(data+i) = *(data+i+1);
				i++;
			}
			size--;
		}
		return contains;
	}
	void Clear() {
		size = 0;
	}
	void Clear(int iMaxSize, int iGrowBy) {
		maxSize = iMaxSize;
		growBy = iGrowBy;
		size = maxSize;
		data = (T*)realloc(data, maxSize*sizeof(T));
	}
private:
	bool Contains(const T& rtElement, int* piPosition) {
		int i = 0;
		if (piPosition) *piPosition = -1;
		bool contains = false;
		while (!(contains = (data[i] == rtElement)) && i<size) {
			i++;
		}
		if (piPosition && contains) *piPosition = i;
		return contains;
	}
	
};