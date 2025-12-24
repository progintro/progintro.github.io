# out compiler
CC=gcc
# macro used to abstract away compilation flags so that we don't have to write them multiple times
CFLAGS=-Wall -Werror -Wextra -pedantic -Os 

# First target is the build target when 'make' is run with no arguments
# 'main' is target that produces the final executable
main: primes.o main.o # we need primes.o and main.o to be up to date in order for us to build
	# to build an executable, we need only invoke the linker with our object files
	$(CC) $(CFLAGS) -o main main.o primes.o


# wildcard rule used to create a family of targets
# Specifically this creates a rule for object files
%.o: %.c # an object file always has a .c file as a prerequisite
	# recipe below uses automatic variable $@ which is the name of the currently building target
	# We *need* to use it because in this general family of rules, we do not specifically know the name of the target we are building
	# $^ refers to the first prerequisite
	$(CC) -c -o $@ $<

# additional rule that does not override the recipe for our object files
# This is used in order to append the additional header file prerequisite 
# to the specific rules created by the above general family of rules
primes.o main.o: primes.h

# additional rule to remove all build artifacts from the project.
# Generally speaking it's always a good idea to have one such rule
clean:
	rm -rf primes.o main.o main

# clean must be marked as phony as it does it's not a file target
.PHONY: clean
