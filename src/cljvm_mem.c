#include "cljvm_precompiled.h"
#include "cljvm_mem.h"

void* cljvm_malloc(size_t size) {
  return malloc(size);
}

void* cljvm_perm_malloc(size_t size) {
  return malloc(size);
}
