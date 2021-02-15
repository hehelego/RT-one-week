#include "hittable_objects.hpp"
#include "hittable.hpp"

namespace Objects {

Point3D Sphere::center() const { return this->ct; }
double Sphere::radius() const { return this->rd; }
std::shared_ptr<Material> Sphere::material() const { return this->mat; }
std::optional<HitRecord> Sphere::hit(const Ray &r, double t_min,
                                     double t_max) const {
  const auto oc = r.ori() - this->ct;
  const auto a = r.dir().norm_sq();
  const auto half_b = dot(r.dir(), oc);
  const auto c = oc.norm_sq() - rd * rd;
  const auto det = half_b * half_b - a * c;
  if (det >= 0) {
    double root = 0;

    root = (-half_b - sqrt(det)) / a;
    if (t_min <= root && root <= t_max) {
      const auto hitpoint = r.at(root);
      const auto n = (hitpoint - this->ct) * (1.0 / this->rd);
      return HitRecord(hitpoint, n, root, this->material());
    }
    root = (-half_b + sqrt(det)) / a;
    if (t_min <= root && root <= t_max) {
      const auto hitpoint = r.at(root);
      const auto n = (hitpoint - this->ct) * (1.0 / this->rd);
      return HitRecord(hitpoint, n, root, this->material());
    }
  }
  return {};
}
} // namespace Objects
