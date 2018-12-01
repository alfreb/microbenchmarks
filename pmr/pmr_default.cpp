#include "buffer.hpp"
#include "malloc.h"
#include <vector>

struct Default_pmr : public std::pmr::memory_resource {
  void* do_allocate(std::size_t size, std::size_t align) override {
    return memalign(align, size);
  }
  
  void do_deallocate (void* ptr, size_t, size_t) override {
    std::free(ptr);
  }
  
  bool do_is_equal (const std::pmr::memory_resource& other) const noexcept override {
    if (const auto* underlying = dynamic_cast<const Default_pmr*>(&other))
      return true;
    return false;
  }
};

std::pmr::memory_resource* std::pmr::get_default_resource() noexcept {
  static Default_pmr* default_pmr;
  if (default_pmr == nullptr)
    default_pmr = new Default_pmr{};
  return default_pmr;
}
