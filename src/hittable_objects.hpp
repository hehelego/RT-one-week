#ifndef __CG_HITOBJ_ONCE__
#define __CG_HITOBJ_ONCE__

#include "common.hpp"
#include "hittable.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "vec.hpp"

namespace Objects {
class Sphere : public Hittable {
  Point3D ct;
  double rd;
  std::shared_ptr<Material> mat;

public:
  Sphere(Point3D c, double r, std::shared_ptr<Material> m)
      : ct(c), rd(r), mat(m) {}
  ~Sphere() {}
  std::optional<HitRecord> hit(const Ray &r, double t_min,
                               double t_max) const override;
  std::shared_ptr<Material> material() const override;
  Point3D center() const;
  double radius() const;
};
} // namespace Objects

#endif
