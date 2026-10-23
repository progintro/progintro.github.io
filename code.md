# Κώδικας Διαλέξεων

<!-- TODO(2026-27) -->

_Ο κώδικας των διαλέξεων θα προστίθεται εδώ καθώς προχωρά το μάθημα._
_Ο κώδικας του περασμένου έτους είναι [εδώ](/past/2025/assets/code.md)._

## lec03

```c
#include <stdio.h>
#include <math.h>

/* A program for computing the area of a square triangle.
   Credit: Konstantinos
*/

float embadon(float a, float b){
        return a*b/2;
}

float hypotenuse(float a, float b) {
  return sqrt(a * a + b * b);
}


int main() {
  float result = embadon(3.5,4.8937489);
  printf("The area of a triangle with sides %d and %d is %f\n", 3, 4, result);
  return 0;
}
```

## lec07

```c

/* This is a program that helps add odd square numbers up to a
   certain limit as part of our projecteuler sign up.

   We include two separate solutions that we came up with incrementally.
   We observed that solution2 is significantly faster than solution1.

   Compile with `gcc -o square square.c -lm`

   Credits: Orfeas
*/


#include <stdio.h>
#include <math.h>

#define LIMIT 10000

void solution1() {

  unsigned long long number = 1;
  unsigned int cnt = 0;
  unsigned long long sum = 0;
  
  while(cnt < LIMIT){
        long long int root = sqrt(number);
        // is this a square number, we first take the square root
        // and check if the result matches
        if(root * root == number) { 
            //printf("This is a square number: %lld\n", number);
            cnt++;
            if(number % 2 == 1) {
                 sum += number;
            }
        }
        // printf("Number: %d, root: %d\n", number, root);
	     ++number;
  }

  printf("Found %d odd square numbers, sum: %llu\n", cnt, sum);
}

void solution2() {
  unsigned long long number = 1;
  unsigned int cnt = 0;
  unsigned long long sum = 0;

  // generate all square numbers up to the limit and add only the odd ones  
  while(number <= LIMIT){
        if (number * number % 2 == 1) {
            sum += number * number;
        }
	++number;
  }
  printf("Found %d odd square numbers, sum: %llu\n", cnt, sum);
}

int main() {
  // solution1();
  solution2();
  return 0;
}

```
