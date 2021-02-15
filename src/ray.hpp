#ifndef __CG_RAY_ONCE__
#define __CG_RAY_ONCE__

#include "common.hpp"
#include "vec.hpp"

class Ray {
  Point3D origin;
  Vec3D direction;

public:
  Ray(const Point3D &p, const Vec3D &d);
  Point3D at(const double t) const;
  Point3D operator()(const double t) const;

  Point3D ori() const;
  Vec3D dir() const;
};

#endif
