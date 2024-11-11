# Κώδικας Διαλέξεων

## Hello world - hello.c - lec00

```c
/* File: hello.c */
#include <stdio.h>

int main() {
  printf("Hello world\n");
  return 0;
}
```

## Τύπωμα μεταβλητών - format.c - lec03

```c
#include <stdio.h>

int main() {
  int x = 42;
  float pi = 3.14;
  char c = 'C';
  printf("Results: %d %f %c\n", x, pi, c);
  printf("Results: %d %f %c\n", x + 1, pi + 1, c + 1);
  return 0;
}
```

## Υπολογισμός Βαθμολογίας - grade.c - lec04

Credits: Άρτεμις

```c
#include <stdio.h>
#include <stdlib.h>

// The grade function computes the final grade
// for first year students according to
// https://progintro.github.io
int grade(int final_exam, int homework, int lab){
  return final_exam*50/100+homework*30/100+lab*20/100;
}

int main(int argc, char ** argv) {
  if (argc != 4) {
	printf("Run as: grade final_exam homework lab\n");
	return 1;
  }
  int final_exam = atoi(argv[1]);
  int homework = atoi(argv[2]);
  int lab = atoi(argv[3]);
  int final_grade = grade(final_exam, homework, lab);
  printf("My grade is: %d\n", final_grade);
  return 0;
}
```

## Prefix vs postfix operators - lec05

```c
#include <stdio.h>
int main() {
  int x = 42, y = 42;
  printf("%d %d\n", x++, ++y);
}
```

## Rounding function & ternary operator - lec05

Credits: Τάσος και Φώτης

```c
#include <stdio.h>

int myround(double x) {
  int first = (int) x;
  double result = (x - first >= 0.5) ? first + 1 : first;
  return result;
}

int main() {
   printf("%d\n", myround(42.67));
   printf("%d\n", myround(42.499999));
   printf("%d\n", myround(42.99));
   printf("%d\n", myround(42.50000001));
   return 0;
}
```

## Conditionals and max/min computation - lec05

```c
#include <stdio.h>

int main() {
  int x = 43, y = 42;
  int max, min;
  if (x > y) {
         max = x;
         min = y;
  } else {
         max = y;
         min = x;
  }
  printf("%d, %d", min, max);
  return 0;
}
```

## Loops and solving pythagorean triplets - lec07

Credits: Γιώργος

```c
/* Program to compute the sole pythagorean
   triplet where a + b + c == 1000. Implements
   the solution to https://projecteuler.net/problem=9
*/

#include <stdio.h>

int main() {
  // For each combination of a, b, c check
  // whether the conditions a + b + c == 1000
  // and a^2 + b^2 == c^2 are met
  for (int a = 1; a <= 1000; a++) {
    for (int b = 1; b <= 1000; b++) {
      for (int c = 1; c <= 1000; c++) {
        if ((a < b) && (b < c) && (a * a + b * b == c * c) &&
            (a + b + c == 1000)) {
          printf("a: %d\nb: %d\nc: %d\n", a, b, c);
          printf("abc:%d\n", a * b * c);
          return 0;
        }
      }
    }
  }
  return 0;
}
```

## Using break and scanf - lec08

```c
/* A small bus simulator that continues to
   pick up passengers and report how many
   are at each stop. */
#include <stdio.h>

int main() {
  int new_passengers, passengers = 0;
  int items_read;
  while (1) {
    printf("How many passengers are going on the bus: ");
    items_read = scanf("%d", &new_passengers);
    if (items_read == 0 || items_read == EOF) {
      break;
    }
    printf("Items read: %d\n", items_read);
    passengers += new_passengers;
    printf("Now we have %d total passengers\n", passengers);
  }
  return 0;
}
```

## Array Initialization, using rand and finding max - lec10

Credits: Αλέξανδρος

```c
/* Small utility demonstrating the use of srand, rand,
   array initialization and looping through array elements
   to produce a metric (max element in this case).
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int bears[100];
  int i;
  int max;
  // First initialize all array values to random integers
  //  srand(time(NULL));
  srand(100);
  for(i = 0; i < 100; i++) {
    bears[i] = rand();
  }
  // Print out all integers
  for(i = 0; i < 100; i++) {
    printf("%d ", bears[i]);
  }
  printf("\n");
  // Find and the maximum integer
  max = bears[0];
  for(i = 1; i < 100; i++) {
    if(max < bears[i]) {
      max = bears[i];
    }
  }
  printf("Max found: %d\n", max);

  // things can go wrong when you write out of bounds:
  // bears[120000] = 42;
  // printf("All good %d\n", bears[120]);
  // printf("All good %d\n", bears[100]);

  return 0;
}
```

## Υπολογισμός παραγοντικού / factorial - χρήση αναδρομής - lec11

Credits: Στέφανος

```c
/* Short program for computing the factorial
   of a number. Does not handle edge-cases
   like negative numbers. */
#include <stdio.h>
#include <stdlib.h>

int factorial(int num) {
  printf("Computing: factorial(%d)\n", num);
  if (num <= 1) {
    return 1;
  } else {
    return num * factorial(num - 1);
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    printf("Run this program as ./factorial <num>\n");
    return 1;
  }
  int num = atoi(argv[1]);
  printf("The factorial of this number is: %d\n", factorial(num));
  return 0;
}
```


