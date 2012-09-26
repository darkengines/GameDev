
#include "../Object.h"
class ObjectB: public Object {
private:
public:
	ObjectB(): Object() {

	}
	Object* GetObjectByName(const String& name) {
			return 0;
	}
	void GetObjectsByName(const String& name, TArray<Object*>& objects) {
		
	}
};