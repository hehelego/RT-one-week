#include "common.hpp"

bool isnan(const double x) { return std::isnan(x); }
bool iszero(const double x) { return fabs(x) < EPS; }

static std::mutex rand_lock;
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<double> dis(0, 1);
double rand_01() {
  std::lock_guard guard(rand_lock);
  return dis(gen);
}
double rand_lr(const double l, const double r) {
  return l + (r - l) * rand_01();
}
