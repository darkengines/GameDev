#ifndef _OBJECTA_H_
#define _OBJECTA_H_

#include "../Object.h"
#include "ObjectB.h";
#include "../TPointer.h";

class ObjectA: public Object {
private:
public:
	ObjectA(): Object() {

	}
	Object* GetObjectByName(const String& name) {
			return 0;
	}
	void GetObjectsByName(const String& name, TArray<Object*>& objects) {
		
	}
	ObjBPt OB;
	static const Rtti Type;
	virtual const Rtti& GetType() const { return Type; }
};
const Rtti ObjectA::Type("ObjectA", &Object::Type);
typedef TPointer<ObjectA> ObjAPt;
#endif