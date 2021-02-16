#ifndef __CG_COMMON_ONCE__
#define __CG_COMMON_ONCE__

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <optional>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <tuple>
#include <utility>
#include <vector>

const int Height = 1080;
const int Width = 1920;
const int ReflectDepLim = 40;
const int RandomSamples = 50;
const double AspectRatio = 1.0 * Width / Height;
const int ColorDepth = 8;
const int ColorLim = (1 << ColorDepth) - 1;
const double Gamma = 2;
const double EPS = 1e-8;
const double INF = 1e14;
const double PI = acos(-1.0);

extern bool isnan(const double x);
extern bool iszero(const double x);
extern double rand_01();
extern double rand_lr(const double l, const double r);

#endif
