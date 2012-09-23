#ifndef _TCOLORRGBA_H_
#define _TCOLORRGBA_H_
#pragma once

#include "TVector.h"

template<class Real>
class TColorRGBA: public TVector<Real, 4> {
private:
public:
	TColorRGBA(): TVector() {

	}
	TColorRGBA(const Real& r, const Real& g, const Real& b, const Real& a) : TVector() {
		_values[0] = r;
		_values[1] = g;
		_values[2] = b;
		_values[3] = a;
	}
	TColorRGBA(const Real* prValues): TVector(prValues) {
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
	Real& A() {
		return _values[3];
	}
	TColorRGBA& operator=(const TColorRGBA& rTColor) {
		return static_cast<TColorRGBA&>(TVector::operator=(rTColor));
	}
	TColorRGBA operator+(const TColorRGBA& rTColor) const {
		return static_cast<TColorRGBA&>(TVector::operator+(rTColor));
	}
	TColorRGBA operator-(const TColorRGBA& rTColor) const {
		return static_cast<TColorRGBA&>(TVector::operator-(rTColor));
	}
	Real operator*(const TColorRGBA& rTColor) const {
		TColorRGBA color(_values);
		color[0] = color[0] * rTColor[0];
		color[1] = color[1] * rTColor[1];
		color[2] = color[2] * rTColor[2];
		color[3] = color[3] * rTColor[3];
		return color;
	}
	TColorRGBA operator+(const Real& rrValue) {
		return static_cast<TColorRGBA&>(TVector::operator+(rrValue));
	}
	TColorRGBA operator-(const Real& rrValue) {
		return static_cast<TColorRGBA&>(TVector::operator-(rrValue));
	}
	TColorRGBA operator*(const Real& rrValue) {
		return static_cast<TColorRGBA&>(TVector::operator*(rrValue));
	}
	TColorRGBA operator/(const Real& rrValue) {
		return static_cast<TColorRGBA&>(TVector::operator/(rrValue));
	}
	TColorRGBA Normalized() {
		return static_cast<TColorRGBA&>(TVector::Normalized());
	}
	TColorRGBA AddedScaledVector(const TVector& rTColor, const Real& rrScale) {
		return static_cast<TColorRGBA&>(TVector::AddedScaledVector(rTColor, rrScale));
	}
	TColorRGBA Inverted() const {
		return static_cast<TColorRGBA&>(TVector::Inverted());
	}

	TColorRGBA<Real>& Clamp() {
		_values[0] = clamp(_values[0]);
		_values[1] = clamp(_values[1]);
		_values[2] = clamp(_values[2]);
		_values[3] = clamp(_values[3]);
		return *this;
	}
	TColorRGBA<Real>& ScaleByMax() {
		unsigned int index = max();
		unsigned int i = 0;
		while (i < 4) {
			if (index != i) _values[i] = _values[i] / _values[index];
			++i;
		} else {
			_values[i] = (Real)1
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
		if (_values[3] > max) max = _values[3];
		index = 3;
		return index;
	}
};
#endif