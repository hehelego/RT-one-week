#include "vec.hpp"
#include "common.hpp"

Vec3D::Vec3D(double x0, double x1, double x2) : x{x0, x1, x2} {}
Vec3D::Vec3D() : Vec3D(0, 0, 0) {}
Vec3D Vec3D::rand(double l, double r) {
  double x = rand_lr(l, r);
  double y = rand_lr(l, r);
  double z = rand_lr(l, r);
  return Vec3D{x, y, z};
}
Vec3D Vec3D::rand_us() {
  Vec3D v = Vec3D::rand(-1, 1);
  while (v.norm_sq() >= 1)
    v = Vec3D::rand(-1, 1);
  return v;
}
Vec3D Vec3D::rand_unit() { return Vec3D::rand_us().normalize(); }

std::tuple<double, double, double> Vec3D::as_tuple() const {
  return {x[0], x[1], x[2]};
}
double Vec3D::operator[](int i) const { return x[i]; }
bool operator==(const Vec3D &x, const Vec3D &y) {
  return iszero(x[0] - y[0]) && iszero(x[1] - y[1]) && iszero(x[2] - y[2]);
}

Vec3D operator+(const Vec3D &x, const Vec3D &y) {
  return {x[0] + y[0], x[1] + y[1], x[2] + y[2]};
}
Vec3D operator-(const Vec3D &x, const Vec3D &y) {
  return {x[0] - y[0], x[1] - y[1], x[2] - y[2]};
}
Vec3D operator*(const Vec3D &x, const double k) {
  return {k * x[0], k * x[1], k * x[2]};
}
Vec3D operator*(const double k, const Vec3D &x) {
  return {k * x[0], k * x[1], k * x[2]};
}

double dot(const Vec3D &x, const Vec3D &y) {
  return x[0] * y[0] + x[1] * y[1] + x[2] * y[2];
}
Vec3D cross(const Vec3D &x, const Vec3D &y) {
  return {x[1] * y[2] - x[2] * y[1], x[2] * y[0] - x[0] * y[2],
          x[0] * y[1] - x[1] * y[0]};
}

double Vec3D::norm_sq() const { return dot(*this, *this); }
double Vec3D::norm() const { return std::sqrt(norm_sq()); }
Vec3D Vec3D::normalize() const {
  const auto l = this->norm();
  return iszero(l) ? *this : (1.0 / l) * (*this);
}
bool Vec3D::valid() const {
  const auto t0 = !std::isnan(x[0]);
  const auto t1 = !std::isnan(x[1]);
  const auto t2 = !std::isnan(x[2]);
  return t0 && t1 && t2;
}

std::string color_string(const RGBcolor &color) {
  assert(color.valid());
  const auto extend = [&](const double x) -> int {
    auto y = x;
    y = std::max<double>(y, 0);
    y = std::min<double>(y, 1 - EPS);
    const auto res = static_cast<int>(floor(y * ColorLim));
    assert(res >= 0 && res < ColorLim);
    return res;
  };
  std::stringstream ss;
  ss << extend(color[0]) << " " << extend(color[1]) << " " << extend(color[2]);
  return ss.str();
}

static double gamma_corr(const double x) { return std::pow(x, 1.0 / Gamma); }
RGBcolor gamma_corr(const RGBcolor &color) {
  const auto [r, g, b] = color.as_tuple();
  return RGBcolor{gamma_corr(r), gamma_corr(g), gamma_corr(b)};
}
