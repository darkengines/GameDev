#ifndef _TVector4_H_
#define _TVector4_H_
#pragma once

#include "TVector.h"
#include "TMatrix4.h"

template<class Real>
class TMatrix4;

template<class Real>
class TVector4: public TVector<Real, 4> {
private:
public:
	TVector4(): TVector() {

	}
	TVector4(const Real* prValues): TVector(prValues) {
	}
	Real& X() {
		return _values[0];
	}
	Real& Y() {
		return _values[1];
	}
	Real& Z() {
		return _values[2];
	}
	Real& W() {
		return _values[3];
	}
	TVector4& operator=(const TVector4& rTVector) {
		return static_cast<TVector4&>(TVector::operator=(rTVector));
	}
	TVector4 operator+(const TVector4& rTVector) const {
		return static_cast<TVector4&>(TVector::operator+(rTVector));
	}
	TVector4 operator-(const TVector4& rTVector) const {
		return static_cast<TVector4&>(TVector::operator-(rTVector));
	}
	Real operator*(const TVector4& rTVector) const {
		return TVector::operator*(rTVector);
	}
	TVector4 operator+(const Real& rrValue) {
		return static_cast<TVector4&>(TVector::operator+(rrValue));
	}
	TVector4 operator-(const Real& rrValue) {
		return static_cast<TVector4&>(TVector::operator-(rrValue));
	}
	TVector4 operator*(const Real& rrValue) {
		return static_cast<TVector4&>(TVector::operator*(rrValue));
	}
	TVector4 operator/(const Real& rrValue) {
		return static_cast<TVector4&>(TVector::operator/(rrValue));
	}
	TVector4 Normalized() {
		return static_cast<TVector4&>(TVector::Normalized());
	}
	TVector4 AddedScaledVector(const TVector& rtVector, const Real& rrScale) {
		return static_cast<TVector4&>(TVector::AddedScaledVector(rtVector, rrScale));
	}
	TVector4 Inverted() {
		return static_cast<TVector4&>(TVector::Inverted());
	}
private:
};
#endif