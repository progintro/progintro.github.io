#ifndef UTILS_H
#define UTILS_H

#include "types.h"

// clear a bit at position n
static inline void clear_bit(U64 *c, int n) {
    *c &= ~((U64)1 << n);
}

// enable (set) a bit at position n
static inline void enable_bit(U64 *c, int n) {
    *c |= ((U64)1 << n);
}

// check if a bit at position n is set (returns 1 if set, 0 if not)
static inline int is_set_bit(U64 c, int n) {
    return (c >> n) & 1;
}

// get the LSB index
static inline int lsb(U64 c) {
    return __builtin_ctzll(c);
}

// pop the LSB and return its index
static inline int pop_lsb(U64 *c) {
    int n = lsb(*c);
    clear_bit(c, n);
    return n;
}

// pop count
static inline int pop_count(U64 c) {
    return __builtin_popcountll(c);
}

#endif
