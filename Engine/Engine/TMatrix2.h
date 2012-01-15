#ifndef _TMATRIX2_H_
#define _TMATRIX2_H_

#include "TMatrixN.h"
#include "TVector2.h"

template<class Real>
class TMatrix2: TMatrixN<Real, 2> {
public:
	TMatrix2(): TMatrixN() {

	}
	TMatrix2(Real* prValues, bool bRowMajor): TMatrixN(prValues, bRowMajor) {

	}
	TMatrix2(Real rValue): TMatrixN(rValue) {

	}
	TMatrix2(const TMatrix2& rtMatrix): TMatrixN(rtMatrix) {

	}
	TMatrix2& operator=(const TMatrix2& rtMatrix) {
		return static_cast<TMatrix2&>(TMatrixN::operator=(rtMatrix));
	}
	TMatrix2 operator+(const TMatrix2& rtMatrix) const {
		return static_cast<TMatrix2&>(TMatrixN::operator+(rtMatrix));
	}
	TMatrix2 operator-(const TMatrix2& rtMatrix) const {
		return static_cast<TMatrix2&>(TMatrixN::operator-(rtMatrix));
	}
	TMatrix2 operator*(const TMatrix2& rtMatrix) const {
		return static_cast<TMatrix2&>(TMatrixN::operator*(rtMatrix));
	}
	TMatrix2 operator+(const Real& rValue) const {
		return static_cast<TMatrix2&>(TMatrixN::operator+(rValue));
	}
	TMatrix2 operator-(const Real& rValue) const {
		return static_cast<TMatrix2&>(TMatrixN::operator-(rValue));
	}
	TMatrix2 operator*(const Real& rValue) const {
		return static_cast<TMatrix2&>(TMatrixN::operator*(rValue));
	}
	TMatrix2 operator/(const Real& rValue) const {
		return static_cast<TMatrix2&>(TMatrixN::operator/(rValue));
	}
	TVector2<Real> operator*(TVector2<Real>& rtVector) {
		return static_cast<TVector2<Real>&>(TMatrixN::operator*(rtVector));
	}
	TMatrix2 Inverted() {
		return static_cast<TMatrix2&>(TMatrixN::Inverted());
	}
	TMatrix2 Transposed() {
		return static_cast<TMatrix2&>(TMatrixN::Transposed());
	}
	TVector2<Real> Row() {
		return static_cast<TVector2<Real>&>(TMatrixN::Row());
	}
	TVector2<Real> Column() {
		return static_cast<TVector2<Real>&>(TMatrixN::Column());
	}
	void SetRow(TVector2<Real>& rtVector) {
		TMatrixN::SetRow(rtVector);
	}
};

#endif