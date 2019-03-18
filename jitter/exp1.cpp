#include <iostream>
#include <vector>

using namespace std;


int iterations = 1000;

__attribute__((noinline))
void work() {
  volatile int i = 0;
  while(i < iterations) i++;  
}

inline uint64_t cycles() noexcept {
  uint32_t hi, lo;
  asm("rdtsc" : "=a"(lo), "=d"(hi));
  return ((uint64_t) lo) | ((uint64_t) hi) << 32;
}

std::vector<uint64_t> cycle_counter;


void experiment1(){

  for (int i = 0; i<iterations; i++) {
    auto t1 = cycles();    
    work();
    auto t2 = cycles();    
    cycle_counter.push_back(t2 - t1);
  }
  std::cout << "Measured " << cycle_counter.size() << "iterations \n";

  for (auto i : cycle_counter)
    std::cout << i << "\n";
    
}  


