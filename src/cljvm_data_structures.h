#pragma once
#include "cljvm_precompiled.h"

/* all GC-able objects must have this as the first member */
typedef struct cljvm_object {
  void** vtable;
} cljvm_object;

typedef struct cljvm_number {
  struct cljvm_object base;
  double number;
} cljvm_number;

typedef struct cljvm_string {
  struct cljvm_object base;
  size_t _count;
  int32_t _hash;
  uint8_t _value[];
} cljvm_string;

typedef struct cljvm_boolean {
  struct cljvm_object base;
  /* excessive, but the GC's malloc allocates by 16 byte chunks anyways, so we
   * don't really save any space by using a char */
  size_t _boolean;
} cljvm_boolean;

typedef struct cljvm_plist {
  struct cljvm_object base;
  void* _meta;
  size_t _count;
  void* _first;
  void* _rest;
} cljvm_plist;

typedef struct cljvm_phash {
  struct cljvm_object base;
  void* _meta;
  uint32_t datamap;
  uint32_t nodemap;
  size_t content_array_length;
  void* content_array[];
} cljvm_phash;

/******************************************************************************
 * Virtual Functions
 *****************************************************************************/ 
typedef enum {
  cljvm_vfn_RESERVED = 0,
  cljvm_vfn_lookup_count,
  // Seq interface
  cljvm_vfn_lookup_first,
  cljvm_vfn_lookup_next,
  cljvm_vfn_lookup_more,
  // number of virtual functions
  cljvm_number_of_vfuncs,
} cljvm_vfunction;

typedef size_t (*cljvm_vfn_count)(void* thiz);

/******************************************************************************
 * init functions
 *****************************************************************************/ 
void cljvm_string_init();
void cljvm_plist_init();
void cljvm_empty_plist_init();

cljvm_number* cljvm_number_new(double n);

cljvm_string* cljvm_string_new(const char* str, size_t len);

cljvm_plist* cljvm_plist_new(void* _meta, void* _first, cljvm_plist* _rest, size_t _count);
