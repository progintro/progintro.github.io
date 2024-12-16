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

## Εκτύπωση command line arguments - lec12

```c
// Program expects *exactly* one argument (so 2 in total including its name)
// And then proceeds iterating through all of argv and printing them as strings.
#include <stdio.h>

int main(int argc, char * argv[]) {
  if (argc != 2) {
    printf("Usage: %s num1\n", argv[0]);
    return 1;
  }
  int i;
  for(i = 0 ; i < argc ; i++) {
    printf("%s\n", argv[i]);
  }
  return 0;
}
```

## Πράξεις με pointers - lec12

Credits: Δημήτρης και Δημήτρης

```c
// A small program to test how pointers behave
// and also how is an assignment expression
// evaluated in C.
#include <stdio.h>

int main() {
  int *p;
  int x[] = {5, 7, 2, 3, 6, 0, 1, 4};
  p = x;
  while (1) {
    printf("p: %p\n", p);
    printf("p + 2: %p\n", p + 2);
    printf("*p: %d\n", *p);
    printf("*(p+2): %d\n", *(p+2));
    printf("Value of *p = *(p+2): %d\n", *p = *(p+2));  // try to use +1000000000 instead of +2 and see what happens
    if (!(*p)) break;
    p++;
  }
  return 0;
}
```

## Δέσμευση δυναμικού πίνακα - lec13

```c
// Program that allocates and deallocates a 2D array of integers.

#include <stdio.h>
#include <stdlib.h>

int ** create_2d(int rows, int cols) {
  int ** array = malloc(rows * sizeof(int *));
  if (array == NULL) {
    perror("rows malloc");
    exit(1);
  }
  for(int i = 0; i < rows; i++) {
    array[i] = malloc(cols * sizeof(int));
    if (array[i] == NULL) {
      perror("cols malloc");
      exit(1);
    }
  }
  return array;
}

void free_2d(int ** array, int rows) {
  for(int i = 0; i < rows; i++) {
    free(array[i]);
  }
  free(array);
}

int main() {
  int ** array = create_2d(3, 4);
  array[0][0] = 1;
  free_2d(array, 3);
  return 0;
}
```

## Συγκρίνοντας δύο αλφαριθμητικά - lec14

```c
// Comparing two strings using strcmp vs comparing the pointers (i.e., addresses)
// of two strings. The result is very different.

#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {
  if (argc != 3) return 1;
  printf("strcmp(arg1, arg2): %d %d\n",
         strcmp(argv[1], argv[2]), argv[1] == argv[2]);
  return 0;
}
```

## Υπολογισμός του μέσου όρου στοιχείων πίνακα - lec15

Credits: Φώτης

```c
// Program to demonstrate finding the average of a
// number of elements in an array and allocating
// elements in different kinds of memory.

#include <stdio.h>
#include <stdlib.h>

double average(int *p, int n) {
  int sum = 0;
  for (int i = 0; i < n; i++)
    sum += *(p + i);

  double av = (double)sum / n;
  return av;
}

int main(int argc, char **argv) {
  int array[100];
  int *p = array;
  average(array, 100);

  int static_array[2][2];
  int *ptr_array[2];
  ptr_array[0] = malloc(2 * sizeof(int));
  ptr_array[1] = malloc(2 * sizeof(int));

  printf("static array: %p\n", static_array);
  printf("static array[0]: %p\n", static_array[0]);
  printf("ptr array: %p\n", ptr_array);
  printf("ptr array[0]: %p\n", ptr_array[0]);
}
```


## Βρίσκοντας τον Ν-οστό πρώτο αριθμό - lec15

Credits: Άρτεμις

```c
// A program for finding the n-th prime.
#include <stdio.h>
#include <stdlib.h>
long long int loops = 0;

int is_prime(int i) {
  int is_first = 1;
  for (int j = 2; j*j <= i; j++) {
    loops++;
    if (i % j == 0) {
      is_first = 0;
      break;
    }
  }
  return is_first;
}

int main(int argc, char **argv) {
  int counter = 0;
  int i = 2;
  int hold = 2;
  int max_prime = atoi(argv[1]);
  while (counter < max_prime) {
    if (is_prime(i) == 1) {
      counter++;
      hold = i;
    }
    i++;
  }
  printf("Prime number %d is %d\n", max_prime, hold);
  printf("Number of loops: %lld\n", loops);
  return 0;
}
```

## 1ο παράδειγμα χρήσης Valgrind - Guest Lecture 2/12

