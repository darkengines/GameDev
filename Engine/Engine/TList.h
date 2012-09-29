#ifndef _TLIST_H_
#define _TLIST_H_

#include "System.h"

template<class T>
class TList {
private:
	const T* item;
	TList* next;
public:
	TList() {}
	TList(const T& rtItem, TList* pkNext): item(&rtItem), next(pkNext) {
		
	}
	void SetItem(const T& rtItem) {
		item = &rtItem;
	}
	void SetNext(TList* pkNext) {
		next = pkNext;
	}
	const T& GetItem() const {
		return *item;
	}
	TList* GetNext() const {
		return next;
	}
	TList* Next() const {
		return next;
	}
	int GetQuantity() {
		int i = 0;
		TList<T>* e = this;
		while (e) {
			i++;
			e = e->Next();
		}
		return i;
	}
private:
};

#endif