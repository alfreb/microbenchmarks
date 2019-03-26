#include <vector>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

std::vector<uint64_t>& experiment(int tasksize = 1000, int task_count = 1000);

void usage(const char* prog) {
  std::cout << "Usage: \n" << prog << " task_size task_count \n";
  exit(42);
}


int main(int argc, char** argv){

  int task_size  = 60000;
  int task_count = 1000000;
  
  if (argc < 3) {
    //usage(argv[0]);
    printf("Using default params, %i, %i \n", task_size, task_count);
    
  } else {
      task_size  = std::atoi(argv[1]);
      task_count = std::atoi(argv[2]);
  }

  asm("cli");
  
  std::cout << "# Running " << task_size << " tasks of size " << task_count << "\n";
  
  auto t1 = std::chrono::high_resolution_clock::now();
  auto cycles = experiment(task_size, task_count);
  auto t2 = std::chrono::high_resolution_clock::now();

  auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

  for (auto i : cycles)
    std::cout << i << "\n";

  std::cout << "# Completed " << task_count << " experiments "
            << " in " << time_span.count() << " seconds \n";
}
