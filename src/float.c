#include "precompiled.h"
#include "data_structures.h"
#include "mem.h"

static void* float_vtable[cljvm_number_of_vfuncs];

cljvm_float* cljvm_float_new(double value) {
  cljvm_float* f = cljvm_malloc(sizeof(cljvm_float));
  f->base.vtable = float_vtable;
  f->value = value;
  return f;
}

/**
 * core hashing algorithm copied from JDK, hope they don't mind.
 * done to match Clojure proper hasheq()
 */
int32_t cljvm_float_hasheq(void* thiz) {
  cljvm_float* f = thiz;
  void* addr = &f->value;
  uint64_t bits = *((uint64_t*)addr);
  return (int32_t)(bits ^ (bits >> 32));
}

void cljvm_float_init() {
  float_vtable[cljvm_vfn_lookup_hasheq] = cljvm_float_hasheq;
}
