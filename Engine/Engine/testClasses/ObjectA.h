#include "../Object.h"

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
	static const Rtti Type;
	virtual const Rtti& GetType() const { return Type; }
};
const Rtti ObjectA::Type("ObjectA", &Object::Type);