#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "System.h"

template<class Real, int Size>
class Vector {
protected:
	Real* values;
public:
	Vector() {
		values = (Real*)malloc(sizeof(Real)*Size);
	}
	Real& operator[](int iIndex) {
		return *(values+iIndex);
	}
	Vector& operator=(const Vector<Real, Size>& rVector) {
		int i = 0;
		while (i<Size) {
			*(values+i) = *(rVector.values+i);
			i++;
		}
		return *this;
	}
	Vector& operator+(Vector<Real, Size>& rVector) {
		int i = 0;
		while (i<Size) {
			*(values+i) += *(rVector.values+i);
			i++;
		}
		return *this;
	}
private:
};

#endif