#include <iostream>
#include <vector>
#include <cstdint>


using namespace std;

__attribute__((noinline))
void task(int iterations) {
  volatile int i = 0;
  while(i < iterations) i++;
}

inline uint64_t cycles() noexcept {
  uint32_t hi, lo;
  asm("rdtsc" : "=a"(lo), "=d"(hi));
  return ((uint64_t) lo) | ((uint64_t) hi) << 32;
}

std::vector<uint64_t> cycle_counter;


std::vector<uint64_t>& experiment(int task_size = 1000, int task_count = 1000) {
  
  // Reserve memory for counters in advance
  cycle_counter.reserve(task_count * sizeof(decltype(cycle_counter)::value_type));
  
  // Execute task_count tasks of task_size  
  for (int i = 0; i < task_count; i++) {
    auto t1 = cycles();
    task(task_size);
    auto t2 = cycles();
    cycle_counter.push_back(t2 - t1);
  }

  return cycle_counter;
}
