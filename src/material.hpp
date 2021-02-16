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
  virtual RGBcolor albedo() const = 0;
  virtual std::string name() const = 0;
};

namespace Materials {
class Diffuse : public Material {
  RGBcolor alb;

public:
  Diffuse(const RGBcolor &albedo) : alb(albedo) {
    auto [r, g, b] = albedo.as_tuple();
    assert(0 <= r && r <= 1);
    assert(0 <= g && g <= 1);
    assert(0 <= b && b <= 1);
  }
  ~Diffuse() {}
  std::optional<Ray> scatter(const Ray &ray,
                             const HitRecord &rec) const override;
  RGBcolor albedo() const override;
  std::string name() const override;
};

class Metal : public Material {
  RGBcolor alb;
  double f;

public:
  Metal(const RGBcolor &albedo, double fuzz = 0) : alb(albedo), f(fuzz) {
    assert(0 <= f && f <= 1);
    auto [r, g, b] = albedo.as_tuple();
    assert(0 <= r && r <= 1);
    assert(0 <= g && g <= 1);
    assert(0 <= b && b <= 1);
  }
  ~Metal() {}
  std::optional<Ray> scatter(const Ray &ray,
                             const HitRecord &rec) const override;
  RGBcolor albedo() const override;
  std::string name() const override;
};

class Dielectric : public Material {
  RGBcolor alb;
  double eta;
  Metal refl_mat;

public:
  Dielectric(double eta, double f = 0)
      : alb(RGBcolor{1, 1, 1}), eta(eta), refl_mat(alb, f) {
    assert(eta > 1);
    assert(0 <= f && f <= 1);
    auto [r, g, b] = alb.as_tuple();
    assert(0 <= r && r <= 1);
    assert(0 <= g && g <= 1);
    assert(0 <= b && b <= 1);
  }
  std::optional<Ray> scatter(const Ray &ray,
                             const HitRecord &rec) const override;
  RGBcolor albedo() const override;
  std::string name() const override;
};

}; // namespace Materials

#endif
