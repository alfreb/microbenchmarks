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


int experiment(int task_size = 1000, int log_threshold = 1000) {
  
  
  // Execute task_count tasks of task_size  
  while (true) {
    auto t1 = cycles();
    task(task_size);
    auto t2 = cycles();
    int c = t2 - t1;
    if (c > log_threshold) {
      std::cout<<c <<"\n";
    }
  }

  return 0;
}
