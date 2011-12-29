#ifndef _TMATRIXN_H_
#define _TMATRIXN_H_

#include "System.h"

using namespace std;

template<class Real, unsigned int Order>
class TMatrixN {
protected:
	Real* _values;
public:
	TMatrixN() {
		_values = new Real[Order*Order];
	}
	TMatrixN(const Real* prValues) {
		unsigned int i = 0u;
		unsigned int length = Order*Order;
		_values = new Real[length];
		while (i<length) {
			_values[i] = prValues[i];
			++i;
		}
	}
	TMatrixN(const Real rValue) {
		unsigned int i = 0u;
		unsigned int length = Order*Order;
		_values = new Real[length];
		while (i<length) {
			_values[i] = rValue;
			++i;
		}
	}
	TMatrixN(const TMatrixN& rtMatrixN) {
		_values = new Real[Order*Order];
		*this = rtMatrixN;
	}
	~TMatrixN() {
		delete[] _values;
	}
	Real& operator[](const int iIndex) {
		return _values[iIndex];
	}
	TMatrixN& operator=(const TMatrixN& rtMatrixN) {
		unsigned int i = 0u;
		unsigned int length = Order*Order;
		while (i<length) {
			_values[i] = rtMatrixN._values[i];
			++i;
		}
		return *this;
	}
	TMatrixN operator+(const TMatrixN& rtMatrixN) const {
		TMatrixN result(rtMatrixN._values);
		result+=rtMatrixN;
		return result;
	}
	void operator+=(const TMatrixN& rtMatrixN) {
		unsigned int i = 0u;
		unsigned int length = Order*Order;
		while (i<length) {
			_values[i] += rtMatrixN._values[i];
			++i;
		}
	}
	TMatrixN operator-(const TMatrixN& rtMatrixN) const {
		TMatrixN result(rtMatrixN._values);
		result-=rtMatrixN;
		return result;
	}
	void operator-=(const TMatrixN& rtMatrixN) {
		unsigned int i = 0u;
		unsigned int length = Order*Order;
		while (i<length) {
			_values[i] -= rtMatrixN._values[i];
			++i;
		}
	}
	TMatrixN operator*(const TMatrixN& rtMatrixN) const {

	}
	void operator*=(const TMatrixN& rtMatrixN) {
		unsigned int i,j,k;
		TMatrixN temp((Real)0);
		i = 0u;
		while (i<Order) {
			j=0u;
			while (j<Order) {
				k = 0u;
				while (k<Order) {
					temp._values[j*Order+i] += rtMatrixN._values[k*Order+i]*_values[j*Order+k];
					++k;
				}
				++j;
			}
			++i;
		}
		*this = temp;
	}
	void Zero() {
		unsigned int i = 0u;
		unsigned int length = Order*Order;
		while (i<length) {
			_values[i] = 0;
			++i;
		}
	}
	void Identity() {
		unsigned int i = 0u;
		unsigned int j = 0u;
		unsigned int length = Order*Order;
		while (i<Order) {
			j = 0u;
			while (j<Order) {
				if (i == j) {
					_values[i*Order+j] = 1;
				} else {
					_values[i*Order+j] = 0;
				}
				++j;
			}
			++i;
		}
	}

	void ToString() {
		unsigned int i = 0u;
		unsigned int j = 0u;
		unsigned int length = Order*Order;
		while (i<Order) {
			j = 0u;
			while (j<Order) {
				printf("%5.1f", _values[i*Order+j]);
				++j;
			}
			printf("\n");
			++i;
		}
	}

protected:
};

#endif