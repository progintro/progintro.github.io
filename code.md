# Κώδικας Διαλέξεων

## perfect.c - Credit: Στέφανος

```c
// Program to compute the sum of perfect squares up to a point.
#include <stdio.h>

int main(int argc, char ** argv) {
  long long int threshold = 540000;
  long long int i;
  long long sum = 0;
  for(i = 1; i <= threshold; i+=2) {
     sum += i * i;
     printf("Intermediate value: %lld\n", i * i);
  }
  printf("Sum: %lld\n", sum);
  return 0;

}
```

## grade.c - Credit: Γιάννης

```c
#include <stdio.h>
#include <stdlib.h>

/*
  Computes the grade for a first year student
  following the formula published on progintro.github.io
*/
int grade (int final_exam,int homework,int lab) {
        return 0.5*final_exam+0.3*homework+0.2*lab;
}

int main(int argc, char ** argv) {
  printf("Argc: %d\n", argc);
  printf("My argv[0] is: %s\n", argv[0]);
  printf("size of int: %zu\n", sizeof(int));
  printf("size of long int: %zu\n", sizeof(long int));

  double x = 5 / 2;
  printf("Double: %f\n", x);

  if (argc != 4) {
     printf("Usage: ./grade <final_exam> <homework> <lab>\n");
     return 1;
  }

  int final_exam = atoi(argv[1]);
  printf("Final exam: %d\n", final_exam);
  int homework = atoi(argv[2]);
  int lab = atoi(argv[3]);

  int final_grade = grade(final_exam, homework, lab);
  printf("My final grade is: \n", final_grade);
//  printf("Test: %d\n", (int)42.42);

  return 0;
}
```
