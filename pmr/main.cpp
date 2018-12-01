#include "buffer.hpp"

void flush(Buf_ptr buf);
void print_status();

size_t count = 1000;
size_t packetsize = 1500;

// Allocate N chunks of data, write to them and flush to external function.
int main(int argc, char** args){

  if (argc > 1)
    count = std::atoi(args[1]);

  if (argc > 2)
    packetsize = std::atoi(args[2]);
  
  printf("Running %zu packets using %s \n", count, variant());
  
  for (int i = 0; i < count; i++) {
    auto buf = std::make_shared<Buf>(1500l, '!');
    flush(buf);
  }
  
  print_status();
}
