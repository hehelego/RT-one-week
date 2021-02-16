#include "material.hpp"

namespace Materials {

std::optional<Ray> Diffuse::scatter(const Ray &ray,
                                    const HitRecord &rec) const {
  auto norm = rec.norm_vec();
  if (dot(norm, ray.dir()) >= 0) {
    norm = (-1.0) * norm;
  }
  auto dir = norm + Vec3D::rand_unit();
  if (dir == Vec3D{0, 0, 0}) {
    dir = norm;
  }
  assert(dir.valid());
  return Ray{rec.point(), dir};
}
RGBcolor Diffuse::albedo() const { return alb; }
std::string Diffuse::name() const { return "diffuse"; }

std::optional<Ray> Metal::scatter(const Ray &ray, const HitRecord &rec) const {
  auto norm = rec.norm_vec().normalize();
  auto k = -dot(ray.dir(), norm);
  auto refl = ray.dir() + 2.0 * k * norm;
  auto fuzz_offset = f * Vec3D::rand_us();
  assert((refl + fuzz_offset).valid());
  return Ray{rec.point(), refl + fuzz_offset};
}
RGBcolor Metal::albedo() const { return alb; }
std::string Metal::name() const { return "metal"; }

std::optional<Ray> Dielectric::scatter(const Ray &ray,
                                       const HitRecord &rec) const {
  const double prob_refl = 0.3; // TODO: probability=energy_out/energy_in
  if (rand_01() < prob_refl) {
    return this->refl_mat.scatter(ray, rec);
  }

  if (cross(ray.dir(), rec.norm_vec()) == Vec3D{0, 0, 0}) {
    return Ray{rec.point(), ray.dir()};
  }
  auto vin = ray.dir().normalize(), norm = rec.norm_vec().normalize();
  auto cos_in = dot(vin, norm);
  auto sin_in = std::sqrt(1.0 - cos_in * cos_in);
  double cos_out, sin_out = 0, norm_out = 0;
  if (cos_in <= 0) { // (Air) -> (Material)
    cos_in = -cos_in;
    sin_out = sin_in / this->eta;
    norm_out = this->eta;
    cos_out = std::sqrt(1.0 - sin_out * sin_out);
  } else {
    sin_out = sin_in * this->eta;
    norm_out = 1.0 / this->eta;
    if (sin_out >= 1)
      return this->refl_mat.scatter(ray, rec);
    cos_out = std::sqrt(1.0 - sin_out * sin_out);
  }
  const auto k = 1.0 * cos_in - norm_out * cos_out;
  assert((vin + norm * k).valid());
  return Ray{rec.point(), vin + norm * k};
}
RGBcolor Dielectric::albedo() const { return alb; }
std::string Dielectric::name() const { return "dielectric"; }

} // namespace Materials
