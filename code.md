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
