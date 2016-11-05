#pragma once
#include "cljvm_precompiled.h"

/* all GC-able objects must have this as the first member */
typedef struct cljvm_object {
  void* vtable;
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

typedef struct cljvm_persistent_list {
  struct cljvm_object base;
  void* _meta;
  size_t _count;
  void* _first;
  void* _rest;
} cljvm_persistent_list;

typedef struct cljvm_persistent_hash_map {
  struct cljvm_object base;
  void* _meta;
  uint32_t datamap;
  uint32_t nodemap;
  size_t content_array_length;
  void* content_array[];
} cljvm_persistent_hash_map;

/* constructors */
cljvm_number* cljvm_number_new(double n);
cljvm_string* cljvm_string_new(const char* str, size_t len);
