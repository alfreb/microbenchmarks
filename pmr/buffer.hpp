#if defined(USE_PMR)

#if __has_include("memory_resource")
#include <vector>
#include <memory>
#include <memory_resource>
#else
#include <experimental/memory_resource>
#include <experimental/vector>
namespace std {
  namespace pmr = std::experimental::pmr;
}
#endif

//#namespace stdx = std::experimental;

using Buf     = std::pmr::vector<uint8_t>;
using Buf_ptr = std::shared_ptr<Buf>;

inline const char* variant() { return "Buffer *with* pmr"; }

#elif defined(USE_STD_ALLOC)
#warning "using std::allocator"
#include <vector>
#include <memory>
using Buf     = std::vector<uint8_t, std::allocator<uint8_t>>;
using Buf_ptr = std::shared_ptr<Buf>;

inline const char* variant() { return "Buffer with std::allocator"; }

#else // NON-PMR

#include <vector>
#include <memory>

using Buf     = std::vector<uint8_t>;
using Buf_ptr = std::shared_ptr<Buf>;

inline const char* variant() { return "Buffer *without* pmr"; }

#endif


