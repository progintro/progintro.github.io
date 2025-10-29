# Κώδικας Διαλέξεων

## Code Samples - Credit: Τάκης

### capitalize.c

```c
/* File: capitalize.c */

#include <stdio.h>

int main()
{
	int ch; /* Be careful! Declare ch as int because of getchar() and EOF */
	ch = getchar();                               /* Read first character */
	while (ch != EOF) {           /* Go on if we didn't reach end of file */
		if (ch >= 'a' && ch <= 'z')           /* If lower case letter */
			ch = ch - ('a'-'A');        /* Move 'a'-'A' positions
							   in the ASCII table */
		putchar(ch);                           /* Print out character */
		ch = getchar();                        /* Read next character */
	}
	return 0;
}
```

### easter.c

```c
/* File: easter.c */

#include <stdio.h>
#define STARTYEAR 2020
#define ENDYEAR   2040

int main()
{
	int year, a, b, c, d, e;
	for (year = STARTYEAR ; year <= ENDYEAR ; year++) {
		a = year % 19;
 		b = year % 4;    /* Gauss method for Easter date computation */
		c = year % 7;
		d = (19*a+15) % 30;
		e = (2*b+4*c+6*d+6) % 7;
		printf("Easter in the year %d: ", year);
		if (d+e+4 > 30) {                             /* Easter in May */
 			printf("  May %d\n", d+e-26);
		}
		else {                                      /* Easter in April */
			printf("April %d\n", d+e+4);
		}
	}
	return 0;
}
```

### factorize.c

```c
/* File: factorize.c */

/* Factorizes all numbers in a range */

#include <stdio.h>

int main()
{
	int minnum, maxnum, num, temp, factor;
	printf("Please, give minimum number: ");
	scanf("%d", &minnum);
	printf("Please, give maximum number: ");
	scanf("%d", &maxnum);
	for (num = minnum ; num <= maxnum ; num++) {
		printf("Prime factors of %d are:", num);
		temp = num;
		factor = 2;	// Start with 2 as possible factor
		while (factor * factor <= temp) {
				// Check candidate factors up to the square root
			while (temp % factor == 0) {
				printf(" %d", factor);
				temp /= factor;
			}
			if (factor == 2) {
				factor = 3;	// Next factor to check is 3
			}
			else if (factor % 6 == 1) {
				factor += 4;	// Next of 7 is 11, of 13 is 17, etc.
			}
			else {
				factor += 2;
					// Next of 3 is 5, of 5 is 7, of 11 is 13, etc.
			}
		}
		if (temp != 1) {	// Is final temp a prime factor?
			printf(" %d", temp);
		}
		printf("\n");
	}
	return 0;
}
```

### humble.c

```c
/* File: humble.c */

/* Finds all humble numbers in a given range */

/* A number is humble if it doesn't have any prime
   factors different from 2, 3, 5, 7  */

#include <stdio.h>
#define MINNUM 10
#define MAXNUM 1000

int main()
{
	int num, temp;
	for (num = MINNUM ; num <= MAXNUM ; num++) {
		temp = num;
		while (temp % 2 == 0) {
			temp /= 2;
		}                  // Remove all 2's as factors
		while (temp % 3 == 0) {
                        temp /= 3;
                }                  // Remove all 3's as factors
		while (temp % 5 == 0) {
                        temp /= 5;
                }                  // Remove all 5's as factors
		while (temp % 7 == 0) {
                        temp /= 7;
                }                  // Remove all 7's as factors
		if (temp == 1) {   // Are there any remaining factors?
			printf("%d is a humble number\n", num);
		}
	}

	return 0;
}
```

### magic.c

```c
/* File: magic.c */

#include <stdio.h>
#define SIZE 5

int main()
{
	int i, j, k;
	int x[SIZE][SIZE];                      /* The board to be filled */
	for (i=0 ; i < SIZE ; i++) {
		for (j=0 ; j < SIZE ; j++) {
			x[i][j] = 0;            /* Mark all squares as empty */
		}
	}
	i = (SIZE-1)/2;                         /* Go to middle */
	j = SIZE-1;                             /* right square */
	for (k=1 ; k <= SIZE*SIZE ; k++) {
		if (x[i][j] != 0) {             /* If current not empty */
 			i = i-1;                /* Move one square up */
			j = j-2;                /* and two squares left */
			if (i < 0)
				i = i+SIZE;     /* If you are outside */
			if (j < 0)
				j = j+SIZE;     /* go to the respective square inside */
		}
		x[i][j] = k;                    /* Fill current square with number k */
		i++;                            /* Move one square down */
		if (i == SIZE)
			i = 0;                  /* If outside get inside */
		j++;                            /* Move one square right */
		if (j == SIZE)
			j = 0;                  /* If outside get inside */
	}
	for (i=0 ; i < SIZE ; i++) {
		for (j=0 ; j < SIZE ; j++) {
			printf("%4d ", x[i][j]);   /* Print out board */
		}
		printf("\n");
	}
	return 0;
}
```

