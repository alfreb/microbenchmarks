#include <vector>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <smp>
#include <debug>
#include <map>

#include <tinf.h>

extern "C" void kprintf(...);

std::vector<uint64_t>& experiment(int tasksize = 1000, int task_count = 1000);

void usage(const char* prog) {
  std::cout << "Usage: \n" << prog << " task_size task_count \n";
  exit(42);
}

int task_size  = 400;
int task_count = 100;

using Histogram = std::map<uint64_t,int64_t>;
using Plot      = std::vector<uint64_t>;

Histogram histogram(std::vector<uint64_t>& input) {

  Histogram h;
  
  for(auto& i : input) {
    h[i]++;
  }

  return h;
}

void print_data(Plot::iterator begin, Plot::iterator end) {
  
  for (auto it = begin; it != end; it++) {
    printf("%zu\n", *it);
  }
  
}

void print_hist(Histogram hist) {

  Histogram::mapped_type data_points = 0;
    
  for (auto[cycles, count] : hist) {
    printf("%zu : %li \n", cycles, count);
    data_points += count;
  }

  printf("\n%zu data points total, %zu unique values\n", data_points, hist.size());
  
}

int main(int argc, char** argv){
  
  //GDB_ENTRY;

  if (argc < 3) {
    //usage(argv[0]);
    printf("Using default params, %i, %i \n", task_size, task_count);
    
  } else {
    task_size  = std::atoi(argv[1]);
    task_count = std::atoi(argv[2]);
  }

  

  SMP::add_task([]{

      volatile int lead_in = std::numeric_limits<int>::max();
      while (lead_in--);

      printf("Multicore test starting on core %i \n", SMP::cpu_id());

      
      // asm("cli");
      printf("# Running %i tasks of size %i \n", task_count, task_size);
      
      auto t1 = std::chrono::high_resolution_clock::now();  
      auto cycles = experiment(task_size, task_count);
      auto t2 = std::chrono::high_resolution_clock::now();      
      
      auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);


      printf("# First 10 data points: \n");
      print_data(cycles.begin(), cycles.begin() + 10);
      printf("# Last 10 data points: \n");
      print_data(cycles.end() - 10, cycles.end());      

      printf("# Histogram: \n");
      print_hist(histogram(cycles));

      if (task_count <= 1000000) {
	printf("# All %zu data points \n", cycles.size());
	print_data(cycles.begin(), cycles.end());	
      }
      
      //uzlib_compress(void *data, const uint8_t *src, unsigned slen);
      
      
      printf("# Completed %i experiments in %f seconds \n", task_count, time_span.count());
      
    }, 2);

  SMP::signal();
  
}
