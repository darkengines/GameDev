#ifndef _TLIST_H_
#define _TLIST_H_

#include "System.h"

template<class T>
class TListItem {
private:
	const T* item;
	TListItem* next;
public:
	TListItem() {}
	TListItem(const T* rtItem, TListItem* pkNext) {
		item = rtItem;
		next = pkNext;
	}
	~TListItem() {
		delete item;
	}
	void SetItem(const T& rtItem) {
		item = &rtItem;
	}
	void SetNext(TListItem* pkNext) {
		next = pkNext;
	}
	const T& GetItem() const {
		return *item;
	}
	TListItem* GetNext() const {
		return next;
	}
	TListItem* Next() const {
		return next;
	}
	int Length() {
		int i = 0;
		TListItem<T>* e = this;
		while (e) {
			i++;
			e = e->Next();
		}
		return i;
	}

private:
};

template<class T> class TList {
private:

public:
	TList() {
		_head = 0;
		_cursor = 0;
		_length = 0;
	}
	TList(const TList& from) {

	}
	~TList() {

	}
	void AppendHead(const T& item) {
		TListItem<T>* item = new TListItem<T>(rtItem, 0);
		if (_head) {
			item->SetNext(_head);
		}
		_head = item;
	}
	void AppendTail(const T& item) {
		TListItem<T>* item = new TListItem<T>(rtItem, 0);

	}
	TListItem<T>* Tail() {
		TListItem<T>* current = _head;
		while (current->GetNext()) {
			current = current->GetNext();
		}
		return current;
	}
	TListItem<T>* Head() {
		return _head;
	}
	void Remove(const T& item) {

	}

	void Insert(const T& item, const T& previous) {

	}

	const T& GetFirst() {
		_cursor = _head;
		return _cursor->GetItem();
	}
private:
	TListItem<T>* _cursor;
	TListItem<T>* _head;
	unsigned int _length;
};

#endif