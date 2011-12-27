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
	TVector2(const Real* prValues): TVector(prValues) {
	}
	Real& X() {
		return _values[0];
	}
	Real& Y() {
		return _values[1];
	}
	TVector2& operator=(const TVector2& rTVector) {
		return static_cast<TVector2&>(TVector::operator=(rTVector));
	}
	TVector2 operator+(const TVector2& rTVector) const {
		return static_cast<TVector2&>(TVector::operator+(rTVector));
	}
	TVector2 operator-(const TVector2& rTVector) const {
		return static_cast<TVector2&>(TVector::operator-(rTVector));
	}
	TVector2 operator+(const Real& rrValue) {
		return static_cast<TVector2&>(TVector::operator+(rrValue));
	}
	TVector2 operator-(const Real& rrValue) {
		return static_cast<TVector2&>(TVector::operator-(rrValue));
	}
	TVector2 operator*(const Real& rrValue) {
		return static_cast<TVector2&>(TVector::operator*(rrValue));
	}
	TVector2 operator/(const Real& rrValue) {
		return static_cast<TVector2&>(TVector::operator/(rrValue));
	}
	TVector2 Normalized() {
		return static_cast<TVector2&>(TVector::Normalized());
	}
private:
};

#endif