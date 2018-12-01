#include <cerrno>
#include <cstdlib>
#include <cstddef>
#include <cstdio>

void* memalign(size_t align, size_t size) {
  void* ptr {nullptr};

  if (align < sizeof(void*))
    align = sizeof(void*);
  if (size < sizeof(void*))
    size = sizeof(void*);

  int res = posix_memalign(&ptr, align, size);
  if (res == EINVAL)
    printf("Error %i: posix_memalign got invalid alignment param %zu \n", res, align);
  if (res == ENOMEM)
    printf("Error %i: posix_memalign failed, not enough memory  %zu \n", res, align);
  return ptr;
}
void* aligned_alloc(size_t align, size_t size) {
  return memalign(align, size);
}
