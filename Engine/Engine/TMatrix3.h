#ifndef _TMATRIX3_H_
#define _TMATRIX3_H_
#pragma once

#include "TMatrixN.h"
#include "TVector3.h"
#define _USE_MATH_DEFINES
#include <math.h>

template<class Real>
class TVector3;

template<class Real>
class TMatrix3: public TMatrixN<Real, 3> {
public:
	TMatrix3(): TMatrixN() {

	}
	TMatrix3(Real* prValues, bool bRowMajor): TMatrixN(prValues, bRowMajor) {

	}
	TMatrix3(Real rValue): TMatrixN(rValue) {

	}
	TMatrix3(const TMatrix3& rtMatrix): TMatrixN(rtMatrix) {

	}
	TMatrix3& operator=(const TMatrix3& rtMatrix) {
		return static_cast<TMatrix3&>(TMatrixN::operator=(rtMatrix));
	}
	TMatrix3 operator+(const TMatrix3& rtMatrix) const {
		return static_cast<TMatrix3&>(TMatrixN::operator+(rtMatrix));
	}
	TMatrix3 operator-(const TMatrix3& rtMatrix) const {
		return static_cast<TMatrix3&>(TMatrixN::operator-(rtMatrix));
	}
	TMatrix3 operator*(const TMatrix3& rtMatrix) const {
		return static_cast<TMatrix3&>(TMatrixN::operator*(rtMatrix));
	}
	TMatrix3 operator+(const Real& rValue) const {
		return static_cast<TMatrix3&>(TMatrixN::operator+(rValue));
	}
	TMatrix3 operator-(const Real& rValue) const {
		return static_cast<TMatrix3&>(TMatrixN::operator-(rValue));
	}
	TMatrix3 operator*(const Real& rValue) const {
		return static_cast<TMatrix3&>(TMatrixN::operator*(rValue));
	}
	TMatrix3 operator/(const Real& rValue) const {
		return static_cast<TMatrix3&>(TMatrixN::operator/(rValue));
	}
	TVector3<Real> operator*(TVector3<Real>& rtVector) {
		return static_cast<TVector3<Real>&>(TMatrixN::operator*(rtVector));
	}
	TMatrix3 Inverted() {
		return static_cast<TMatrix3&>(TMatrixN::Inverted());
	}
	TMatrix3 Transposed() {
		return static_cast<TMatrix3&>(TMatrixN::Transposed());
	}
	TVector3<Real> Row(const unsigned int iIndex) {
		return static_cast<TVector3<Real>&>(TMatrixN::Row(iIndex));
	}
	TVector3<Real> Column(const unsigned int iIndex) {
		return static_cast<TVector3<Real>&>(TMatrixN::Column(iIndex));
	}
	void SetRow(const unsigned int iIndex, const TVector3<Real>& rtVector) {
		TMatrixN::SetRow(iIndex, rtVector);
	}
	void SetColumn(const unsigned int iIndex,const TVector3<Real>& rtVector) {
		TMatrixN::SetColumn(iIndex, static_cast<TVector<Real, 3>>(rtVector));
	}
	void ToAxisAngle(TVector3<Real>& rtVector, Real& rrAngle) const {
		rrAngle = acos((Trace()-1)/2);
		if (!rrAngle) {
			rtVector.X() = 1;
			rtVector.Y() = 0;
			rtVector.Z() = 0;
		} else if (rrAngle == M_PI) {
			TMatrix3 S2(*this);
			S2[0][0] -= 1;
			S2[1][1] -= 1;
			S2[2][2] -= 1;
			S2 /= 2;
			rtVector[0] = sqrt(S2[0][0] + 1);
			rtVector[1] = sqrt(S2[1][1] + 1);
			rtVector[2] = sqrt(S2[2][2] + 1);
		} else {
			rtVector.X() = (_values[3*2+1] - _values[3*1+2])/(2*sin(rrAngle));
			rtVector.Y() = (_values[3*0+2] - _values[3*2+0])/(2*sin(rrAngle));
			rtVector.Z() = (_values[3*1+0] - _values[3*0+1])/(2*sin(rrAngle));
		}
	}
	void FromAxisAngle(TVector3<Real>& rtVector, Real rAngle) {
		TMatrix3 result;
		result.Identity();
		result *= cos(rAngle);
		TMatrix3 cross = rtVector.SkewSym();
		TMatrix3 tensor = rtVector.TensorProduct(rtVector);
		result += cross*sin(rAngle) + tensor*(1-cos(rAngle));
		(*this)=result;
	}
	void ToEulerAnglesXYZ(Real& rrX, Real& rrY, Real& rrZ) {
		if (abs(_values[6]) != 1) {
			rrY = -asin(_values[6]);
			rrX = atan2(_values[7]/cos(rrY), _values[8]/cos(rrY));
			rrZ = atan2(_values[3]/cos(rrY), _values[0]/cos(rrY));
		} else {
			rrZ = 0;
			if (_values[6] == -1) {
				rrY = M_PI/2;
				rrX = rrZ + atan2(_values[1], _values[2]);
			} else {
				rrY = -M_PI/2;
				rrX = -rrZ + atan2(-_values[1], -_values[2]);
			}
		}
	}
	void FromEulerAngles(const Real rX, const Real rY, const Real rZ) {
		TMatrix3 RX, RY, RZ;
		TVector3<Real> AX, AY, AZ;
		AX[0] = AY[1] = AZ[2] = 1;
		RX.FromAxisAngle(AX, rX);
		RY.FromAxisAngle(AY, rY);
		RZ.FromAxisAngle(AZ, rZ);
		(*this) = RZ*RY*RX;
	}
};

#endif