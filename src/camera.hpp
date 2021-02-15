#ifndef __CG_CAMERA_ONCE__
#define __CG_CAMERA_ONCE__

#include "common.hpp"
#include "ray.hpp"
#include "vec.hpp"

class Camera {
  double focal_length, vfov, aspect_ratio;
  Point3D origin, corner;
  Vec3D vert, hori;

public:
  Camera(Point3D lookfrom, Point3D lookat, Vec3D vup, double vfov,
         double ratio);
  Ray ray_to(double x, double y) const;
};

#endif
