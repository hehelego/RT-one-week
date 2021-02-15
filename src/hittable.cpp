#include "hittable.hpp"

Point3D HitRecord::point() const { return p; }
Vec3D HitRecord::norm_vec() const { return n; }
double HitRecord::root() const { return t; }
std::shared_ptr<Material> HitRecord::material() const { return m; }

void HittableList::clear() { objs.clear(); }
void HittableList::add(std::shared_ptr<Hittable> obj) { objs.push_back(obj); }
std::optional<HitRecord> HittableList::hit(const Ray &r, double t_min,
                                           double t_max) const {
  std::optional<HitRecord> record = {};
  for (const auto &o : this->objs) {
    const auto rec = o->hit(r, t_min, t_max);
    if (rec.has_value()) {
      t_max = rec.value().root();
      record = rec;
    }
  }
  return record;
}
std::shared_ptr<Material> HittableList::material() const { return nullptr; }
