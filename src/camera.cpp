#include "camera.hpp"

Camera::Camera(
    Point3D lookfrom,
    Point3D lookat,
    Vec3D vup,
    double vfov,
    double ratio
    )
    : focal_length(1.0),
      vfov(vfov),
      aspect_ratio(ratio),
      origin(lookfrom)
{
  auto h = std::tan(vfov / 2);
  auto viewport_height = 2.0 * h;
  auto viewport_width = aspect_ratio * viewport_height;

  auto w = (lookfrom - lookat).normalize();
  auto u = cross(vup, w).normalize();
  auto v = cross(w, u);

  hori = viewport_width * u;
  vert = viewport_height * v;
  corner = origin - hori*0.5 - vert*0.5 - w;
}

Ray Camera::ray_to(double x, double y) const {
  return Ray{origin, corner + x * hori + y * vert - origin};
}
