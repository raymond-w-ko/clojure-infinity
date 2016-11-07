#include "cljvm_precompiled.h"
#include "cljvm_data_structures.h"
#include "cljvm_mem.h"

static void* plist_vtable[cljvm_number_of_vfuncs];

static cljvm_plist* EMPTY = NULL;

cljvm_plist* cljvm_plist_new(void* _meta, void* _first, cljvm_plist* _rest, size_t _count) {
  cljvm_plist* list = cljvm_malloc(sizeof(cljvm_plist));
  list->base.vtable = plist_vtable;
  list->_meta = _meta;
  list->_first = _first;
  list->_rest = _rest;
  list->_count = _count;
  return list;
}

cljvm_plist* cljvm_plist_next(cljvm_plist* thiz) {
  if (thiz->_count == 1) {
    return NULL;
  } else {
    return thiz->_rest;
  }
}

cljvm_plist* cljvm_plist_more(cljvm_plist* thiz) {
  cljvm_plist* s = cljvm_plist_next(thiz);
  if (s == NULL) {
    return EMPTY;
  } else {
    return s;
  }
}

void cljvm_plist_init() {
  plist_vtable[cljvm_vfn_lookup_next] = cljvm_plist_next;
}

/**
 * interned empty list
 */

void cljvm_empty_plist_init() {
  EMPTY = cljvm_plist_new(NULL, NULL, NULL, 0);
}
