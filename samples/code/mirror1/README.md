*****
# This programme finds all the non-palindromic prime square mirrors in a given range. 
******
### These are the libraries used:
 1. **stdio.h**  This library is included for the function **printf**, so we can output the results to __STDOUT__.
 2. **stdlib.h** This library is included for the function **strtoll**, so we can covert the command line arguments to **long long** datatype numbers.
 3. **math.h** This library is included for the function **pow**, so we can calculate the square of numbers; the function **sqrt**, so we can calculate square roots; the function **floor** so we can take the floor of a number, and the function **ceil**n so we can take the ceiling of a number.
 4. **stdbool.h** This library is included for the datatype **bool**, so we can handle more easily true/false statements.
 5. **errno.h** This library is included for the variable **errno**, which can be set from other functions in the c library, in this case **strtoll**, so we can detect errors (in this case whether the conversion was successful, or there was overflow/undeflow).
***********

## Build


This programme can be compiled with the command:
```shell
gcc -O3 -Wall -Wextra -Werror -pedantic -o mirror mirror.c -lm
```

## Usage

And it must be executed in this manner:
```shell
./mirror low high
```
where low is the lower bound and high is the higher bound.
***************

## Demo

```sh
$ ./trolley
lkjsdflk sjlkj
```

## Functions
#### isPrime
```c
bool isPrime(unsigned int n){		//works for n > 2
	if((n % 2) == 0){
		return false;
	}


	for(int i = 3; i < (floor(sqrt(n)) + 1); i += 2){
		if((n % i) == 0){
			return false;
		}
	}

	return true;

}
```
This function tests if a number above 2 is prime or not.
This function employs a basic primality testing algorithm. It first checks if the input number is divisible by 2, and if so, returns false. Then, it
iterates through odd numbers starting from 3 up to the square root of the input number. If the input number is divisible by any of these odd numbers,
the function returns false. If no divisors are found, the function concludes that the input number is a prime number and returns true.
This primality test works, because if a number is not prime it has at least one divisor apart from 1 and itself.
Therefore, if $n$ isn't prime and has a divisor $a$ it can be written such as $s = a \cdot b$, where $b$ is the result of the division of $n$ by $a$.
Then either $\sqrt{n} \geq a$ or $\sqrt{n} \geq b$. Otherwise $a \ge \sqrt{n}$ and $b > \sqrt{n}$ so $a \cdot b > {\sqrt{n}}^2 = n \xRightarrow[]{n = a \cdot b} n > n$
which cannot be true. Therefore if $n$ isn't prime it has one divisor smaller or equal then the $\sqrt{n}$.
(Also we take the ceiling of the square root of n beacuse one check is really cheap computationally and can't hurt.)

***********
#### mirror
```c
unsigned long long mirror(unsigned long long n){
	
	unsigned long long rslt = 0;

	while(n){			//works beacuse MIN low is 1
		rslt = ((n % 10) + (rslt * 10));
		n /= 10;
	}	

	return rslt;

}
```
This function takes an unsigned long long integer as input and returns a new integer with its digits reversed. It uses a while loop to iterate through
the digits of the input number, extracting the last digit in each iteration and appending it to the result after shifting the result to the left by one
decimal place and then shifhting the number $n$ by ne decimal place to the right so that in the next iteration we will get th next digit. 
The loop continues until the input number becomes zero due to divisions by 10.

***********

## main
1. First, we check that the correct number of arguments is provided; otherwise, the programmme terminates with exit code 1.
```c
	if(argc != 3){
		return 1;
	}
```
2. **errno** is set to 0 (as required by its documentation), so if **strtod** sets it to a non-zero value, we can be certain this value is due to an error.
3. Then we parse the command-line arguments corresponding to the higher and lower bound of our range.
```c
long long low = strtoll(argv[1], NULL, 10);
long long high = strtoll(argv[2], NULL, 10);
```
4. Then we check whether **errno** has a non-zero value, thus indicating that there was overflow/underflow during a conversion from **string** to **long long**.
5. Afterwards, we check that range we are given is valis.
```c
if((low > high) || (high > 1E15) || (low < 1)){
	return 1;
}
```
6. Then we generate 2 new bounds for a loop ```l_low``` and ```l_high``` which correspond to the square root of the smallest and largest perefect square in our range (we use **seil** and **floor** to ensure that we dont include numbers outside our range).
```c
int l_low = ceil(sqrt(low));
int l_high = floor(sqrt(high)) + 1;
```
7. Then we further adjust the lower boound ```l_low``` so that in case it is smaller than 5 it is to 5 as it is the smallest odd number and its square has more than one digit,
as signle digit numbers are palindromes which we want to exclude. Also if ```l_low``` is even we increment by one, due to the fact that even nubers cannot prime (with the exception of 2),
so we can have step 2 in our loop so we only check odd numbers for primality.
```c
if(l_low < 5){ l_low = 5; }
else if((l_low % 2) == 0 ){ ++l_low; }
```
8. Then we iterate from ```l_low``` to ```l_high``` with step 2, so that we can go through all the square roots of the perfect squares in our given range. Thus we generate the perfect squares instead of checking if all numbers whether they are a perfect square.
 1. First we generate the perfect square ```square```.
 2. Then we generate its mirror ```mirr```.
 3. Then in case the square is the same as the mirror the number is a palindrome and so we skip to the next iteration.
 4. If the mirror divided by 2 has a remainder zero then it's odd. Therefore even if it is a perfect square its square root will be odd and therefore not prime (as the only odd prime is 2 and its square 4 is a palindrome, as it a one digit number), so we skip to the next iteration.
 5.  If the square root of the mirror ```mirr_sqrt``` has a non zero decimal part then the mirror isn't a perfect square hence it's root can't be prime as primes are natural numbers. So we skip to the next iteration.
 6.  If the square root of the mirror ```mirr_sqrt``` or the square root of the perfect square ```i```, which was used to generate the mirror, isn't a prime we skip to the  next iteration as this number doesn't satisfy the given definition.
 7.  If all the above tests were passed then ```square``` meets all of our criteria and therefore we add it to the total sum.

8. Last we print the total sum of all the prime square mirrors and terminate the programme with exit code 0.


