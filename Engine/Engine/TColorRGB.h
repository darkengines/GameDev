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
	TColorRGB(const Real& r, const Real& g, const Real& b) : TVector() {
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
	TColorRGB<Real>& Clamp() {
		_values[0] = clamp(_values[0]);
		_values[1] = clamp(_values[1]);
		_values[2] = clamp(_values[2]);
		return *this;
	}
	TColorRGB<Real>& ScaleByMax() {
		unsigned int index = _max();
		unsigned int i = 0u;
		while (i < 3) {
			if (index != i) {
				_values[i] = _values[i] / _values[index];
			} else {
				_values[index] = (Real)1;
			}
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
	unsigned int _max() const {
		Real max = _values[0];
		unsigned int index = 0;
		if (_values[1] > max) {
			max = _values[1];
		}
		index = 1;
		if (_values[2] > max) {
			max = _values[2];
		}
		index = 2;
		return index;
	}
};
#endif