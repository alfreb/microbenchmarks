#include <vector>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

std::vector<uint64_t>& experiment(int tasksize = 1000, int task_count = 1000);

void usage(const char* prog) {
  std::cout << "Usage: \n" << prog << " task_size log_threshold \n";
  exit(42);
}


int main(int argc, char** argv){

  if (argc < 3) {
    usage(argv[0]);
  }

  auto task_size  = std::atoi(argv[1]);
  auto log_threshold = std::atoi(argv[2]);

  std::cout << "# Running " << task_size << " with log_threshold " << log_threshold << "\n";

  auto t1 = std::chrono::high_resolution_clock::now();

  auto cycles = experiment(task_size, log_threshold);

  auto t2 = std::chrono::high_resolution_clock::now();

  auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

  for (auto i : cycles)
    std::cout << i << "\n";

  std::cout << "# Completed " << log_threshold << " experiments "
            << " in " << time_span.count() << " seconds \n";
}
