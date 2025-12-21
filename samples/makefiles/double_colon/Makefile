# This Makefile is only an example of how make macros work
# Try different combinations of the commented out lines of code
# and run 'make' between them. 
# For more info look at the slides on the part about macro assignments.
A=makis
B=$(A) 42 # comment this out and see what happens
# B:=$(A) 42 # uncomment this and see what happens
A=takis

# try to think about what running 'make' will print here
hello:
	@echo $(B)

.PHONY: hello

# B=$(A) 42 # uncomment this and see what happens
