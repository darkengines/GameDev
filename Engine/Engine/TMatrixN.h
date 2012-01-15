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
	void SetColumn(const unsigned int iColumn, TVector<Real, Order>& rtVector) {
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

	void Jacobi(TMatrixN& rtOutEigenVectors, TVector<Real, Order>& rtOutEigenValues) {
		int i,j,ip,iq;
		Real tresh, theta, tau, t, sm, s, h, g, c;
		TVector<Real, Order> b, z;
		rtOutEigenVectors.Identity();
		TMatrixN temp(this->_values, true);
		for (ip = 0;ip<Order;++ip) {
			b[ip] = rtOutEigenValues[ip] = temp[ip][ip];
			z[ip] = 0;
		}
		for (i=1;i<=50;++i) {
			sm = 0;
			for (ip=0;ip<Order-1;++ip) {
				for (iq=ip+1;iq<Order;++iq) {
					sm += abs(temp[ip][iq]);
				}
				if (sm == 0) {
					eigsrt(rtOutEigenValues, rtOutEigenVectors);
					return;
				}
				if (i<4) {
					tresh = 0.2*sm/(Order*Order);
				} else {
					tresh = 0;
				}
				for (ip=0;ip<Order-1;ip++) {
					for (iq = ip+1; iq<Order; iq++) {
						g = 100*abs(temp[ip][iq]);
						if (i>4 && g<=FLT_EPSILON*abs(rtOutEigenValues[ip]) && g<=FLT_EPSILON*abs(rtOutEigenValues[iq])) {
							temp[ip][iq] = 0;
						} else if (abs(temp[ip][iq]) > tresh) {
							h = rtOutEigenValues[iq]-rtOutEigenValues[ip];
							if (g<=FLT_EPSILON*abs(h)) {
								t = temp[ip][iq]/h;
							} else {
								theta = 0.5*h/(temp[ip][iq]);
								t = 1/(abs(theta)+sqrt(1+theta*theta));
								if (theta < 0) {
									t = -t;
								}
								c=1/sqrt(1+t*t);
								s = t*c;
								tau = s/(1+c);
								h = t*temp[ip][iq];
								z[ip] -= h;
								z[iq] += h;
								rtOutEigenValues[ip] -= h;
								rtOutEigenValues[iq] += h;
								temp[ip][iq] = 0;
								for (j=0;j<ip;j++) {
									rot(temp, s, tau, j, ip, j, iq);
								}
								for (j=ip+1;j<iq;++j) {
									rot(temp, s, tau, ip, j, j, iq);
								}
								for (j=iq+1;j<Order;++j) {
									rot(temp, s, tau, ip, j, iq, j);
								}
								for (j=0; j<Order; ++j) {
									rot(rtOutEigenVectors, s, tau, j, ip, j, iq);
								}
							}
						}
					}
				}
				for (ip=0;ip<Order;++ip) {
						b[ip] += z[ip];
						rtOutEigenValues[ip] = b[ip];
						z[ip] = 0;
					}
			}
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
	void rot(TMatrixN& rtIOMatrixN, const Real s, const Real tau, const int i, const int j, const int k, const int l) {
		Real g= rtIOMatrixN[i][j];
		Real h = rtIOMatrixN[k][l];
		rtIOMatrixN[i][j] = g - s*(h+g*tau);
		rtIOMatrixN[k][l] = h + s*(g-h*tau);
	}
	void eigsrt(TVector<Real, Order>& rtIOEigenValues, TMatrixN& rtIOEigenVectors) {
		int k;
		int n=Order;
		for (int i = 0;i<n-1;++i) {
			Real p = rtIOEigenValues[k=i];
			for (int j=i;j<n;++j) {
				if (rtIOEigenValues[j] >=p) p=rtIOEigenValues[k=j];
			}
			if (k!= i) {
				rtIOEigenValues[k] = rtIOEigenValues[i];
				rtIOEigenValues[i] = p;
					for (int j=0;j<n;++j) {
						p = rtIOEigenVectors[j][i];
						rtIOEigenVectors[j][i] = rtIOEigenVectors[j][k];
						rtIOEigenVectors[j][k] = p;
					}
			}
		}
	}
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