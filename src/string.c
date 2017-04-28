#include "precompiled.h"
#include "data_structures.h"
#include "mem.h"

static void* string_vtable[cljvm_number_of_vfuncs];

cljvm_string* cljvm_string_new(const char* str, size_t str_len) {
  size_t obj_len = sizeof(cljvm_string) + str_len + 1;
  cljvm_string* s = cljvm_malloc(obj_len);
  s->base.vtable = string_vtable;
  s->_count = str_len;
  s->_hash = 0;
  /* override const to write bytes */
  uint8_t* bytes = (void*)s->_value;
  memcpy(bytes, str, str_len);
  bytes[str_len] = '\0';
  return s;
}

size_t cljvm_string_count(cljvm_string* thiz) {
  return thiz->_count;
}

void cljvm_string_init() {
  string_vtable[cljvm_vfn_lookup_count] = cljvm_string_count;
}
