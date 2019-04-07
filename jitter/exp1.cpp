#include <iostream>
#include <vector>
#include <cstdint>
#include "exp.hpp"

using namespace std;

std::vector<uint64_t> cycle_counter;

std::vector<uint64_t>& experiment(int task_size = 1000, int task_count = 1000) {
  
  // Reserve memory for counters in advance
  cycle_counter.resize(task_count, 0);
  
  // Execute task_count tasks of task_size  
  for (int i = 0; i < task_count; i++) {
    auto t1 = cycles_start();
    task(task_size);
    auto t2 = cycles_end();
    auto res = t2 - t1;
    cycle_counter[i] = t2 - t1;
  }

  return cycle_counter;
}