### picomp.c

```c
/* File: picomp.c */

#include <stdio.h>            /* Header file for standard I/O library */
#include <math.h>                     /* Header file for math library */

int main()
{
	int i;  
	double sum, current, pi;
	i = 1;                               /* Denominator of current term */
	sum = 0.0;                                            /* So far sum */
	do {
		current = 1/(((double) i)*((double) i));          /* Current term */
		sum = sum+current;                     /* Add current term to sum */
		i++;                                             /* Next term now */
	} while (current > 1.0e-18);  /* Stop if current term is very small */
	pi = sqrt(6*sum);                    /* Compute approximation of pi */
	printf("Summed %d terms, pi is %.8f\n", i-1, pi);
	return 0;
}
```

### perfect.c

```c
/* File: perfect.c */

/* Find all perfect numbers up to a maximum number */

/* A number is perfect if the sum of all its proper divisors,
   that is its divisors excluding itself, is equal to the number */

#include <stdio.h>

int main()
{
	int num, maxnum = 40000000, divisor, sum;
	for (num = 2 ; num <= maxnum ; num++) {
		sum = 1;	// Initialize sum of proper divisors of num
		for (divisor = 2 ; divisor * divisor < num ; divisor++) {
			// Check all candidate divisors in [2,sqrt(num)]
			if (num % divisor == 0) {
			// Is divisor really a divisor of num?
			// If yes, add it to sum together with its sibling
				sum += divisor + num / divisor;
			}
		}
		if (divisor * divisor == num) {
			// Is num a perfect square?
			sum += divisor;
		}
		if (sum == num) {
			// Just the definition of a perfect number
			printf("%d is a perfect number\n", num);
		}
	}
	return 0;
}
```

### primes.c

```c
/* File primes.c */

#include <stdio.h>
#include <stdlib.h>

/* Finds all prime numbers in a given range */

/* A number is prime if its only divisors are 1 and itself */

int main(int argc, char **argv)
{
	int minnum, maxnum, num, divisor, is_prime, count = 0;
	if (argc != 3) {
		printf("Usage: %s <minnum> <maxnum>\n", argv[0]);
		return 1;
	}
	minnum = atoi(argv[1]);
	maxnum = atoi(argv[2]);
	for (num = minnum ; num <= maxnum ; num++) {
		is_prime = 1;       // Consider num as prime
		if ((num != 2 && num % 2 == 0) || (num != 3 && num % 3 == 0)) {
			is_prime = 0;
		}
		else {
			for (divisor = 5 ; divisor * divisor <= num ; divisor += 6) {
				// Check for divisors up to the square root
				if (num % divisor == 0 || num % (divisor + 2) == 0) {
					is_prime = 0;   // num is not prime
					break;
				}
			}
		}
		if (is_prime == 1) {   // num is prime
//			printf("%d is prime\n", num);
			count++;
		}
	}
	printf("\nFound %d prime numbers\n", count);
	return 0;
}
```


## Student Programs
### prime.c - Credit: Ματθαίος

```c
// Computing the n-th prime (efficient enough? can it be done without math.h?)
#include <stdio.h>
#include <math.h>

long long is_prime(long long num) {
  long long count = 0;
  if (num == 2) return 1;
  if (num % 2 == 0) return 0;
  for (long long j = 3; j <= sqrt(num); j+=2) {
    if (num % j == 0) {
      count++;
      break;
    }
  }
  if (count == 0) {
    return 1;
  } else
    return 0;
}

int main() {
  long long a = 0;
  for (long long int i = 2; i <= 1000000; i++) {
    if (is_prime(i) == 1) {
      a++;
    }
    if (a == 20001) {
      printf("%lld\n", i);
      i = 1000000;
    }
  }
  return 0;
}
```

### multiples.c - Credit: Θανάσης

```c
// Computing the sum of all 3-digit multiples of 3 or 5.
#include <stdio.h>

int main(){
    long long int sum = 0;
    for (  int i = 3; i < 1000; i++){
        if (( i % 3 == 0) || (i % 5 ==0)){
           sum += i;
        }
    }
    printf("Sum: %lld\n", sum);
    return 0;
}
```

### perfect.c - Credit: Στέφανος

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

### grade.c - Credit: Γιάννης

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
