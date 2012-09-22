#ifndef _TCOLORRGB_H_
#define _TCOLORRGB_H_
#pragma once

#include "TVector.h"

template<class Real>
class TColorRGB: public TVector<Real, 3> {
private:
public:
	TColorRGB(): TVector() {

	}
	TColorRGB(const Real& r, const Real& g, const Real& b) : TVector() const {
		_values[0] = r;
		_values[1] = g;
		_values[2] = b;
	}
	TColorRGB(const Real* prValues): TVector(prValues) {
	}
	Real& R() {
		return _values[0];
	}
	Real& G() {
		return _values[1];
	}
	Real& B() {
		return _values[2];
	}
	TColorRGB& operator=(const TColorRGB& rTColor) {
		return static_cast<TColorRGB&>(TVector::operator=(rTColor));
	}
	TColorRGB operator+(const TColorRGB& rTColor) const {
		return static_cast<TColorRGB&>(TVector::operator+(rTColor));
	}
	TColorRGB operator-(const TColorRGB& rTColor) const {
		return static_cast<TColorRGB&>(TVector::operator-(rTColor));
	}
	TColorRGB operator%(const TColorRGB& rTColor) const {
		TColorRGB result(_values);
		return result %= rTColor;
	}
	TColorRGB& operator%=(const TColorRGB& rTColor) {
		Real x,y,z;
		x = _values[0];
		y = _values[1];
		z = _values[2];
		_values[0] = y * rTColor._values[2] - z * rTColor[1];
		_values[1] = z * rTColor._values[0] - x * rTColor[2];
		_values[2] = x * rTColor._values[1] - y * rTColor[0];
		return *this;
	}
	void UnitCross(const TColorRGB& rTColor) {
		*this%=rTColor;
		Normalize();
	}
	TColorRGB UnitCrossed(const TColorRGB& rTColor) {
		TColorRGB result(_values);
		return result.UnitCross();
	}
	Real operator*(const TColorRGB& rTColor) const {
		TColorRGB color(_values);
		color[0] = color[0] * rTColor[0];
		color[1] = color[1] * rTColor[1];
		color[2] = color[2] * rTColor[2];
		return color;
	}
	TColorRGB operator+(const Real& rrValue) {
		return static_cast<TColorRGB&>(TVector::operator+(rrValue));
	}
	TColorRGB operator-(const Real& rrValue) {
		return static_cast<TColorRGB&>(TVector::operator-(rrValue));
	}
	TColorRGB operator*(const Real& rrValue) {
		return static_cast<TColorRGB&>(TVector::operator*(rrValue));
	}
	TColorRGB operator/(const Real& rrValue) {
		return static_cast<TColorRGB&>(TVector::operator/(rrValue));
	}
	TColorRGB Normalized() {
		return static_cast<TColorRGB&>(TVector::Normalized());
	}
	TColorRGB AddedScaledVector(const TVector& rTColor, const Real& rrScale) {
		return static_cast<TColorRGB&>(TVector::AddedScaledVector(rTColor, rrScale));
	}
	TColorRGB Inverted() const {
		return static_cast<TColorRGB&>(TVector::Inverted());
	}
	
	void Perp() {
		Real temp = _values[0];
		_values[0] = _values[1];
		_values[1] = -temp;
	}
	TColorRGB UnitPerped() const {
		TColorRGB result = Perped();
		result.Normalize();
		return result;
	}
	Real DotPerp(const TColorRGB& rTColor) {
		return *this*rTColor.Perped();
	}
	static void Orthonormalize(TColorRGB& rTColor1, TColorRGB& rTColor2, TColorRGB& rTColorRGB) {
		rTColor1.Normalize();

		rTColor2 -= rTColor1*(rTColor1*rTColor2);
		rTColor2.Normalize();

		rTColorRGB -= ((rTColor1 * (rTColor1*rTColorRGB)) + (rTColor2 * (rTColor2*rTColorRGB)));
		rTColorRGB.Normalize();
	}
	static void GenerateOrthonormalBasis(TColorRGB& rTColorU, TColorRGB& rTColorV, TColorRGB& rTColorW, bool bUIsNormalized) {
		if (!bUIsNormalized) {
			rTColorU.Normalize();
		}
		if (abs(rTColorU._values[0]) > abs(rTColorU._values[1])) {
			rTColorV._values[0] = rTColorU._values[2];
			rTColorV._values[2] = -rTColorU._values[1];
			rTColorV._values[1] = 0;
		} else {
			rTColorV._values[1] = rTColorU._values[2];
			rTColorV._values[2] = -rTColorU._values[0];
			rTColorV._values[0] = 0;
		}
		rTColorV.Normalize();
		rTColorW = rTColorU.UnitCrossed(rTColorV);
	}
	TMatrix3<Real> SkewSym() {
		TMatrix3<Real> result;
		result[0][0] = 0;
		result[0][1] = -_values[2];
		result[0][2] = _values[1];
		result[1][0] = _values[2];
		result[1][1] = 0;
		result[1][2] = -_values[0];
		result[2][0] = -_values[1];
		result[2][1] = _values[0];
		result[2][2] = 0;
		return result;
	}
	TMatrix3<Real> TensorProduct(const TColorRGB<Real>& rTColor) const {
		return static_cast<const TMatrix3<Real>&>(TVector::TensorProduct(rTColor));
	}
	TColorRGB<Real>& Clamp() {
		_values[0] = clamp(_values[0]);
		_values[1] = clamp(_values[1]);
		_values[2] = clamp(_values[2]);
		return *this;
	}
	TColorRGB<Real>& ScaleByMax() {
		unsigned int index = max();
		unsigned int i = 0;
		while (i < Size) {
			if (index != i) _values[i] = _values[i] / _values[max];
			++i;
		}
		return *this;
	}
private:
	Real& clamp(Real& real) {
		if (real < 0) real = 0;
		if (real > 1) real = 1;
		return real;
	}
	unsigned int max() const {
		Real max = _values[0];
		unsigned int index = 0;
		if (_values[1] > max) max = _values[1];
		index = 1;
		if (_values[2] > max) max = _values[2];
		index = 2;
		return index;
	}
};
#endif