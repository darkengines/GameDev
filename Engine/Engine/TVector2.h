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
	Real operator*(const TVector2& rTVector) const {
		return TVector::operator*(rTVector);
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
	TVector2 AddedScaledVector(const TVector& rtVector, const Real& rrScale) {
		return static_cast<TVector2&>(TVector::AddedScaledVector(rtVector, rrScale));
	}
	TVector2 Inverted() {
		return static_cast<TVector2&>(TVector::Inverted());
	}
	void Perp() {
		Real temp = _values[0];
		_values[0] = _values[1];
		_values[1] = -temp;
	}
	TVector2 Perped() const {
		TVector2 result(_values);
		result.Perp();
		return result;
	}
	void UnitPerp() {
		Perp();
		Normalize();
	}
	TVector2 UnitPerped() const {
		TVector2 result = Perped();
		result.Normalize();
		return result;
	}
	Real DotPerp(const TVector2& rtVector) {
		return *this*rtVector.Perped();
	}
	static void Orthonormalize(TVector2& rtVector1, TVector2& rtVector2) {
		rtVector1.Normalize();
		rtVector2 -= rtVector1*(rtVector1*rtVector2);
		rtVector2.Normalize();
	}
	static void GenerateOrthonormalBasis(TVector2& rtVectorU, TVector2& rtVectorV, bool bUIsNormalized) {
		if (!bUIsNormalized) {
			rtVectorU.Normalize();
		}
		rtVectorV = rtVectorU.Perped();
	}
private:
};

#endif