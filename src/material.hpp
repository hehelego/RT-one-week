#ifndef __CG_MATERIAL_ONCE__
#define __CG_MATERIAL_ONCE__

#include "common.hpp"
#include "hittable.hpp"
#include "ray.hpp"
#include "vec.hpp"

class Material {
public:
  virtual ~Material() {}
  virtual std::optional<Ray> scatter(const Ray &ray,
                                     const HitRecord &rec) const = 0;
  virtual RGBcolor absorb() const = 0;
  virtual std::string name() const = 0;
};

namespace Materials {
class Diffuse : public Material {
  RGBcolor albedo;

public:
  Diffuse(const RGBcolor &albedo) : albedo(albedo) {
    auto [r, g, b] = albedo.as_tuple();
    assert(0 <= r && r <= 1);
    assert(0 <= g && g <= 1);
    assert(0 <= b && b <= 1);
  }
  ~Diffuse() {}
  std::optional<Ray> scatter(const Ray &ray,
                             const HitRecord &rec) const override;
  RGBcolor absorb() const override;
  std::string name() const override;
};

class Metal : public Material {
  RGBcolor albedo;
  double fuzz;

public:
  Metal(const RGBcolor &albedo, double f = 0) : albedo(albedo), fuzz(f) {
    assert(0 <= f && f <= 1);
    auto [r, g, b] = albedo.as_tuple();
    assert(0 <= r && r <= 1);
    assert(0 <= g && g <= 1);
    assert(0 <= b && b <= 1);
  }
  ~Metal() {}
  std::optional<Ray> scatter(const Ray &ray,
                             const HitRecord &rec) const override;
  RGBcolor absorb() const override;
  std::string name() const override;
};

class Dielectric : public Material {
  RGBcolor albedo;
  double eta;
  Metal refl_mat;

public:
  Dielectric(double eta, double f = 0)
      : albedo(RGBcolor{1, 1, 1}), eta(eta), refl_mat(albedo, f) {
    assert(eta > 1);
    assert(0 <= f && f <= 1);
    auto [r, g, b] = albedo.as_tuple();
    assert(0 <= r && r <= 1);
    assert(0 <= g && g <= 1);
    assert(0 <= b && b <= 1);
  }
  std::optional<Ray> scatter(const Ray &ray,
                             const HitRecord &rec) const override;
  RGBcolor absorb() const override;
  std::string name() const override;
};

}; // namespace Materials

#endif
