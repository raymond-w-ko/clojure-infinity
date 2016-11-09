#include "cljvm_precompiled.h"
#include "cljvm_data_structures.h"
#include "cljvm_murmur3.h"

void debug_print_size() {
  printf("cljvm_string %zd\n", sizeof(cljvm_string));
  printf("cljvm_plist %zd\n", sizeof(cljvm_plist));
}

void cljvm_init() {
  cljvm_float_init();
  cljvm_string_init();
  cljvm_plist_init();
  cljvm_empty_plist_init();
}

/* clang-format off */
#define CLJVM_CALL(NAME, OBJECT, ...)                                            \
  (                                                                              \
    (cljvm_vfn_ ## NAME)                                                         \
    (                                                                            \
      ((void**)(((size_t)((cljvm_object*)OBJECT)->vtable) & (((size_t)-1) - 1))) \
      [cljvm_vfn_lookup_ ## NAME]                                                \
    )                                                                            \
  )                                                                              \
  (OBJECT, __VA_ARGS__);
/* clang-format on */

int cljvm_get_gray(void* obj) {
  return *((size_t*)obj) & 0b1;
}

void cljvm_set_gray(void* obj, unsigned int flag) {
  size_t* p = obj;
  size_t vtable_ptr = *p;
  *p = vtable_ptr | flag;
}

void test_vtable() {
  cljvm_object* s = (void*)cljvm_string_new("foobar", 6);
  /* example of calling a virtual function */
  size_t cnt = CLJVM_CALL(count, s);
  printf("string size: %zu\n", cnt);
}

void test_gray_bit() {
  cljvm_object* s = (void*)cljvm_string_new("foobar", 6);
  printf("get_gray(): %d\n", cljvm_get_gray(s));
  
  cljvm_set_gray(s, 1);
  
  size_t cnt = CLJVM_CALL(count, s);
  printf("string size: %zu\n", cnt);
  
  printf("get_gray(): %d\n", cljvm_get_gray(s));
  cljvm_set_gray(s, 0);
  printf("get_gray(): %d\n", cljvm_get_gray(s));
  size_t cnt2 = CLJVM_CALL(count, s);
  printf("string size: %zu\n", cnt2);
}

void test_hash() {
  uint64_t h = hash_long(42);
  printf("murmur(42) = %lld\n", h);
}

int main() {
  cljvm_init();
  
  void* obj = cljvm_float_new(3.14159);
  int32_t h = CLJVM_CALL(hasheq, obj);
  printf("hasheq(3.14) = %d\n", h);
  
  return 0;
}
