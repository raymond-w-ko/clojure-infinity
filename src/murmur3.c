/*
 * Copyright (C) 2011 The Guava Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy
 * of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

/*
 * MurmurHash3 was written by Austin Appleby, and is placed in the public
 * domain. The author hereby disclaims copyright to this source code.
 */

/*
 * Source:
 * http://code.google.com/p/smhasher/source/browse/trunk/MurmurHash3.cpp
 * (Modified to adapt to Guava coding conventions and to use the HashFunction interface)
 */

/**
 * Modified to remove stuff Clojure doesn't need, placed under clojure.lang namespace,
 * all fns made static, added hashOrdered/Unordered
 */

/**
 * Modified yet again for the omni-clojure project
 */
#include "precompiled.h"


uint32_t rotate_left(uint32_t value, int shift) {
  return _rotl(value, shift);
}

static const uint32_t seed = 0;
static const uint32_t C1 = 0xcc9e2d51;
static const uint32_t C2 = 0x1b873593;

static uint32_t mix_k1(uint32_t k1) {
  k1 *= C1;
  k1 = rotate_left(k1, 15);
  k1 *= C2;
  return k1;
}

static uint32_t mix_h1(uint32_t h1, uint32_t k1) {
  h1 ^= k1;
  h1 = rotate_left(h1, 13);
  h1 = h1 * 5 + 0xe6546b64;
  return h1;
}

// Finalization mix - force all bits of a hash block to avalanche
static uint32_t fmix(uint32_t h1, uint32_t length) {
  h1 ^= length;
  h1 ^= h1 >> 16;
  h1 *= 0x85ebca6b;
  h1 ^= h1 >> 13;
  h1 *= 0xc2b2ae35;
  h1 ^= h1 >> 16;
  return h1;
}

uint32_t hash_int(uint32_t input) {
  if(input == 0) return 0;
  uint32_t k1 = mix_k1(input);
  uint32_t h1 = mix_h1(seed, k1);

  return fmix(h1, 4);
}

uint32_t hash_long(uint64_t input) {
  if(input == 0) return 0;
  uint32_t low = (uint32_t) input;
  uint32_t high = (uint32_t) (input >> 32);

  uint32_t k1 = mix_k1(low);
  uint32_t h1 = mix_h1(seed, k1);

  k1 = mix_k1(high);
  h1 = mix_h1(h1, k1);

  return fmix(h1, 8);
}

/*
int hash_unencoded_chars(CharSequence input){
  int h1 = seed;

  // step through the CharSequence 2 chars at a time
  for(int i = 1; i < input.length(); i += 2)
  {
    int k1 = input.charAt(i - 1) | (input.charAt(i) << 16);
    k1 = mix_k1(k1);
    h1 = mix_h1(h1, k1);
    }

  // deal with any remaining characters
  if((input.length() & 1) == 1)
    {
    int k1 = input.charAt(input.length() - 1);
    k1 = mix_k1(k1);
    h1 ^= k1;
    }

  return fmix(h1, 2 * input.length());
}

static int mix_coll_hash(int hash, int count){
  int h1 = seed;
  int k1 = mix_k1(hash);
  h1 = mix_h1(h1, k1);
  return fmix(h1, count);
}

static int hash_ordered(Iterable xs){
  int n = 0;
  int hash = 1;

  for(Object x : xs)
    {
    hash = 31 * hash + Util.hasheq(x);
    ++n;
    }

  return mixCollHash(hash, n);
}

static int hash_unordered(Iterable xs){
  int hash = 0;
  int n = 0;
  for(Object x : xs)
    {
    hash += Util.hasheq(x);
    ++n;
    } 

  return mixCollHash(hash, n);
}
*/
