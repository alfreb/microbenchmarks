
inline void task(int iterations) {
  volatile int i = 0;
  while(i < iterations) i++;
}


// From recommendations in Section 3.2.1 in
// https://www.intel.com/content/dam/www/public/us/en/documents/white-papers/ia-32-ia-64-benchmark-code-execution-paper.pdf

inline uint64_t cycles_start() noexcept {
  uint32_t cycles_high, cycles_low;
  asm volatile ("CPUID\n\t"
		"RDTSC\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
		"%rax", "%rbx", "%rcx", "%rdx");
  return ((uint64_t) cycles_low) | ((uint64_t) cycles_high) << 32;
}

inline uint64_t cycles_end() noexcept {
  uint32_t cycles_high, cycles_low;
  asm volatile ("RDTSCP\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
                "CPUID\n\t": "=r" (cycles_high), "=r" (cycles_low)::
                "%rax", "%rbx", "%rcx", "%rdx");
  return ((uint64_t) cycles_low) | ((uint64_t) cycles_high) << 32;
}


#define ASM_TASK_SIZE "50000"
#define STR(A) #A

inline void task_asm() {
  asm volatile(
    "mov $" ASM_TASK_SIZE ", %%rsi\n"
    ".task_asm_loop:\n"
    "dec %%rsi\n"
    "jnz .task_asm_loop\n"
    ::: "%rsi");
}

inline void task_dummy() { };
