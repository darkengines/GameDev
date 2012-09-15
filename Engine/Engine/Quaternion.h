#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "TVector.h"
#include "TVector3.h"
#include "TMatrix4.h"

#define NEAR_ZERO 0.001

template<class Real>
class Quaternion: public TVector<Real, 4> {
private:
public:
	Quaternion(): TVector() {

	}
	Quaternion(const Real* prValues): TVector(prValues) {
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
	Quaternion& operator=(const Quaternion& rTVector) {
		return static_cast<Quaternion&>(TVector::operator=(rTVector));
	}
	Quaternion operator+(const Quaternion& rTVector) const {
		return static_cast<Quaternion&>(TVector::operator+(rTVector));
	}
	Quaternion operator-(const Quaternion& rTVector) const {
		return static_cast<Quaternion&>(TVector::operator-(rTVector));
	}
	Real operator*(const Quaternion& rTVector) const {
		return TVector::operator*(rTVector);
	}
	Quaternion operator+(const Real& rrValue) {
		return static_cast<Quaternion&>(TVector::operator+(rrValue));
	}
	Quaternion operator-(const Real& rrValue) {
		return static_cast<Quaternion&>(TVector::operator-(rrValue));
	}
	Quaternion operator*(const Real& rrValue) {
		return static_cast<Quaternion&>(TVector::operator*(rrValue));
	}
	Quaternion operator/(const Real& rrValue) {
		return static_cast<Quaternion&>(TVector::operator/(rrValue));
	}
	Quaternion Normalized() {
		return static_cast<Quaternion&>(TVector::Normalized());
	}
	Quaternion AddedScaledVector(const TVector& rtVector, const Real& rrScale) {
		return static_cast<Quaternion&>(TVector::AddedScaledVector(rtVector, rrScale));
	}
	Quaternion Inverted() {
		return static_cast<Quaternion&>(TVector::Inverted());
	}

	//QPart

	Quaternion& operator*=(const Quaternion& rqQ) {
		Quaternion result = Quaternion();
		result[0] = _values[3]*rqQ[0] + _values[0]*rqQ[3] + _values[1]*rqQ[2] - _values[2]*rqQ[1];
		result[1] = _values[3]*rqQ[1] + _values[1]*rqQ[3] + _values[2]*rqQ[0] - _values[0]*rqQ[2];
		result[2] = _values[3]*rqQ[2] + _values[2]*rqQ[3] + _values[0]*rqQ[1] - _values[1]*rqQ[0];
		result[3] = _values[3]*rqQ[3] - _values[0]*rqQ[0] - _values[1]*rqQ[1] - _values[2]*rqQ[2];

		_values[0] = result[0];
		_values[1] = result[1];
		_values[2] = result[2];
		_values[3] = result[3];

		return *this;
	}

	Quaternion operator*(const Quaternion& rqQ) {
		Quaternion result = Quaternion(_values);
		result *= rqQ;
		return result;
	}

	TVector3<Real> Rotate(const TVector3<Real>& v) {
		Quaternion<Real> vq = Quaternion<Real>();
		vq[0] = v[0];
		vq[1] = v[1];
		vq[2] = v[2];
		vq[3] = 0;
		vq = *this*vq;
		Quaternion<Real> cj = Conjugate();
		vq = vq*cj;
		TVector3<Real> result  = TVector3<Real>();
		result[0] = vq[0];
		result[1] = vq[1];
		result[2] = vq[2];
		return result;
	}

	Quaternion<Real>& Conjugate() {
		_values[0] = -_values[0];
		_values[1] = -_values[1];
		_values[2] = -_values[2];
		return *this;
	}

	Quaternion<Real>& FromAxisAngle(const TVector3<Real>& axis, const Real angle) {
		Real x= angle/2;
		_values[0] = sin(x)*axis[0];
		_values[1] = sin(x)*axis[1];
		_values[2] = sin(x)*axis[2];
		_values[3] = cos(x);
		return *this;
	}

	Real Dot(const Quaternion& q) const {
		return TVector<Real, 4>::operator*(q);
	}

	Quaternion& Slerp(const Real& t, const Quaternion& q1, const Quaternion& q2, const Quaternion& q3) {
		Real cosTheta = q1.Dot(q2);
		Quaternion result = Quaternion();
		if (cosTheta >= 1) {
			return q1;
		}
		Real sinTheta = sqrt(1-cosTheta);
		if (sinTheta < NEAR_ZERO) {
			if (t <= 1/2) {
				return sin(M_PI*(1/2-t))*q0+sin(M_PI*t)*q3;
			} else {
				return sin(M_PI*(1-t))*p+sin(M_PI*(t-1/2))*q1;
			}
		} else {
			Real theta = acos(cosTheta)*2;
			return (sin((1-t)*theta)*q0+sin(t*theta)*q1)/sin(theta);
		}
	}

	Quaternion Slerp(const Real& t, const Quaternion& q0, const Quaternion& q1) {
	Real cosTheta = q0.Dot(q1);
		Quaternion result = Quaternion();
		if (cosTheta >= 1) {
			return q0;
		}
		Real theta = acos(cosTheta)*2;
		return q0*(sin((1-t)*theta)+q1*sin(t*theta))/sin(theta);
	}

	TMatrix4<Real>& ToRotationMatrix() {
		TMatrix3<Real> result = TMatrix3<Real>();
		result[0] = _values[3]*_values[3]+_values[0]*_values[0]-_values[1]*_values[1]-_values[2]*_values[2];
		result[1] = 2*_values[0]*_values[1]+2*_values[3]*_values[2];
		result[2] = 2*_values[0]*_values[2]-2*_values[3]*_values[1];
		result[3] = 0;

		result[4] = 2*_values[0]*_values[1]-2*_values[3]*_values[2];
		result[5] = _values[3]*_values[3] - _values[0]*_values[0] +_values[1]*_values[1] -_values[2]*_values[2];
		result[6] = 2*_values[1]*_values[2]+2*_values[3]*_values[0];
		result[7] = 0;

		result[8] = 2*_values[0]*_values[2]+2*_values[3]*_values[1];
		result[9] = 2*_values[1]*_values[2]-2*_values[3]*_values[0];
		result[10] = _values[3]*_values[3] - _values[0]*_values[0] -_values[1]*_values[1]+_values[2]*_values[2];
		result[11] = 0

		result[12] = 0;
		result[13] = 0;
		result[14] = 0;
		result[15] = 1;

		return result;
	}

private:
};

#endif