```c 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 3
#define M 2

int main(void)
{
    int **arr, i, j;
    arr = malloc(N * sizeof(int*));
    for (i = 0; i < N; ++i)
        arr[i] = malloc(M * sizeof(int));

    for (i = 0; i < N; ++i) {
        for (j = 0; j < M; ++j) {
            arr[i][j] = time(NULL);
            sleep(1);
        }
    }

    for (i = 0; i < N; ++i) {
        for (j = 0; j < M; ++j)
            printf("%d\t", arr[i][j]);

        printf("\n");
    }

    for (i = 0; i < N; i++)
        free(arr[i]);
    free(arr);

    return 0;
}
```

## 2ο παράδειγμα χρήσης Valgrind - Geust Lecture 2/12

### Αρχείο example2.c
```c
#include <stdio.h>
#include "primes.h"

int main(void)
{
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);
    printf("%d\n", count_of_prime_numbers(a, b));
    return 0;
}
```

### Αρχείο primes.c (προσπαθήστε να βρείτε & να λύσετε τα memleaks!)
```c 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "primes.h"

int64_t count_of_prime_numbers(int64_t from, int64_t to)
{
    if (from > to || from < 1 || to < 1) {
        printf("Wrong data\n");
        return -1;
    }

    uint8_t *primes = malloc((to + 1) * sizeof(uint8_t));
    if (primes == NULL) {
        printf("Malloc failed!\n");
        return -1;
    }

    memset(primes, 1, (to + 1) * sizeof(uint8_t));
    primes[0] = 0;
    primes[1] = 0;

    int i, j;
    for (i = 2; i * i <= to; ++i) {
        if (!primes[i])
            continue;

        for (j = i * i; j <= to; j += i)
            primes[j] = 0;
    }

    int64_t count = 0;
    for (i = from; i <= to; ++i) {
        if (primes[i])
            ++count;
    }

    return count;
}
```

### Αρχείο league.c (παλιό θέμα) - lec20

Credits: Αλέξανδρος

```c
// Program for computing league scores.
// Possible solution to: https://progintro.github.io/exams/2023/fall/ex13/ - problem #3

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Datastructure for holding team data
typedef struct {
  char name[64]; // including null terminator
  int points;
  int goals[2]; // in, out
} Team;

// TEST ASAP
// Comparing teams first by points, then by goal difference, last by name
int teamcmp(const void *team1, const void *team2) {
  Team *t1 = (Team *)team1; // implicit casting, cry
  Team *t2 = (Team *)team2;
  if (t1->points != t2->points)
    return t2->points - t1->points;
  int diff = (t2->goals[0] - t2->goals[1]) - (t1->goals[0] - t1->goals[1]);
  if (diff != 0)
    return diff;
  return strcmp(t1->name, t2->name);
}

// Up to 100 teams, more checks are needed for real world usage
Team teams[100] = {0};
int8_t last_team = 0;
// TODO add helper functions... eventually(tm)

int team_index(char *name) {
  int index = -1;
  // char found=0; // JUSTICE FOR UNCONDITIONAL JUMPS
  for (int i = 0; i < last_team; i++) {
    if (strcmp(name, teams[i].name) == 0) {
      index = i;
      break;
    }
  }
  return index;
}

void add_team(char *name) {
  strcpy(teams[last_team].name, name); // ez pwn challenge
  last_team++;
}

int main(int argc, char **argv) {
  if (argc != 2)
    return 1;
  FILE *f = fopen(argv[1], "r");
  if (!f)
    return 1;
  char name1[64], name2[64];
  int gin, gout;
  while (fscanf(f, "%63[^-]-%63[^,],%d-%d\n", name1, name2, &gin, &gout) == 4) {
    int team1_index = team_index(name1);
    int team2_index = team_index(name2);
    if (team1_index == -1) {
      add_team(name1);
      team1_index = team_index(name1);
    }
    if (team2_index == -1) {
      add_team(name2);
      team2_index = team_index(name2);
    }
    teams[team1_index].goals[0] += gin;
    teams[team2_index].goals[0] += gout;
    teams[team1_index].goals[1] += gout;
    teams[team2_index].goals[1] += gin;
    int points = 0;
    if (gin > gout) {
      teams[team1_index].points += 3;
    } else if (gout > gin) {
      teams[team2_index].points += 3;
    } else {
      teams[team1_index].points += 1;
      teams[team2_index].points += 1;
    }

  } // GET OUT
  fclose(f);
  // Sort out the teams
  qsort(teams, last_team, sizeof(Team), &teamcmp);
  for (int i = 0; i < last_team; i++) {
    fprintf(stdout, "%s, %d, %d - %d\n", teams[i].name, teams[i].points,
            teams[i].goals[0], teams[i].goals[1]);
  }

  return 0;
}
```
