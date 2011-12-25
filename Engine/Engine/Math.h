#ifndef _MATH_H_
#define _MATH_H_

#include "System.h"

template<class Real>
class Math {
private:
public:
	static const float EPSILON = FLT_EPSILON;
	static const float MAX_REAL = FLT_MAX;
	static const float PI = 4.0*ATan(1.0);
	static const float TWO_PI = 8.0*ATan(1.0);
	static const float HALF_PI = 2.0*ATan(1.0);
	static const float INV_PI = 1/PI;
	static const float INV_TWO_PI = 1/TWO_PI;

	static Real Cos(Real fValue) {
		if (fValue == 0) return 1.0;
		if (fValue == HALF_PI) return 0.0;
		if (fValue == PI) return -1.0;
		return (Real)cos((double)fValue);
	}
	static Real Sin(Real fValue) {
		if (fValue == 0 || fValue == PI) return 0.0;
		if (fValue == HALF_PI) return 1.0;
		return (Real)sin((double)fValue);
	}
	static Real Tan(Real fValue) {
		if (fValue == 0) return 0.0;
		if (fValue == PI/4) return 1.0;
		return (Real)tan((double)fValue);
	}
	static Real Exp(Real fValue) {
		if (fValue == 0) return 1.0;
		return (Real)exp((double)fValue);
	}
	static Real Pow(Real fValue, Real fExponent) {
		if (fExponent == 0) return 1;
		if (fExponent == 1) return fValue;
		return (Real)pow((double)fValue, (double)fExponent);
	}
	static Real SQR(Real fValue) {
		return (Real)fValue*(Real)fValue;
	}
	static Real ACos(Real fValue) {
		if (fValue == 1.0) return 0;
		if (fValue == 0.0) return HALF_PI;
		if (fValue == -1.0) return PI;
		return (Real)acos((double)fValue);
	}
	static Real ASin(Real fValue) {
		if (fValue == 0.0) return 0.0;
		if (fValue == 1.0) return HALF_PI;
		return (Real)asin((double)fValue);
	}
	static Real ATan(Real fValue) {
		if (fValue == 0) return 0;
		return (Real)atan((double)fValue);
	}
	static Real Log(Real fValue) {
		if (fValue == 1.0) return 0.0;
		return (Real)log((double)fValue);
	}
	static Real Abs(Real fValue) {
		return (Real)abs((double)fValue);
	}
	static Real Ceil(Real fValue) {
		return (Real)ceil((double)fValue);
	}
	static Real Floor(Real fValue) {
		return (Real)floor((double)fValue);
	}
	static Real SQRT(Real fValue) {
		return (Real)sqrt((double)fValue);
	}
	static Real InvSQRT(Real fValue) {
		return (Real)1/(Real)sqrt((double)fValue);
	}
	static int Sign(int iValue) {
		if (iValue == 0) return 0;
		return (iValue > 0) ? 1:-1;
	}
	static Real Sign(Real fValue) {
		if (iValue == 0) return 0;
		return (iValue > 0) ? 1:-1;
	}
	static Real UnitRandom() {
		srand(time(0));
		int rnd = rand();
		return (rnd == 0) ? 0.0:1.0/(Real)rnd;
	}
	static Real SymmetricRandom() {
		srand(time(0));
		int sign = (rand() % 2 == 0) ? -1 : 1;
		return UnitRandom() * sign;
	}
	static Real IntervalRandom(Real fMin, Real fMax) {
		srand(time(0));
		Real range = fMax-fMin;
		return range*UnitRandom()+fMin;
	}
private:
};

#endif