#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "primes.h"

int main(int argc, const char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <number>\n", argv[0]);
    return 1;
  }

  char *end;
  errno = 0;

  ull n = strtoull(argv[1], &end, 10);

  if (errno) {
    perror("ERROR: could not parse n");
    return 1;
  } else if (end == argv[1]) {
    fprintf(stderr, "ERROR: %s is not a valid integer\n", end);
    return 1;
  } else if (n < 2) {
    fprintf(stderr, "ERROR: n must be at least 2\n");
    return 1;
  }

  ull *primes = n_primes(n);
  if (!primes) {
    fprintf(stderr, "ERROR: failed to find primes up to %lld\n", n);
    return 1;
  }

  printf("Found primes: ");
  for (ull *it = primes; *it; it++)
    printf("%lld ", *it);

  printf("\n");
  free(primes);

  return 0;
}
