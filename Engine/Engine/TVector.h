#ifndef _TVECTOR_H_
#define _TVECTOR_H_

#include "System.h"

template<class Real, int Size>
class TVector {
protected:
	Real* values;
public:
	TVector() {
		values = (Real*)malloc(sizeof(Real)*Size);
	}
	TVector(Real* prValues) {
		values = prValues;
	}
	virtual ~TVector() {
		free(values);
	}
	virtual Real& operator[](int iIndex) {
		return *(values+iIndex);
	}
	// TVector x TVector operators
	virtual bool operator==(const TVector<Real, Size>& rTVector) {
		int i = 0;
		bool result = true;
		while (i<Size) {
			result = result && (*(values+i) == *(rTVector.values+i));
			i++;
		}
		return result;
	}
	virtual bool operator!=(const TVector<Real, Size>& rTVector) {
		return !(*this==rTVector);
	}
	virtual bool operator>(const TVector<Real, Size>& rTVector) {
		return memcmp(values, rTVector.values, Size) > 0;
	}
	virtual bool operator<(const TVector<Real, Size>& rTVector) {
		return memcmp(values, rTVector.values, Size) < 0;
	}
	virtual bool operator>=(const TVector<Real, Size>& rTVector) {
		return memcmp(values, rTVector.values, Size) >= 0;
	}
	virtual bool operator<=(const TVector<Real, Size>& rTVector) {
		return memcmp(values, rTVector.values, Size) <= 0;
	}
	virtual TVector<Real, Size>& operator=(const TVector<Real, Size>& rTVector) {
		int i = 0;
		while (i<Size) {
			*(values+i) = *(rTVector.values+i);
			i++;
		}
		return *this;
	}
	virtual TVector<Real, Size>& operator+(const TVector<Real, Size>& rTVector) const {
		int i = 0;
		Real* result = (Real*)malloc(sizeof(Real)*Size);
		memcpy(result, values, Size);
		while (i<Size) {
			*(result+i) += *(rTVector.values+i);
			i++;
		}
		return TVector(result);
	}
	virtual void operator+=(const TVector<Real, Size>& rTVector) {
		int i = 0;
		while (i<Size) {
			*(values+i) += *(rTVector.values+i);
			i++;
		}
	}
	virtual TVector<Real, Size> operator-(const TVector<Real, Size>& rTVector) const {
		int i = 0;
		Real* result = (Real*)malloc(sizeof(Real)*Size);
		memcpy(result, values, Size);
		while (i<Size) {
			*(result+i) -= *(rTVector.values+i);
			i++;
		}
		return TVector<Real, Size>(result);
	}
	virtual Real operator*(TVector<Real, Size>& rTVector) const {
		int i = 0;
		Real result = 0;
		while (i<Size) {
			result += *(rTVector.values+i)**(values+i);
			i++;
		}
		return result;
	}
	// TVector x Real operators
	virtual TVector<Real, Size> operator+(const Real& rrValue) const {
		int i = 0;
		Real* result = (Real*)malloc(sizeof(Real)*Size);
		memcpy(result, values, Size);
		while (i<Size) {
			*(result+i) += rrValue;
			i++;
		}
		return TVector<Real, Size>(result);
	}
	virtual TVector<Real, Size> operator-(const Real& rrValue) const {
		int i = 0;
		Real* result = (Real*)malloc(sizeof(Real)*Size);
		memcpy(result, values, Size);
		while (i<Size) {
			*(result+i) -= rrValue;
			i++;
		}
		return TVector<Real, Size>(result);
	}
	virtual TVector<Real, Size> operator*(const Real& rrValue) const {
		int i = 0;
		Real* result = (Real*)malloc(sizeof(Real)*Size);
		memcpy(result, values, Size);
		while (i<Size) {
			*(result+i) *= rrValue;
			i++;
		}
		return TVector<Real, Size>(result);
	}
	virtual TVector<Real, Size> operator/(const Real& rrValue) const {
		int i = 0;
		Real* result = (Real*)malloc(sizeof(Real)*Size);
		memcpy(result, values, Size);
		while (i<Size) {
			*(result+i) /= rrValue;
			i++;
		}
		return TVector<Real, Size>(result);
	}
private:
};

#endif