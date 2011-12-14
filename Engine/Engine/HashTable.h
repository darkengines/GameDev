#include "System.h"

template<class TKEY, class TVALUE>
class HashItem {
private:
	TKEY& key;
	TVALUE& value;
	HashItem* next;
public:
	HashItem(const TKEY& rtKey, const TVALUE& rtValue): key(rtKey), value(rtValue) {
		next = 0;
	}
	void SetKey(TKEY& rtKey) {
		key = rtKey;
	}
	void SetValue(TVALUE& rtValue) {
		value = rtValue;
	}
	void SetNext(HashItem* pkNext) {
		next = pkNext;
	}
	TKEY* GetKey()  {
		return key;
	}
	TVALUE* GetValue()  {
		return value;
	}
	HashItem* GetNext()  {
		return next;
	}
};

template<class TKEY, class TVALUE>
class HashTable {
private:
	HashItem<TKEY, TVALUE>** hashItems;
	HashItem<TKEY, TVALUE>* listIndex;
	int itemIndex;
	int size;
public:
	int (*UserHashFunction)(const TKEY&);
	HashTable(int iSize, int (*pfUserHashFunction)(const TKEY&)) {
		size = iSize;
		UserHashFunction = pfUserHashFunction;
		hashItems = (HashItem<TKEY, TVALUE>**)malloc(sizeof(HashItem<TKEY, TVALUE>*)*size);
		int i = 0;
		while (i<size) {
			hashItems[i]= 0;
			i++;
		}
	}
	
	bool Insert(const TKEY& rtKey, const TVALUE& rtValue) {
		HashItem<TKEY, TVALUE>* item = 0;
		int key = Hash(rtKey);
		item = hashItems[key];
		if (!item) {
			hashItems[key] = new HashItem<TKEY, TVALUE>(rtKey, rtValue);
			return true;
		} else {
			while (item->GetKey() != rtKey && item->GetNext()) {
				item = item->GetNext();
			}
			if (item->GetKey() != rtKey) {
				item->SetNext(new HashItem<TKEY, TVALUE>(rtKey, rtValue));
				return true;
			}
			return false;
		}
	}

	bool Remove(const TKEY& rtKey) {
		HashItem<TKEY, TVALUE>* item = 0;
		int key = Hash(rtKey);
		item = hashItems[key];
		if (!item) {
			return false;
		} else {
			HashItem<TKEY, TVALUE>* back = 0;
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

	TVALUE* Find(const TKEY& rtKey) {
		HashItem<TKEY, TVALUE>* item = 0;
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
			return found ? &item->GetValue() : 0;
		}
	}

	TVALUE* GetFirst(TKEY* ptKey) {
		itemIndex = 0;
		listIndex = 0;
		while (!hashItems[itemIndex] && itemIndex < size) {
			itemIndex++;
		}
		if (hashItems[itemIndex] && itemIndex < size) {
			listIndex = hashItems[itemIndex];
			*ptKey = listIndex->GetKey();
			return &listIndex->GetValue();
		} 
		*ptKey = 0;
		return 0;
	}

	TVALUE* GetNext(TKEY* ptKey) {
		if (listIndex) {
			if (listIndex->GetNext()) {
				listIndex = listIndex->GetNext();
				*ptKey = listIndex->GetKey();
				return listIndex->GetValue();
			}
			itemIndex++;
			while (!hashItems[itemIndex] && itemIndex < size) {
				itemIndex++;
			}
			if (hashItems[itemIndex] && itemIndex < size) {
				listIndex = hashItems[itemIndex];
				*ptKey = listIndex->GetKey();
				return listIndex->GetValue();
			} 
		}
		*ptKey = 0;
		return 0;
	}

private:
	int DefaultHashFunction(const TKEY& key) {
		return key % size;
	}
	int Hash(const TKEY& rtKey) {
		if (UserHashFunction) {
			return UserHashFunction(rtKey);
		} else {
			return DefaultHashFunction(rtKey);
		}
	}
};