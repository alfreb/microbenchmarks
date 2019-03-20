
__attribute__((noinline))
void task(int iterations) {
  volatile int i = 0;
  while(i < iterations) i++;
}

inline uint64_t cycles() noexcept {
  uint32_t hi, lo;
  asm("rdtscp" : "=a"(lo), "=d"(hi));
  return ((uint64_t) lo) | ((uint64_t) hi) << 32;
}
