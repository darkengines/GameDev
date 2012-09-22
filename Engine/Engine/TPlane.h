#ifndef _TPLANE_H_
#define _TPLANE_H_

#include "System.h"
#include "TVector3.h"

template<class Real>
class TPlane {
private:
public:
	TPlane(const TVector3<Real>& point, const TVector3<Real>& normal) {
		Normal = normal;
		Constant = -(point*normal);
	}
	TPlane(const TVector3<Real>& normal, const Real& constant) {
		Normal = normal;
		Constant = constant;
	}
	TPlane(const TVector3<Real>& p0, const TVector3<Real>& p1, const TVector3<Real>& p2) {
		TVector3<Real> e0 = p1-p0;
		TVector3<Real> e1 = p2-p0;
		Normal = (e0%e1);
		Normal.Normalized();
		Constant = -(p0*Normal);
	} 
	TPlane(TPlane& from) {
		Normal = from.Normal;
		Constant = from.Constant;
	}

	int WhichSide(const TVector3<Real>& p) const {
		Real d= DistanceTo(p);
		if (d < 0) return -1;
		if (d > 0) return 1;
		return d;
	}

	Real DistanceTo(const TVector3<Real>& p) const {
		return Normal*p-Constant;
	}

	TVector3<Real> Normal;
	Real Constant;
	
	Real DistanceTo(const TVector3<Real>& point) const {
		TVector3<Real> w = Direction.operator%(point-Point);
		return w.Magnitude();
	}
private:
};

#endif