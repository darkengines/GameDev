#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Rtti.h"

class Object {
	public:
		static const Rtti TYPE("Object", 0);
		virtual const Rtti& GetType() const {
			return TYPE;
		}
};

#endif