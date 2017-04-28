#include "precompiled.h"
#include "data_structures.h"
#include "mem.h"

static void* empty_plist_vtable[cljvm_number_of_vfuncs];
static cljvm_empty_plist* EMPTY = NULL;

/* ISeq interface */

void* empty_plist_first(cljvm_empty_plist* thiz) {
  return NULL;
}

void* empty_plist_next(cljvm_empty_plist* thiz) {
  return NULL;
}

void* empty_plist_more(cljvm_empty_plist* thiz) {
  return thiz;
}

void* empty_plist_cons(cljvm_empty_plist* thiz, void* item) {
  return cljvm_plist_new(thiz->_meta, item, NULL, 1);
}

size_t empty_plist_count(cljvm_empty_plist* thiz) {
  return 0;
}

void cljvm_empty_plist_init() {
  empty_plist_vtable[cljvm_vfn_lookup_first] = empty_plist_first;
  empty_plist_vtable[cljvm_vfn_lookup_next] = empty_plist_next;
  empty_plist_vtable[cljvm_vfn_lookup_more] = empty_plist_more;
  empty_plist_vtable[cljvm_vfn_lookup_cons] = empty_plist_cons;
  
  empty_plist_vtable[cljvm_vfn_lookup_count] = empty_plist_count;
  
  EMPTY = cljvm_perm_malloc(sizeof(cljvm_empty_plist));
  EMPTY->base.vtable = empty_plist_vtable;
}

cljvm_empty_plist* cljvm_get_empty_plist() {
  return EMPTY;
}
