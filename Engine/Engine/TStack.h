#ifndef _TSTACK_H_
#define _TSTACK_H_

#include "System.h"

template <class T>
class TStack {
private:
	int count;
	int size;
	T* data;
public:
	TStack(int iSize) {
		assert(iSize >= 0);
		size = iSize;
		data = (T*)malloc(sizeof(T)*size);
		count = 0;
	}
	bool IsEmpty() {
		return count == 0;
	}
	bool IsFull() {
		return count == size;
	}
	void Push(const T& rtItem) {
		*(data+count) = rtItem;
		count++;
	}
	void Pop(T& rtItem) {
		rtItem = *(data+count-1);
		count--;
	}
	void Clear() {
		count = 0;
	}
	bool GetTop(T& rtItem) const {
		if (!empty) {
			rtItem = *(data+count-1);
			return true;
		}
		return false;
	}
	int GetCount() const {
		return count;
	}
	const T* GetData() const {
		return data;
	}
private:
};

#endif