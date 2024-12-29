#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPPERLIMIT 1000000000000LL

// Function that takes an integer and its root and returns if its flawless
bool isFlawless(long long root, long long number) {
  for (int power10 = 10;; power10 *= 10) {
    long long quotient = number / power10;   // left part
    long long remainder = number % power10;  // right part
    // If root < remainder there is no point in continuing
    // since we want remainder + something to be equal to root
    if (root < remainder) return false;
    // if quo + rem < root - prev_remainders then there is no point
    // in breaking quotient further since its not going to increase.
    // So we try breaking it in a different way by increasing the power of 10
    if (quotient + remainder < root) continue;
    // If we found a combination that equals root, number is flawless
    if (quotient + remainder == root) return true;
    // If quotient single digit we've reached the end of the number
    // and we haven't found it, so return false
    if (quotient <= 9) return false;
    // Call recursively to break the number further, removing the remainder
    // from root, taking it into account for the sum of the next iteration
    if (isFlawless(root - remainder, quotient)) return true;
  }
}

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Program needs to be called as `%s low high`\n", argv[0]);
    return 1;
  }
  // if number length is higher than 13, number is out of bounds
  if (strlen(argv[1]) > 13 || strlen(argv[2]) > 13) return 1;

  // Parsing command-line arguments and input validation
  long long low = strtoll(argv[1], NULL, 10);
  long long high = strtoll(argv[2], NULL, 10);

  if (high < low || low < 1 || high > UPPERLIMIT) return 1;

  long long root = 1, perfectSquare, sum = 0;

  // We check what's the smallest root^2 within range and start from there
  while (root * root < low) root++;

  // Instead of checking if number is perfect square we build them ourselves
  for (; (perfectSquare = root * root) <= high; root++) {
    // Mod trick explained in README
    if (root % 9 != perfectSquare % 9) continue;
    // if number is flawless add it to the sum
    if (isFlawless(root, perfectSquare)) sum += perfectSquare;
  }
  printf("%lld\n", sum);
  return 0;
}
