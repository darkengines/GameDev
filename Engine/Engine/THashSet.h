#include "System.h"

template<class TKEY>
class THashSetItem {
private:
	const TKEY& key;
	THashSetItem* next;
public:
	THashSetItem(const TKEY& rtKey): key(rtKey) {
		next = 0;
	}
	~THashSetItem() {
	}
	void SetKey(const TKEY& rtKey) {
		key = rtKey;
	}
	void SetNext(THashSetItem* pkNext) {
		next = pkNext;
	}
	const TKEY& GetKey() const  {
		return key;
	}
	THashSetItem* GetNext()  {
		return next;
	}
};

template<class TKEY>
class THashSet {
private:
	THashSetItem<TKEY>** hashItems;
	THashSetItem<TKEY>* listIndex;
	int itemIndex;
	int size;
public:
	int (*UserHashFunction)(const TKEY&);
	THashSet(int iSize, int (*pfUserHashFunction)(const TKEY&)) {
		size = iSize;
		UserHashFunction = pfUserHashFunction;
		hashItems = (THashSetItem<TKEY>**)malloc(sizeof(THashSetItem<TKEY>*)*size);
		int i = 0;
		while (i<size) {
			hashItems[i]= 0;
			i++;
		}
	}
	~THashSet() {
		int i = 0;
		THashSetItem<TKEY>* item = 0;
		THashSetItem<TKEY>* temp = 0;
		while (i<size) {
			if ((item = hashItems[i]) != 0) {
				while (item) {
					temp = item->GetNext();
					delete item;
					item = temp;
				}
			}			
			i++;
		}
	}
	const TKEY* Insert(const TKEY& rtKey) const {
		THashSetItem<TKEY>* item = 0;
		int key = Hash(rtKey);
		item = hashItems[key];
		if (!item) {
			hashItems[key] = new THashSetItem<TKEY>(rtKey);
			return &hashItems[key]->GetKey();
		} else {
			while (item->GetKey() != rtKey && item->GetNext()) {
				item = item->GetNext();
			}
			if (item->GetKey() != rtKey) {
				item->SetNext(new THashSetItem<TKEY>(rtKey));
				return &hashItems[key]->GetKey();
			}
			return 0;
		}
	}

	bool Remove(const TKEY& rtKey) {
		THashSetItem<TKEY>* item = 0;
		int key = Hash(rtKey);
		item = hashItems[key];
		if (!item) {
			return false;
		} else {
			THashSetItem<TKEY>* back = 0;
			while (item->GetKey() != rtKey && item->GetNext()) {
				back = item;
				item = item->GetNext();
			}
			if (item->GetKey() == rtKey) {
				if (back) {
					back->SetNext(item->GetNext());
				} else {
					hashItems[key] = item->GetNext();
				}
				delete item;
				return true;
			}
			return false;
		}
	}

	const TKEY* Get(const TKEY& rtKey) const {
		THashSetItem<TKEY>* item = 0;
		int key = Hash(rtKey);
		item = hashItems[key];
		if (!item) {
			return 0;
		} else {
			bool found = item->GetKey() == rtKey;
			while (!found && item->GetNext()) {
				item = item->GetNext();
				found = item->GetKey() == rtKey;
			}
			return found ? &item->GetKey() : 0;
		}
	}

	const TKEY* GetFirst() {
		itemIndex = 0;
		listIndex = 0;
		while (!hashItems[itemIndex] && itemIndex < size) {
			itemIndex++;
		}
		if (hashItems[itemIndex] && itemIndex < size) {
			listIndex = hashItems[itemIndex];
			return &listIndex->GetKey();
		} 
		return 0;
	}

	const TKEY* GetNext() {
		if (listIndex) {
			if (listIndex->GetNext()) {
				listIndex = listIndex->GetNext();
				return &listIndex->GetKey();
			}
			itemIndex++;
			while (!hashItems[itemIndex] && itemIndex < size) {
				itemIndex++;
			}
			if (hashItems[itemIndex] && itemIndex < size) {
				listIndex = hashItems[itemIndex];
				return &listIndex->GetKey();
			} 
		}
		return 0;
	}

private:
	int DefaultHashFunction(const TKEY& key) const {
		return key % size;
	}
	int Hash(const TKEY& rtKey) const {
		if (UserHashFunction) {
			return UserHashFunction(rtKey);
		} else {
			return DefaultHashFunction(rtKey);
		}
	}
};