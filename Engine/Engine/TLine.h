#ifndef _TLINE_H_
#define _TLINE_H_

#include "System.h"
#include "TVector3.h"

template<class Real>
class TLine {
private:
public:
	TLine(const TVector3<Real>& point, const TVector3<Real>& direction) {
		Point = point;
		Direction = direction;
	}
	TLine(TLine& from) {
		this->_direction = from.Direction;
		this->_point = from.Point;
	}
	TVector3<Real> Point;
	TVector3<Real> Direction;
	Real DistanceTo(const TVector3<Real>& point) const {
		TVector3<Real> w = Direction.operator%(point-Point);
		return w.Magnitude();
	}
private:
};

#endif