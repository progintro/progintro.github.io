# First target is the build target when 'make' is run with no arguments
# 'main' is target that produces the final executable
main: primes.o main.o # we need primes.o and main.o to be up to date in order for us to build
	# to build an executable, we need only invoke the linker with our object files
	gcc -o main main.o primes.o

# primes.o is a target that produces an object file
primes.o: primes.c primes.h # whenever primes.c or primes.h change, this target is marked out of date
	# to build an object file we need only invoke the compiler using our source file an input
	gcc -c primes.c

# main.o is also a target that produces an object file
main.o: main.c primes.h # whenever main.c or primes.h change, this target is market out of data
	# to build an object file we again invoke the compiler
	gcc -c main.c

