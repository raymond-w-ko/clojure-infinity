#include "cljvm_precompiled.h"
#include "cljvm_data_structures.h"
#include "cljvm_mem.h"

static void* boolean_vtable[cljvm_number_of_vfuncs];
/*  */
static cljvm_boolean* cljvm_true = NULL;
static cljvm_boolean* cljvm_false = NULL;

cljvm_boolean* cljvm_get_false() {
  return cljvm_false;
}

cljvm_boolean* cljvm_get_true() {
  return cljvm_true;
}

cljvm_boolean* cljvm_boolean_new(int boolean) {
  cljvm_boolean* b = cljvm_perm_malloc(sizeof(cljvm_boolean));
  b->base.vtable = boolean_vtable;
  b->_boolean = boolean;
  return b;
}

int32_t cljvm_boolean_hasheq(void* thiz) {
  cljvm_boolean* b = thiz;
  return b->_boolean ? 1231 : 1237;
}

void cljvm_boolean_init() {
  boolean_vtable[cljvm_vfn_lookup_hasheq] = cljvm_boolean_hasheq;
  
  cljvm_false = cljvm_boolean_new(0);
  cljvm_true = cljvm_boolean_new(1);
}
