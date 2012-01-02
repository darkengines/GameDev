#ifndef _TMATRIXN_H_
#define _TMATRIXN_H_

#include "System.h"
#include "TVector.h"

using namespace std;

template<class Real, int Order>
class TMatrixN {
protected:
	Real* _values;
public:
	TMatrixN() {
		_values = new Real[Order*Order];
	}
	TMatrixN(const Real* prValues, bool bRowMajor) {
		unsigned int i = 0u;
		unsigned int length = Order*Order;
		_values = new Real[length];
		if (!bRowMajor) {
			unsigned int j = 0u;
			while (i<Order) {
				j = 0u;
				while (j<Order) {
					_values[i*Order+j] = prValues[j*Order+i];
					++j;
				}
				++i;
			}
		} else {
			while (i<length) {
				_values[i] = prValues[i];
				++i;
			}
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
	Real* operator[](const int iIndex) {
		return (Real*)(_values+iIndex*Order);
	}
	Real& operator()(int iRow, int iColumn) {
		return _values[iRow*Order+iColumn];
	}
	virtual bool operator==(const TMatrixN& rtMatrixN) const {
		return !memcmp(_values, rtMatrixN._values, Order*Order*sizeof(Real));
	}
	virtual bool operator!=(const TMatrixN& rtMatrixN) const {
		return !!memcmp(_values, rtMatrixN._values, Order*Order*sizeof(Real));
	}
	virtual bool operator>(const TMatrixN& rtMatrixN) const {
		return memcmp(_values, rtMatrixN._values, Order*Order*sizeof(Real)) > 0;
	}
	virtual bool operator>=(const TMatrixN& rtMatrixN) const {
		return memcmp(_values, rtMatrixN._values, Order*Order*sizeof(Real)) >= 0;
	}
	virtual bool operator<(const TMatrixN& rtMatrixN) const {
		return memcmp(_values, rtMatrixN._values, Order*Order*sizeof(Real)) < 0;
	}
	virtual bool operator<=(const TMatrixN& rtMatrixN) const {
		return memcmp(_values, rtMatrixN._values, Order*Order*sizeof(Real)) <= 0;
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
		TMatrixN result(rtMatrixN._values, true);
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
		TMatrixN result(rtMatrixN._values, true);
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
		TMatrixN result(rtMatrixN._values, true);
		result *= *this;
		return result;
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
	TVector<Real, Order> operator*(TVector<Real, Order>& rtVector) {
		TVector<Real, Order> result;
		unsigned int i = 0u;
		while (i<Order) {
			result[i] = rtVector*Row(i);
			++i;
		}
		return result;
	}
	TMatrixN operator+(const Real& rrValue) const {
		TMatrixN result(rtMatrixN._values, true);
		result+=rrValue;
		return result;
	}
	void operator+=(const Real& rrValue) {
		unsigned int i = 0u;
		unsigned int length = Order*Order;
		while (i<length) {
			_values[i] += rrValue;
			++i;
		}
	}
	TMatrixN operator-(const Real& rrValue) const {
		TMatrixN result(rtMatrixN._values, true);
		result-=rrValue;
		return result;
	}
	void operator-=(const Real& rrValue) {
		unsigned int i = 0u;
		unsigned int length = Order*Order;
		while (i<length) {
			_values[i] -= rrValue;
			++i;
		}
	}
	TMatrixN operator*(const Real& rrValue) const {
		TMatrixN result(rtMatrixN._values, true);
		result*=rrValue;
		return result;
	}
	void operator*=(const Real& rrValue) {
		unsigned int i = 0u;
		unsigned int length = Order*Order;
		while (i<length) {
			_values[i] *= rrValue;
			++i;
		}
	}
	TMatrixN operator/(const Real& rrValue) const {
		TMatrixN result(rtMatrixN._values, true);
		result*=rrValue;
		return result;
	}
	void operator/=(const Real& rrValue) {
		unsigned int i = 0u;
		unsigned int length = Order*Order;
		while (i<length) {
			_values[i] /= rrValue;
			++i;
		}
	}
	void Invert() {
		Real det = Determinant();
		Cofactor();
		Transpose();
		*this /= det;
	}
	TMatrixN Inverted() {
		TMatrixN result(_values, true);
		result.Invert();
		return result;
	}
	TMatrixN Transposed() {
		TMatrixN result(_values, true);
		result.Transpose();
		return result;
	}
	void Transpose() {
		unsigned int i, j;
		i = j = 0u;
		Real temp;
		while (i<Order) {
			j = i;
			while (j<Order) {
				temp = _values[i*Order+j];
				_values[i*Order+j] = _values[j*Order+i];
				_values[j*Order+i] = temp;
				++j;
			}
			++i;
		}
	}
	void Cofactor() {
		*this = Cofactored();
	}
	TMatrixN Cofactored() {
		TMatrixN result(0);
		unsigned int i, j;
		i = 0u;
		while (i<Order) {
			j = 0u;
			while (j<Order) {
				TMatrixN<Real, Order-1> temp = Subed(i, j);
				result[i][j] = Cofactor(i, j)*temp.Determinant();
				++j;
			}
			++i;
		}
		return result;
	}
	TVector<Real, Order> Row(unsigned int iRowIndex) {
		return TVector<Real, Order>(_values+iRowIndex*Order);
	}
	void SetRow(const unsigned int iRow, const TVector<Real, Order>& rtVector) {
		unsigned int i = 0u;
		while (i<Order) {
			_values[iRow*Order+i] = rtVector[i];
			++i;
		}
	}
	void SetColumn(const unsigned int iColumn, const TVector<Real, Order>& rtVector) {
		unsigned int i = 0u;
		while (i<Order) {
			_values[i*Order+iColumn] = rtVector[i];
			++i;
		}
	}
	TVector<Real, Order> Column(unsigned int iColumnIndex) {
		TVector<Real, Order> result;
		unsigned int i = 0u;
		while (i<Order) {
			result[i] = _values[i*Order+iColumnIndex];
			++i;
		}
		return result;
	}
	Real Determinant() {
		return Determinant<Order>();
	}
	Real FastDeterminant() {
		TMatrixN temp(_values, true);
		Real pivot;
		Real result = 1;
		unsigned int i, j, k;
		i = 0u;
		while (i<Order) {
			j = i;
			pivot = 0;
			while (j<Order && !pivot) {
				pivot = temp._values[Order*j+i];
				++j;
			}
			if (pivot) {
				result *= pivot;
				temp.SwitchLines(i, j-1);
				k = i;
				while (k<Order) {
					temp._values[Order*i+k] /= pivot;
					++k;
				}
				k = 0u;
				while (k<Order) {
					if (k != i) {
						j = 0u;
						while (j<Order) {
							temp._values[k*Order+j] -= temp._values[i*Order+k]*temp._values[k*Order+i];
							++j;
						}
					}
					++k;
				}
			} else {
				return 0;
			}
			++i;
		}
		return result;
	}
	Real FastInvert() {
		TMatrixN result, tmpResult;
		TMatrixN temp(_values, true);
		result.Identity();
		tmpResult = result;
		Real pivot;
		Real det = 1;
		unsigned int i, j, k;
		i = 0u;
		while (i<Order) {
			j = i;
			pivot = 0;
			while (j<Order && !pivot) {
				pivot = temp._values[Order*j+i];
				++j;
			}
			if (pivot) {
				det *= pivot;
				SwitchLines(i, j-1);
				result.SwitchLines(i, j-1);
				k = i;
				while (k<Order) {
					_values[Order*i+k] = temp._values[Order*i+k] / pivot;
					result._values[Order*i+k] = tmpResult._values[Order*i+k] / pivot;
					++k;
				}
				k = 0u;
				while (k<Order) {
					if (k != i) {
						j = 0u;
						while (j<Order) {
							_values[k*Order+j] = temp._values[k*Order+j]-temp._values[k*Order+i]*_values[i*Order+j];
							result._values[k*Order+j] = tmpResult._values[k*Order+j]-temp._values[k*Order+i]*result._values[i*Order+j];
							++j;
						}
					}
					++k;
				}
			} else {
				return 0;
			}
			temp = *this;
			tmpResult = result;
			++i;
		}
		*this = result;
		return det;
	}

	

	TMatrixN FastInverted(Real* prOutDeterminant) {
		TMatrixN result(_values, true);
		Real det = result.FastInvert();
		if (prOutDeterminant) {
			*prOutDeterminant = det;
		}
		return result;
	}
	void Zero() {
		unsigned int i = 0u;
		unsigned int length = Order*Order;
		while (i<length) {
			_values[i] = 0;
			++i;
		}
	}
	TMatrixN QR() {
		TMatrixN H(0.0f);
		TMatrixN Q(0.0f);
		H.Identity();
		unsigned int k = 0u;
		while (k<Order-1) {
			TVector<Real, Order> v;
			Real a = 0;
			unsigned int i = k;
			while (i<Order) {
				a += this->operator()(i, k)*(this->operator()(i, k));
				++i;
			}
			a = sqrt(a);
			Real b = a*a-a*(this->operator()(k,k));
			v[k] = this->operator()(k, k) - a;
			i = k+1;
			while (i<Order) {
				v[i] = this->operator()(i,k);
				++i;
			}
			unsigned int j = k;
			while (j<Order) {
				unsigned int i = k;
				Real c = 0;
				while (i<Order) {
					c += v[i]*(this->operator()(i,j));
					++i;
				}
				c/=b;
				i = k;
				while (i<Order) {
					this->operator()(i,j) -= c*v[i];
					++i;
				}
				++j;
			}
			j = 0u;
			while (j<Order) {
				unsigned int i = k;
				Real c = 0;
				while (i<Order) {
					c += v[i]*H[i][j];
					++i;
				}
				c/=b;
				i=k;
				while (i<Order) {
					H[i][j] -= c*v[i];
					++i;
				}
				++j;
			}
			++k;
		}
		Q = H.Transposed();
		return Q;
	}

	void Jacobi(TVector<Real, Order>& rtOutEigenValues, TMatrixN& rtOutEigenVectors) {
		int i, k, l, m, state;
		Real s, c, t, p, y;
		TVector<int, Order> ind;
		TVector<bool, Order> changed;

		rtOutEigenVectors.Identity();
		state = Order;
		k = 0;
		while (k<Order) {
			m = k+1;
			i = k+2;
			//maxind(k)
			while (i<Order) {
				if (abs(this->operator()(k, i)) > abs(this->operator()(k, m))) {
					m = i;
				}
				++i;
			}
			ind[k] = m;
			rtOutEigenValues[k] = this->operator()(k,k);
			changed[k] = true; 
			++k;
		}
		while (state != 0) {
			m = 0;
			k = 1;
			while (k<Order-1) {
				if (fabs(this->operator()(k, ind[k])) > fabs(this->operator()(m, ind[m]))) {
					m = k;
				}
				++k;
			}
			k = m;
			l = ind[m];
			p = this->operator()(k, l);
			y = (rtOutEigenValues[l]-rtOutEigenValues[k])/2;
			t = fabs(y)+sqrtf(p*p+y*y);
			s = sqrtf(p*p+t*t);
			c = t/s;
			s = p/s;
			t = (p*p)/t;
			if (y<0) {
				s = -s;
				t = -t;
			}
			this->operator()(k,l) = 0.0;

			//update(k,−t);
			y = rtOutEigenValues[k];
			rtOutEigenValues[k] = y-t;
			if (changed[k] && y == rtOutEigenValues[k]) {
				changed[k] = false;
				state--;
			} else if (!changed[k] && y != rtOutEigenValues[k]) {
				changed[k] = true;
				state++;
			}

			//update(l,t);
			y = rtOutEigenValues[l];
			rtOutEigenValues[l] = y+t;
			if (changed[l] && y == rtOutEigenValues[l]) {
				changed[l] = false;
				state--;
			} else if (!changed[l] && y != rtOutEigenValues[l]) {
				changed[l] = true;
				state++;
			}

			i = 0;
			while (i<=k) {
				//rotate(i,k,i,l);
				TVector<Real, 2> tmp;
				tmp[0] = this->operator()(i,k);
				tmp[1] = this->operator()(i,l);
				this->operator()(i,k)= tmp[0]*c + tmp[1]*-s;
				this->operator()(i,l)= tmp[0]*s + tmp[1]*c;
				++i;
			}
			i = k+1;

			while (i<=l) {
				//rotate(k,i,i,l);
				TVector<Real, 2> tmp;
				tmp[0] = this->operator()(k,i);
				tmp[1] = this->operator()(i,l);
				this->operator()(k,i)= tmp[0]*c + tmp[1]*-s;
				this->operator()(i,l)= tmp[0]*s + tmp[1]*c;
				++i;
			}
			i = l+1;

			while (i<Order) {
				//rotate(k,i,l,i);
				TVector<Real, 2> tmp;
				tmp[0] = this->operator()(k,i);
				tmp[1] = this->operator()(l,i);
				this->operator()(k,i)= tmp[0]*c + tmp[1]*-s;
				this->operator()(l,i)= tmp[0]*s + tmp[1]*c;
				++i;
			}

			i = 0;
			while (i<Order) {
				Real tmp0, tmp1;
				tmp0 = rtOutEigenVectors(k,i);
				tmp1 = rtOutEigenVectors(l,i);
				rtOutEigenVectors(k,i)= tmp0*c + tmp1*-s;
				rtOutEigenVectors(l,i)= tmp0*s + tmp1*c;
				++i;
			}
			//maxind(k)
			m = k+1;
			i = k+2;
			while (i<Order) {
				if (fabs(this->operator()(k, i)) > fabs(this->operator()(k, m))) {
					m = i;
				}
				++i;
			}
			ind[k] = m;
			//maxind(l)
			m = l+1;
			i = l+2;
			while (i<Order) {
				if (fabs(this->operator()(l, i)) > fabs(this->operator()(l, m))) {
					m = i;
				}
				++i;
			}
			ind[l] = m;
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
				printf("%15.8f", _values[i*Order+j]);
				++j;
			}
			printf("\n");
			++i;
		}
	}
	
	TMatrixN<Real, Order-1> Subed(unsigned int iRowIndex, unsigned int iColumnIndex) {
		TMatrixN<Real, Order-1> result;
		unsigned int i, j, k, l = 0u;
		i = j = k = l = 0u;
		while (i<Order) {
			if (i != iRowIndex) {
				j = 0u;
				l = 0u;
				while (j<Order) {
					if (j!=iColumnIndex) {
						result[k][l] = _values[i*Order+j];
						++l;
					}
					++j;
				}
				++k;
			}
			++i;
		}
		return result;
	}

protected:
	int Cofactor(unsigned int iRowIndex, unsigned int iColumnIndex) {
		return (iRowIndex+iColumnIndex) % 2 ? -1 : 1;
	}
	void SwitchLines(int iRow1, int iRow2) {
		if (iRow1 != iRow2) {
			unsigned int i = 0u;
			Real temp;
			while (i<Order) {
				temp = _values[Order*iRow1 + i];
				_values[Order*iRow1 + i] = _values[Order*iRow2 + i];
				_values[Order*iRow2 + i] = temp;
				++i;
			}
		}
	}
	template<int Order>
	Real Determinant() {
		unsigned int i = 0u;
		Real result = 0;
		while (i<Order) {
			if (_values[i]) {
				result += _values[i]*Cofactor(0, i % Order) * Subed(0, i).Determinant();
				++i;
			} else {
				return 0;
			}
		}
		return result;
	}
	template<>
	Real Determinant<2>() {
		return _values[0]*_values[3] - _values[1]*_values[2];
	}
};

#endif