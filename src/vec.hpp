#ifndef __CG_VEC3D__ONCE__
#define __CG_VEC3D__ONCE__

#include "common.hpp"
class Vec3D {
  double x[3];
  using V3 = const Vec3D &;

public:
  Vec3D(double x0, double x1, double x2);
  Vec3D();

  std::tuple<double, double, double> as_tuple() const;
  double operator[](int) const;

  friend Vec3D operator+(V3 x, V3 y);
  friend Vec3D operator-(V3 x, V3 y);
  friend Vec3D operator*(V3 x, const double k);
  friend Vec3D operator*(const double k, V3 x);
  friend bool operator==(V3 x, V3 y);
  friend double dot(V3 x, V3 y);
  friend Vec3D cross(V3 x, V3 y);

  bool valid() const;

  double norm() const;
  double norm_sq() const;
  Vec3D normalize() const;

  static Vec3D rand(double l, double r);
  static Vec3D rand_us();
  static Vec3D rand_unit();
};

using Point3D = Vec3D;
using RGBcolor = Vec3D;

extern std::string color_string(const RGBcolor &color);
extern RGBcolor gamma_corr(const RGBcolor &color);

#endif
