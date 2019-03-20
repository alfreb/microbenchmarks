#include <iostream>
#include <vector>
#include <cstdint>
#include "exp.hpp"

using namespace std;

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
