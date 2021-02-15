#ifndef __CG_HITTABLE_ONCE__
#define __CG_HITTABLE_ONCE__

#include "common.hpp"
#include "ray.hpp"
#include "vec.hpp"

class Material;

class HitRecord {
  Point3D p;
  Vec3D n;
  double t;
  std::shared_ptr<Material> m;

public:
  HitRecord(Point3D pp, Vec3D nn, double tt, std::shared_ptr<Material> mm)
      : p(pp), n(nn), t(tt), m(mm) {}
  Point3D point() const;
  Vec3D norm_vec() const;
  double root() const;
  std::shared_ptr<Material> material() const;
};

class Hittable {
public:
  virtual ~Hittable() {}
  virtual std::optional<HitRecord> hit(const Ray &r, double t_min,
                                       double t_max) const = 0; virtual std::shared_ptr<Material> material() const = 0; };

class HittableList : public Hittable {
  std::vector<std::shared_ptr<Hittable>> objs;

public:
  HittableList() {}
  ~HittableList() {}
  void clear();
  void add(std::shared_ptr<Hittable> obj);
  std::optional<HitRecord> hit(const Ray &r, double t_min,
                               double t_max) const override;
  std::shared_ptr<Material> material() const override;
};

#endif
