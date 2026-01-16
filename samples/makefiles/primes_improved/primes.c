#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "primes.h"

bool is_prime(ull n, ull *primes, size_t primes_sz) {
  for (size_t i = 0; i < primes_sz; i++) {
    if (n % primes[i] == 0)
      return false;
  }

  return true;
}

ull *insert_prime(ull n, ull *primes, size_t *primes_top, size_t *primes_sz) {
  if (*primes_top == *primes_sz) {
    // double the current size or if it's zero, give it a small size
    size_t new_sz = *primes_sz >= 1 ? 2 * *primes_sz : 2;
    void *tmp = reallocarray(primes, new_sz, sizeof(ull));

    // in case of failure, early return
    if (!tmp) {
      free(primes);
      return NULL;
    }

    primes = tmp;
    *primes_sz = new_sz;
  }

  primes[(*primes_top)++] = n;

  return primes;
}

ull *n_primes(ull n) {
  size_t primes_sz = 0;
  size_t primes_top = 0;
  ull *primes = NULL;

  for (ull i = 2; i < n; i++) {
    if (!is_prime(i, primes, primes_top))
      continue;

    if (!(primes = insert_prime(i, primes, &primes_top, &primes_sz)))
      return NULL;
  }

  return insert_prime(0, primes, &primes_top, &primes_sz);
}
