#include "common.hpp"

class ThreadPool {
  using T = std::function<void()>;
  const int N = std::thread::hardware_concurrency();
  std::vector<std::vector<T>> jobs;
  int ptr;

public:
  ThreadPool() : jobs(N) {}
  void add(const T &job);
  void work();
};
