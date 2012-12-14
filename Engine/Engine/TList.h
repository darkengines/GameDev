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
	TListItem(const T& rtItem, TListItem* pkNext) {
		item = &rtItem;
		next = pkNext;
	}
	TListItem(const TListItem<T>& from) {
		item = from.GetItem();
		next = from.GetNext();
	}
	~TListItem() {

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
		TListItem<T>* current = from.Head();
		TListItem<T>* previousCpy = 0;
		while (current) {
			if (previousCpy) {
				previousCpy->SetNext(new TListItem<T>(*current));
				previousCpy = previousCpy->GetNext();
			} else {
				_head = new TListItem(*current);
				previousCpy = _head;
			}
			current = current->GetNext();
		}
	}
	~TList() {

	}
	void AppendHead(const T& rtItem) {
		TListItem<T>* item = new TListItem<T>(rtItem, 0);
		if (_head) {
			item->SetNext(_head);
		} else {
			_head = item;
		}
		_length++;
	}
	void AppendTail(const T& rtItem) {
		TListItem<T>* item = new TListItem<T>(rtItem, 0);
		TListItem<T>* tail = Tail();
		if (tail) {
			tail->SetNext(item);
		} else {
			_head = item;
		}
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
		TListItem<T>* current = _head;
		TListItem<T>* previous = 0;
		bool found = 0;
		while (!found && current) {
			found = &current->GetItem() == &item;
			if (!found) {
				previous = current;
				current = current->GetNext();
			}
		}
		if (found) {
			if (previous) {
				previous->SetNext(current->GetNext());
			} else {
				_head = current->GetNext();
			}
			delete current;
		}
	}
	void Clear() {
		TListItem<T>* current = _head;
		while (current) {
			TListItem<T>* tmp = current;
			current = current->GetNext();
			delete tmp;
		}
		_head = 0;
	}
	void Insert(const T& item, const T& previous) {

	}

	const T& GetFirst() {
		_cursor = _head;
		return _cursor->GetItem();
	}
	const T& GetNext() {
		_cursor = _cursor->GetNext();
		if (_cursor) {
			return _cursor->GetItem();
		} else {
			return 0;
		}
	}
private:
	TListItem<T>* _cursor;
	TListItem<T>* _head;
	unsigned int _length;
};

#endif