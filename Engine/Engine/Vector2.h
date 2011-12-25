#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include "System.h"
#include "Vector.h"

template<class Real>
class Vector2: public Vector<Real, 2> {
private:
public:
	Vector2(): Vector() {
	}
	Real& X() {
		return *(values);
	}
	Real& Y() {
		return *(values+1);
	}
	Vector2& operator=(const Vector2<Real>& rVector) {
		int i = 0;
		while (i<2) {
			*(values+i) = *(rVector.values+i);
			i++;
		}
		return *this;
	}
	Vector2& operator+(Vector2<Real>& rVector) {
		int i = 0;
		while (i<2) {
			*(values+i) += *(rVector.values+i);
			i++;
		}
		return *this;
	}
private:
};

#endif