#ifndef _TMatrix4_H_
#define _TMatrix4_H_
#pragma once

#include "TMatrixN.h"
#include "TVector4.h"
#include "TVector3.h"
#define _USE_MATH_DEFINES
#include <math.h>

template<class Real>
class TVector4;

template<class Real>
class TMatrix4: public TMatrixN<Real, 4> {
public:
	TMatrix4(): TMatrixN() {

	}
	TMatrix4(Real* prValues, bool bRowMajor): TMatrixN(prValues, bRowMajor) {

	}
	TMatrix4(Real rValue): TMatrixN(rValue) {

	}
	TMatrix4(const TMatrix4& rtMatrix): TMatrixN(rtMatrix) {

	}
	TMatrix4& operator=(const TMatrix4& rtMatrix) {
		return static_cast<TMatrix4&>(TMatrixN::operator=(rtMatrix));
	}
	TMatrix4 operator+(const TMatrix4& rtMatrix) const {
		return static_cast<TMatrix4&>(TMatrixN::operator+(rtMatrix));
	}
	TMatrix4 operator-(const TMatrix4& rtMatrix) const {
		return static_cast<TMatrix4&>(TMatrixN::operator-(rtMatrix));
	}
	TMatrix4 operator*(const TMatrix4& rtMatrix) const {
		return static_cast<TMatrix4&>(TMatrixN::operator*(rtMatrix));
	}
	TMatrix4 operator+(const Real& rValue) const {
		return static_cast<TMatrix4&>(TMatrixN::operator+(rValue));
	}
	TMatrix4 operator-(const Real& rValue) const {
		return static_cast<TMatrix4&>(TMatrixN::operator-(rValue));
	}
	TMatrix4 operator*(const Real& rValue) const {
		return static_cast<TMatrix4&>(TMatrixN::operator*(rValue));
	}
	TMatrix4 operator/(const Real& rValue) const {
		return static_cast<TMatrix4&>(TMatrixN::operator/(rValue));
	}
	TVector4<Real> operator*(TVector4<Real>& rtVector) {
		return static_cast<TVector4<Real>&>(TMatrixN::operator*(rtVector));
	}
	TMatrix4 Inverted() {
		return static_cast<TMatrix4&>(TMatrixN::Inverted());
	}
	TMatrix4 Transposed() {
		return static_cast<TMatrix4&>(TMatrixN::Transposed());
	}
	TVector4<Real> Row(const unsigned int iIndex) {
		return static_cast<TVector4<Real>&>(TMatrixN::Row(iIndex));
	}
	TVector4<Real> Column(const unsigned int iIndex) {
		return static_cast<TVector4<Real>&>(TMatrixN::Column(iIndex));
	}
	void SetRow(const unsigned int iIndex, const TVector4<Real>& rtVector) {
		TMatrixN::SetRow(iIndex, rtVector);
	}
	void SetColumn(const unsigned int iIndex,const TVector4<Real>& rtVector) {
		TMatrixN::SetColumn(iIndex, static_cast<TVector<Real, 3>>(rtVector));
	}
	void MakeObliqueProjection(const TVector3<Real>& planarN, const TVector3<Real>& planarP, const TVector3<Real>& direction) {
		TMatrix3<Real> topLeft = TMatrix3<Real>();
		topLeft = planarN.TensorProduct(direction);
		TMatrix3<Real> identity = TMatrix3<Real>();
		identity.Identity();

		topLeft -= identity*(planarN*direction);

		TVector3<Real> topRight = TVector3<Real>();
		Real x = -(planarN*planarP);
		topRight.SetAll(0);

		topRight.AddScaledVector(direction, x);

		_values[0] = topLeft[0][0];
		_values[1] = topLeft[0][1];
		_values[2] = topLeft[0][2];
		_values[4] = topLeft[1][0];
		_values[5] = topLeft[1][1];
		_values[6] = topLeft[1][2];
		_values[8] = topLeft[2][0];
		_values[9] = topLeft[2][1];
		_values[10] = topLeft[2][2];

		_values[3] = topRight[0];
		_values[7] = topRight[1];
		_values[11] = topRight[2];

		_values[12] = 0;
		_values[13] = 0;
		_values[14] = 0;

		_values[15] = (planarN.Inverted())*direction;
	}
	void MakePerspectiveProjection(const TVector3<Real>& planarP,const  TVector3<Real>& planarN,const  TVector3<Real>& eye) {
		TMatrix3<Real> topLeft = TMatrix3<Real>();
		topLeft.Identity();
		topLeft *= (planarN*(eye-planarP));
		topLeft -= planarN.TensorProduct(eye);

		TVector3<Real> topRight = TVector3<Real>();
		topRight = topLeft*eye.Inverted();

		_values[0] = topLeft[0][0];
		_values[1] = topLeft[0][1];
		_values[2] = topLeft[0][2];
		_values[4] = topLeft[1][0];
		_values[5] = topLeft[1][1];
		_values[6] = topLeft[1][2];
		_values[8] = topLeft[2][0];
		_values[9] = topLeft[2][1];
		_values[10] = topLeft[2][2];

		_values[3] = topRight[0];
		_values[7] = topRight[1];
		_values[11] = topRight[2];

		_values[12] = -eye[0];
		_values[13] = -eye[1];
		_values[14] = -eye[2];

		_values[15] = (planarN*eye);

	}
	void MakeReflection(const TVector3<Real>& planarP, const TVector3<Real>& planarN) {
		TMatrix3<Real> topLeft = TMatrix3<Real>();
		topLeft.Identity();
		topLeft -= planarN.TensorProduct(planarN)*2;

		TVector3<Real> topRight = TVector3<Real>();
		topRight.SetAll((Real)0);
		topRight.AddScaledVector(planarN, (Real)2*(planarN*planarP));

		_values[0] = topLeft[0][0];
		_values[1] = topLeft[0][1];
		_values[2] = topLeft[0][2];
		_values[4] = topLeft[1][0];
		_values[5] = topLeft[1][1];
		_values[6] = topLeft[1][2];
		_values[8] = topLeft[2][0];
		_values[9] = topLeft[2][1];
		_values[10] = topLeft[2][2];

		_values[3] = topRight[0];
		_values[7] = topRight[1];
		_values[11] = topRight[2];

		_values[12] = 0;
		_values[13] = 0;
		_values[14] = 0;

		_values[15] = 1;
	}
};

#endif