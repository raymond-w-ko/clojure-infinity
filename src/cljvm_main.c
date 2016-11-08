#include "cljvm_precompiled.h"
#include "cljvm_data_structures.h"

void debug_print_size() {
  printf("cljvm_string %zd\n", sizeof(cljvm_string));
  printf("cljvm_plist %zd\n", sizeof(cljvm_plist));
}

void cljvm_init() {
  cljvm_string_init();
  cljvm_plist_init();
  cljvm_empty_plist_init();
}

/* clang-format off */
#define CLJVM_CALL(NAME, OBJECT, ...)                             \
  (                                                               \
    (cljvm_vfn_ ## NAME)                                          \
    (                                                             \
      ((void**)(((size_t)OBJECT->vtable) & (((size_t)-1) - 1)))  \
      [cljvm_vfn_lookup_ ## NAME]                                 \
    )                                                             \
  )                                                               \
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

int main() {
  cljvm_init();
  cljvm_object* s = (void*)cljvm_string_new("foobar", 6);
  
  printf("get_gray(): %d\n", cljvm_get_gray(s));
  
  cljvm_set_gray(s, 1);
  
  /* example of calling a virtual function */
  size_t cnt = CLJVM_CALL(count, s);
  printf("string size: %zu\n", cnt);
  
  printf("get_gray(): %d\n", cljvm_get_gray(s));
  cljvm_set_gray(s, 0);
  printf("get_gray(): %d\n", cljvm_get_gray(s));
  size_t cnt2 = CLJVM_CALL(count, s);
  printf("string size: %zu\n", cnt2);
  
  return 0;
}
