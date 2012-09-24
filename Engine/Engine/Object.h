#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Rtti.h"
class Object {
private:
	static const Rtti Type;
public:
		virtual const Rtti& GetType() const {
			return Object::Type;
		}
};
const Rtti Object::Type = Rtti("Object",0);
#endif