#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Object.h"

class Controller: public Object {
public:
	Controller(): Object() {

	}
	Controller(Controller& from): Object(from) {

	}

	static const Rtti Type;
	virtual const Rtti& GetType() const { return Type; }
	Object* GetObjectByName(const String& name) {
			return 0;
	}
	void GetObjectsByName(const String& name, TArray<Object*>& objects) {
		
	}
};
const Rtti Controller::Type("Controller", &Object::Type);
typedef TPointer<Controller> ControllerPointer;

#endif