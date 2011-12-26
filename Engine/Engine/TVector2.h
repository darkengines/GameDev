#ifndef _TVECTOR2_H_
#define _TVECTOR2_H_

#include "System.h"
#include "TVector.h"

template<class Real>
class TVector2: public TVector<Real, 2> {
private:
public:
	TVector2(): TVector() {
	}
	TVector2(Real* prValues): TVector(prValues) {
	}
	Real& X() {
		return *(values);
	}
	Real& Y() {
		return *(values+1);
	}
	Real& operator[](int iIndex) {
		return (TVector<Real, 2>::operator[](iIndex));
	}
	// TVector x TVector operators
	bool operator==(const TVector2<Real>& rTVector) {
		return (TVector<Real, 2>::operator==(rTVector));
	}
	bool operator!=(const TVector2<Real>& rTVector) {
		return (TVector<Real, 2>::operator!=(rTVector));
	}
	bool operator>(const TVector2<Real>& rTVector) {
		return (TVector<Real, 2>::operator>(rTVector));
	}
	bool operator<(const TVector2<Real>& rTVector) {
		return (TVector<Real, 2>::operator<(rTVector));
	}
	bool operator>=(const TVector2<Real>& rTVector) {
		return (TVector<Real, 2>::operator>=(rTVector));
	}
	bool operator<=(const TVector2<Real>& rTVector) {
		return (TVector<Real, 2>::operator<=(rTVector));
	}
	TVector2& operator=(const TVector2<Real>& rTVector) {
		return (TVector2&)(TVector<Real, 2>::operator=(rTVector));
	}
	TVector2& operator+(TVector2<Real>& rTVector) const {
		return (TVector2<Real>&)(TVector<Real, 2>::operator+(rTVector));
	}
	TVector2 operator-(TVector2<Real>& rTVector) {
		return (TVector2)(TVector<Real, 2>::operator-(rTVector));
	}
	Real operator*(TVector2<Real>& rTVector) {
		return (TVector<Real, 2>::operator*(rTVector));
	}
	// TTVector x Real operators
	TVector2 operator+(const Real& rrValue) {
		return (TVector2)(TVector<Real, 2>::operator+(rrValue));
	}
	TVector2 operator-(const Real& rrValue) {
		return (TVector2)(TVector<Real, 2>::operator-(rrValue));
	}
	TVector2 operator*(const Real& rrValue) {
		return (TVector2)(TVector<Real, 2>::operator*(rrValue));
	}
	TVector2 operator/(const Real& rrValue) {
		return (TVector2)(TVector<Real, 2>::operator/(rrValue));
	}
private:
};

#endif