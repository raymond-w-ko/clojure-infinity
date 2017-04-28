#include "cljvm_precompiled.h"
#include "cljvm_data_structures.h"
#include "cljvm_mem.h"

static void* plist_vtable[cljvm_number_of_vfuncs];

cljvm_plist* cljvm_plist_new(void* _meta, void* _first, void* _rest, size_t _count) {
  cljvm_plist* list = cljvm_malloc(sizeof(cljvm_plist));
  list->base.vtable = plist_vtable;
  list->_meta = _meta;
  list->_first = _first;
  list->_rest = _rest;
  list->_count = _count;
  return list;
}

void* cljvm_plist_next(cljvm_plist* thiz) {
  if (thiz->_count == 1) {
    return NULL;
  } else {
    return thiz->_rest;
  }
}

void* cljvm_plist_more(cljvm_plist* thiz) {
  cljvm_plist* s = cljvm_plist_next(thiz);
  if (s == NULL) {
    return cljvm_get_empty_plist();
  } else {
    return s;
  }
}

void* cljvm_plist_cons(cljvm_plist* thiz, void* item) {
  return cljvm_plist_new(thiz->_meta, item, thiz, thiz->_count + 1);
}

void cljvm_plist_init() {
  plist_vtable[cljvm_vfn_lookup_next] = cljvm_plist_next;
}
