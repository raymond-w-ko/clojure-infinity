#include "cljvm_precompiled.h"
#include "cljvm_data_structures.h"

void debug_print_size() {
  printf("cljvm_string %zd\n", sizeof(cljvm_string));
  printf("cljvm_persistent_list %zd\n", sizeof(cljvm_persistent_list));
}

int main() {
  debug_print_size();
  cljvm_string* s = cljvm_string_new("foobar", strlen("foobar"));
  return 0;
}
