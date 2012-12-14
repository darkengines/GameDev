#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Rtti.h"
#include "TArray.h"
#include "TList.h"
#include "THashTable.h"
#include "TPointer.h"

class Controller;

class Object {
private:
	String _name;
	static unsigned int _objectCount;
	int _references;
	TList<TPointer<Controller>>* _controllerList;
protected:
	unsigned int _id;
public:
	Object() {
		_id = getNextId();
		InUse.Insert(_id, this);
		_references = 0;
		_controllerList = new TList<TPointer<Controller>>();
	}
	Object(Object& from) {

	}
	~Object() {
		InUse.Remove(_id);
	}
	virtual const Rtti& GetType() const {
		return Type;
	}
	bool IsExactly(const Rtti& type) {
		return GetType().IsExactly(type);
	}
	bool IsDerived(const Rtti& type) {
		return GetType().IsDerived(type);
	}
	bool IsExactlyTypeOf(const Object* object) {
		return GetType().IsExactly(object->GetType());
	}
	bool IsDerivedTypeOf(const Object* object) {
		return GetType().IsDerived(object->GetType());
	}
	template<class T> T* StaticCast(Object* object) {
		return (T*)object;
	}
	template<class T> const T* StaticCast(const Object* object) {
		return (const T*)object;
	}
	template<class T> T* DynamicCast(Object* object) {
		return object && object->IsDerived(T::Type) ? (T*)object : 0;
	}
	template<class T> const T* DynamicCast(const Object* object) {
		return object && object->IsDerived(T::Type) ? (const T*)object : 0;
	}
	void SetName(const String& name) {
		_name = name;
	}
	const String& GetName() const {
		return _name;
	}
	unsigned int GetId() const {
		return _id;
	}
	void IncrementReferences() {
		_references++;	
	}
	void DecrementReferences() {
		if (--_references <= 0) {
			delete this;
		}
	}
	int GetReferences() const {
		return _references;
	}
	static THashTable<unsigned int, Object*> InUse;
	static void PrintInUse(FILE* file, const char* message) {
		fprintf(file, "%s:\n", message);
		unsigned int key = 0;
		Object* object = InUse.GetFirst(&key);
		while (object) {
			fprintf(file, "[id=%6u] [name=%32s]\n", object->_id, object->_name.GetString());
			object = InUse.GetNext(&key);
		}
	}
	virtual Object* GetObjectByName(const String& name) = 0;
	virtual void GetObjectsByName(const String& name, TArray<Object*>& objects) = 0;
	static const Rtti Type;

	void SetController(TPointer<Controller>& controller) {
		_controllerList->AppendHead(controller);
	}

	void RemoveController(Controller* controller) {
		_controllerList->Remove(controller);
	}
	void RemoveAllControllers() {
		_controllerList->Clear();
	}
private:
	static unsigned int getNextId() {
		return _objectCount++;
	}
};
const Rtti Object::Type("Object",0);
THashTable<unsigned int, Object*> Object::InUse = THashTable<unsigned int, Object*>(32, 0);
unsigned int Object::_objectCount = 0;

#include "Controller.h"

#endif