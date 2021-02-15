#include "ray.hpp"

Ray::Ray(const Point3D &o, const Vec3D &d) : origin(o), direction(d) {}

Point3D Ray::at(const double t) const { return origin + t * direction; }
Point3D Ray::operator()(const double t) const { return at(t); }

Point3D Ray::ori() const { return origin; }
Vec3D Ray::dir() const { return direction; }
