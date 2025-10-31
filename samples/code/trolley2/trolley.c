// File: trolley.c
// Compile with:
//     gcc -O0 -m32 -Wall -Wextra -Werror -pedantic -o trolley trolley.c

// I added nice error handling with `strerror` but apparently the lab machines
// don't have `asm/errno.h`. I assume they are missing some/all headers from the
// 32-bit libc. Sigh... why are we even compiling with -m32? Getting rid of it
// seems to fix the issue anyway. :|
//
// When testing on machines where `errno.h` works, add the compile flag:
//     -DUSE_ERRNO=1
#ifdef USE_ERRNO
#include <errno.h>
#include <string.h> // strerror
#endif

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

// Convenient printing macros.
//
// Set -DNO_OUTPUT when compiling to completely disable printing. Useful for
// benchmarking without the overhead of either libc's internal buffering or a
// context switch caused by `write()`.
#ifdef NO_OUTPUT
#define print(...)
#define println(...)
#define eprint(...)
#define eprintln(...)
#else
// The ,##__VA_ARGS__ here is a gcc extension but most major compilers support
// it, so whatever.
#define print(fmt, ...) fprintf(stdout, fmt, ##__VA_ARGS__)
#define println(fmt, ...) print(fmt "\n", ##__VA_ARGS__)
#define eprint(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#define eprintln(fmt, ...) eprint(fmt "\n", ##__VA_ARGS__)
#endif

#define READ_OK 0
#define READ_EOF 1
#define READ_IO_ERR 2
#define READ_NOT_A_NUMBER 3

// Read an `int64_t` from `stream` and place it in `x`.
//
// Returns one of `READ_*`. Values self-explanatory.
static int read_int64(FILE *stream, int64_t *x) {
  int err;

  err = fscanf(stream, "%" SCNd64, x);

  // SAFETY: `fscanf` returns either `EOF` or a positive number indicating the
  // number of items it matched. We only specify 1 item, so `fscanf` can only
  // ever return `EOF`, 0 or 1.

  if (err == 1) {
    // fscanf matched 1 thing, our number
    return READ_OK;
  } else if (err == 0) {
    // fscanf matched nothing so the input was not a valid number
    return READ_NOT_A_NUMBER;
  } else if (ferror(stream)) {
    // err must be equal to `EOF`, we first check for IO errors
    return READ_IO_ERR;
  } else {
    // and if no IO error has occurred then we encountered EOF on
    // `stream`.
    return READ_EOF;
  }
}

int main(void) {
  int64_t cost_left, cost_right;

  while (1) {
    // The 2 blocks bellow could maybe have been abstracted out into another
    // function, but they have slight differences that are hard to reason about.
    // It is easier and clearer to just duplicate them with the appropriate
    // changes. Besides, the only duplicated logic is the error handling which
    // itself is really just a print with a return, nothing too fancy.

    print("Please enter the cost of going left: ");
    switch (read_int64(stdin, &cost_left)) {
    case READ_OK:
      break;

    // Encountering EOF on the left cost is not considered a failure as per the
    // requirements.
    case READ_EOF:
      println("Terminating.");
      return 0;

    case READ_IO_ERR:
#ifdef USE_ERRNO
      eprintln("Failed to read left cost from stdin: %s", strerror(errno));
#else
      eprintln("Failed to read left cost.");
#endif
      return 1;

    case READ_NOT_A_NUMBER:
      eprintln("Expected a number.");
      return 1;
    }

    print("Please enter the cost of going right: ");
    switch (read_int64(stdin, &cost_right)) {
    case READ_OK:
      break;

    // However, encountering EOF on the right cost IS a failure as
    // per the same requirements.
    case READ_EOF:
      println("No right cost provided.");
      return 1;

    case READ_IO_ERR:
#ifdef USE_ERRNO
      eprintln("Failed to read right cost from stdin: %s", strerror(errno));
#else
      eprintln("Failed to read right cost.");
#endif
      return 1;

    case READ_NOT_A_NUMBER:
      eprintln("Expected a number.");
      return 1;
    }

    // Requirements state that the autopilot system must choose the least
    // expensive path. In the case that both paths are equally expensive,
    // we arbitrarily choose the left path.
    if (cost_left <= cost_right) {
      println("Go left.");
    } else {
      println("Go right.");
    }
  }
}
