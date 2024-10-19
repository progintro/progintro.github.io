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
