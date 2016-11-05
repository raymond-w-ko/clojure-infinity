#include "cljvm_precompiled.h"
#include "cljvm_data_structures.h"
#include "cljvm_mem.h"

static int string_vtable;

cljvm_string* cljvm_string_new(const char* str, size_t str_len) {
  size_t obj_len = sizeof(cljvm_string) + str_len + 1;
  cljvm_string* s = cljvm_malloc(obj_len);
  s->base.vtable = &string_vtable;
  s->_count = str_len;
  s->_hash = 0;
  memcpy(s->_value, str, str_len);
  s->_value[str_len] = '\0';
  return s;
}
