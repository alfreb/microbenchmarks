#include "buffer.hpp"

#define UNLIKELY(X) __builtin_expect(!!(X), 0)

Buf buf(1500l, '!');

ssize_t passed = 0;
ssize_t failed = 0;


void flush(Buf_ptr b) {

  if (UNLIKELY(*b != buf)) {
    failed++;
    throw std::runtime_error("Buffer had incorrect data \n");
  }

  passed++;
}

void print_status() {
  printf("Flush: buffers passed: %zu buffers failed: %zu \n", passed, failed);
}
