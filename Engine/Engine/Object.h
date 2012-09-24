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
		bool IsExactly(const Rtti& type) {
			return Object::Type.IsExactly(type);
		}
		bool IsDerived(const Rtti& type) {
			return Object::Type.IsDerived(type);
		}
		bool IsExactlyTypeOf(const Object* object) {
			return Object::Type.IsExactly(object->Type);
		}
		bool IsDerivedTypeOf(const Object* object) {
			return Object::Type.IsDerived(object->Type);
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
};
const Rtti Object::Type = Rtti("Object",0);
#endif