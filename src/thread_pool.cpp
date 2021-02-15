#include "thread_pool.hpp"

void ThreadPool::add(const T &job) {
  jobs[ptr].push_back(job);
  ptr = (ptr + 1) % N;
}
void ThreadPool::work() {
  std::vector<std::thread> workers;
  for (int i = 0; i < N; i++) {
    workers.push_back(std::thread{[&, i]() {
      for (auto &j : jobs[i]) {
        j();
      }
    }});
  }
  for (auto &worker : workers) {
    worker.join();
  }
}
