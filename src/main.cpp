#include "camera.hpp"
#include "common.hpp"
#include "hittable.hpp"
#include "hittable_objects.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "vec.hpp"
#include "thread_pool.hpp"

RGBcolor ray_color(const Ray &r, const HittableList &objs, int depth = 0) {
  if (depth >= ReflectDepLim) {
    return RGBcolor{0, 0, 0};
  }

  // hit some object
  const auto opt_hit = objs.hit(r, EPS, INF);
  if (opt_hit.has_value()) {
    const auto &rec = opt_hit.value();
    const auto scattered = rec.material()->scatter(r, rec);
    if (scattered.has_value()) {
      const auto refl = scattered.value();

      const auto [r0, g0, b0] = ray_color(refl, objs, depth + 1).as_tuple();
      const auto [r1, g1, b1] = rec.material()->albedo().as_tuple();
      return RGBcolor{r0 * r1, g0 * g1, b0 * b1};
    } else { // totally absorbed
      return RGBcolor{0, 0, 0};
    }
  }

  // backgroud
  const auto dir = r.dir().normalize();
  const auto t = (dir[1] + 1) * 0.5;
  return (1 - t) * RGBcolor{1, 1, 1} + t * RGBcolor{0.5, 0.7, 1};
}
RGBcolor result[Height][Width];
void render_row(const Camera &cam, const HittableList &objs, int y,
                RGBcolor *output) {
  for (int x = 0; x < Width; x++) {
    auto color = RGBcolor{0, 0, 0};
    for (int s = 0; s < RandomSamples; s++) {
      auto u = (x + rand_01()) / Width;
      auto v = (y + rand_01()) / Height;
      color = color + ray_color(cam.ray_to(u, v), objs, 0);
    }
    color = color * (1.0 / RandomSamples);
    color = gamma_corr(color);
    output[x] = color;
  }
  std::cerr << "finished row "+std::to_string(y)+"\n";
}
void output() {
  std::cout << "P3\n" << Width << ' ' << Height << "\n255\n";
  for (int y = Height - 1; y >= 0; y--) {
    for (int x = 0; x < Width; x++) {
      const auto &color = result[y][x];
      std::cout << color_string(color) << "\n";
    }
  }
  std::cout << "\n\nEND OF THE PPM FILE" << std::flush;
}

HittableList random_scene() {
  using namespace std;
  using namespace Objects;
  using namespace Materials;
  auto objs = HittableList{};

  auto ground_material = make_shared<Diffuse>(RGBcolor{0.5, 0.5, 0.5});
  objs.add(make_shared<Sphere>(Point3D{0, -1000, 0}, 1000, ground_material));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = rand_01();
      auto center = Point3D{a + 0.9 * rand_01(), 0.2, b + 0.9 * rand_01()};

      if ((center - Point3D{4, 0.2, 0}).norm() > 0.9) {
        shared_ptr<Material> sphere_material;

        if (choose_mat < 0.8) {
          auto albedo = RGBcolor{rand_01(), rand_01(), rand_01()};
          sphere_material = make_shared<Diffuse>(albedo);
          objs.add(make_shared<Sphere>(center, 0.2, sphere_material));
        } else if (choose_mat < 0.95) {
          auto albedo =
              RGBcolor{rand_lr(0.5, 1), rand_lr(0.5, 1), rand_lr(0.5, 1)};
          auto fuzz = rand_lr(0, 0.5);
          sphere_material = make_shared<Metal>(albedo, fuzz);
          objs.add(make_shared<Sphere>(center, 0.2, sphere_material));
        } else {
          sphere_material = make_shared<Dielectric>(1.5);
          objs.add(make_shared<Sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = make_shared<Dielectric>(1.5);
  objs.add(make_shared<Sphere>(Point3D{0, 1, 0}, 1.0, material1));
  auto material2 = make_shared<Diffuse>(RGBcolor{0.4, 0.2, 0.1});
  objs.add(make_shared<Sphere>(Point3D{-4, 1, 0}, 1.0, material2));
  auto material3 = make_shared<Metal>(RGBcolor{0.7, 0.6, 0.5}, 0.0);
  objs.add(make_shared<Sphere>(Point3D{4, 1, 0}, 1.0, material3));
  return objs;
}
HittableList test_sceen() {
  using std::make_shared;
  using P = Point3D;
  using S = Objects::Sphere;
  using color = RGBcolor;
  using namespace Objects;
  using namespace Materials;
  HittableList world;
  auto material_ground = make_shared<Diffuse>(color(0.8, 0.8, 0.0));
  auto material_center = make_shared<Diffuse>(color(0.1, 0.2, 0.5));
  auto material_left = make_shared<Dielectric>(1.5);
  auto material_right = make_shared<Metal>(color(0.8, 0.6, 0.2), 0.0);

  world.add(make_shared<S>(P(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<S>(P(0.0, 0.0, -1.0), 0.5, material_center));
  world.add(make_shared<S>(P(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(make_shared<S>(P(1.0, 0.0, -1.0), 0.5, material_right));

  return world;
}

int main() {
  std::ios::sync_with_stdio(0);

  const auto objs = random_scene();
  const auto cam = Camera{Point3D{13, 2, 3}, Point3D{0, 0, 0}, Vec3D{0, 1, 0}, PI / 2, AspectRatio};
  // const auto objs = test_sceen();
  // const auto cam = Camera{Point3D{-2, 2, 1}, Point3D{0, 0, -1}, Vec3D{0, 1, 0}, PI/5, AspectRatio};

#ifndef EXEC_POLICE_SERIAL
  auto pool = ThreadPool{};
  for (int y = Height - 1; y >= 0; y--) {
    pool.add([=]() { render_row(cam, objs, y, result[y]); });
  }
  pool.work();
#else
  for (int y = Height - 1; y >= 0; y--) {
    render_row(cam, objs, y, result[y]);
  }
#endif
  output();
  return 0;
}
