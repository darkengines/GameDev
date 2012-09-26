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
};