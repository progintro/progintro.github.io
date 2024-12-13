/**
 * @file mirror.c
 * @author Chavatzoglou Lazaros
 * @brief Find (non palindromic) prime square mirrors within a given range.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <errno.h>


// Global variable to store the sum of prime square mirrors.
unsigned long long sq_sum = 0;


/**
 * @brief Check if a given number is a prime number.
 * @param n The number to check for primality.
 *
 * @note This function assumes that the input number (n) is greater than 2.
 * The behavior for n less than or equal to 2 is not defined.
 *
 * @return true if the number is prime, false otherwise.
 */
bool isPrime(unsigned int n){
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


/**
 * @brief Generate the mirror image of a given unsigned long long integer.
 * @param n The number for which to generate the mirror image.
 *
 * @note This function assumes that the input is positive and works only for
 * positive numbers, hence the unsigned datatype.
 *
 * @return The mirror image of the given number.
 */

unsigned long long mirror(unsigned long long n){

	unsigned long long rslt = 0;

	while(n){
		rslt = ((n % 10) + (rslt * 10));
		n /= 10;
	}

	return rslt;

}



/**
 * @brief Main function to find (non palindromic) prime square mirrors within
 * a given range.
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 *
 * @section DESCRIPTION:
 * The program takes two command-line arguments representing the lower and
 * upper bounds of the range. It then iterates from the ceiling of square root
 * of the lower bound to the floor of the square root of the upper bound, but
 * only through the odd numbers (this is done by adjusting the lower bound so
 * it is odd and by incrementing counter by 2), generating the square roots of
 * the all perfect squares in the given range. In each iterationa perfect
 * square is genrated and then its mirror. And we check whether these numbers
 * meet  our criteria and if so we add them to the sum.
 *
 * @section OUTPUT:
 * Last but not least the programme outputs the total sum of all the prime
 * square mirrors found (given that the programme did not terminate due to the
 * input not meeting the technical specifications).
 *
 *
 * @note The programme iterates only through odd numbers because we are
 * interested in these numbers being prime and odd numbers aren't (with the
 * exception of 2 which is the root of 4 which only has  one digit therefore a
 * palindrome which excludes it from excluding it from our interest).
 *
 *
 * @return 0 if successful, 1 if an incorrect number of arguments is provided,
 * or genrally the technical specifications describbed in
 * https://progintro.github.io/resources/hw1.pdf concerning the input of the
 * programme mirror are not met.
 */


int main(int argc, char **argv){

	// Check if the correct number of command-line arguments is provided.
	if(argc != 3){
		return 1;
	}

	// Set errno to 0.
	errno = 0;

	// Parse command-line arguments and set the range.
	long long low = strtoll(argv[1], NULL, 10);
	long long high = strtoll(argv[2], NULL, 10);
	// CHeck whether an error occured during the the conversions using strtoll
	// (overflow/underflow).
	if(errno != 0) { return 1; }

	// Validate the range.
	if((low > high) || (high > 1E15) || (low < 1)){
		return 1;
	}

	// Generate a new low which coresponds to the root of the smallest
	// perfect square within range.
	int l_low = ceil(sqrt(low));
	// Gnerate a new high which coresponds to the root of the largest
	// perfect square within range.
	int l_high = floor(sqrt(high));

	// Adjust the lower bound so it skips all numbers with single digit squares (as they
	// are plindromes) and set it to the first odd number 5 so we can iterate
	// with step 2 only through odd numbers as even ones above 10 aren't
	// canditates for prime numbers.
	if(l_low < 5){ l_low = 5; }
	// Adjust the lower bound to skip one number if the current one is even so
	// we can iterate with step 2 and check only even numbers for primality as
	// odds above 11 aren't prime.
	else if((l_low % 2) == 0 ){ ++l_low; }

	// Iterate through all odd numbers which are square roots of perfect
	// squares in the range.
	for(int i = l_low; i <= l_high; i += 2){

		// Generate the perfect square.
		unsigned long long square = pow(i, 2);
		// Generate the mirror
		unsigned long long mirr = mirror(square);

		// Check if the mirror of the square and the square are equal which
		// means it's a palindrome, therefore we skip the current iteration
		if(square == mirr) { continue; }
		// Check if the mirror is even in which case even if it is a perfect
		// square the square root will be even therefore not prime, therefore
		// we skip to the next iteration.
		if((mirr % 2) == 0) {  continue; }
		// Generate the square root of the mirror.
		double mirr_sqrt = sqrt(mirr);
		// Check if the square root has a non zero decimal part threrfore not
		// an integer and subsequently not a prime, so we skip to the next
		// iteration.
		if(fmod(mirr_sqrt, 1.0) != 0) { continue; }

		// Check if the the current square root i has stored and the square
		// root of the mirror aren't prime, in which case you guessed it we
		// skip to the next iteration.
		if(!isPrime(i)){continue; }
		if(!isPrime(mirr_sqrt)) {continue; }

		// If i passed all the above tests it fits all our criteria and
		// therefore is the square root of a prime perefect square mirror, so
		// we add the corespondindg square to the sum.
		sq_sum += square;
	}


	// Print the total sum of prime square mirrors to STDOUT.
	printf("%llu\n", sq_sum);

	return 0;

}

