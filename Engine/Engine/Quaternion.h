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
	Quaternion operator-() {
		return static_cast<Quaternion&>(TVector::operator-());
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

	static Quaternion Slerp(const Real& t, const Quaternion& q0, const Quaternion& q1) {
		if (t<=0) return q0;
		if (t>=1) return q1;
		Real cosTheta = q0.Dot(q1);
		Quaternion result = q1;
		if (cosTheta < 0) {
			result = -result;
			cosTheta = -cosTheta;
		}
		if (cosTheta > 1-0.001) {
			return Quaternion::Lerp(t, q0, result);
		}
		Real theta = acos(cosTheta)*2;
		Real a = sin((1-t)*theta);
		Real b = sin(t*theta);
		Quaternion qq = q0;
		return (qq*a+result*b)/sin(theta);
	}

	static Quaternion Lerp(const Real& t, const Quaternion& q0, const Quaternion& q1) {
		return q0 + (q1-q0) * t;
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