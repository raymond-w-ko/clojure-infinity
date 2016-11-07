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

#define CLJVM_CALL(NAME, OBJECT, ...) \
  ((cljvm_vfn_ ## NAME)OBJECT->vtable[cljvm_vfn_lookup_ ## NAME])(OBJECT, __VA_ARGS__);

int main() {
  cljvm_init();
  cljvm_object* s = (void*)cljvm_string_new("foobar", 6);
  
  /* example of calling a virtual function */
  size_t cnt = CLJVM_CALL(count, s);
  printf("string size: %zu\n", cnt);
  
  return 0;
}
