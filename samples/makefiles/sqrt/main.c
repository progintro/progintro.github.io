#include <stdio.h>
// #include <math.h> // comment this back in to fix compilation error
// try compiling with: gcc -o main main.c
// try compiling with: gcc -o main main.c -l:libm.so

int main(void) {
  double x = 3;
  printf("%.2f\n", sqrt(x));
  return 0;
}
