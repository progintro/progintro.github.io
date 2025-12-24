# the following is an advanced example of a Makefile
# We assume you know how macros work and how wildcard rules work
# for simplicity, we have also removed the part of the original makefile that
# built wasm targets.
# Huge thanks to ohgreg and itsfeold for letting us use their code here
# https://github.com/ItsFeold/ChessEngine

INCLUDE=src # our include directory
# -MMD instructs the compiler to emit Makefile dependency rules for the object files it compiles
# Then those rules are emitted in .d files
CFLAGS=-Wall -Wextra -Werror -pedantic -O3 -I$(INCLUDE) -MMD 
# the binary target we want to build
BINS=engine
# test files we want to build when testing
TESTS=perft

# include src and tests directories into the default vpath 
# that make default rules search for files in
# This lets make find the files we want our object files to be built from
vpath %.c src/
vpath %.c tests/

# default build target is just the binary targets
all: $(BINS)

# the rest of this makefile makes heavy use of built-in rules.
# Basically, since make was MADE to be used for building software projects
# it comes with a lot of built-in rules for exactly that
# The ones we care about, are those that define how an object file may be compiled from a .c files
# and the ones that define how an executable may be built by linking object files
# For more info:
# * The slides on makefiles
# * https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html

# this makes use of the built-in linking rule that make has
# each one of the object files is then created using the built-in rules for object files
engine: engine.o \
  fen.o \
  moves.o \
  print.o \
  board.o \
  eval.o \
  search.o \
  zobrist.o \
  transposition.o

# a test runner also depends on object files
# also makes use of the built-in linking rule
perft: moves.o board.o fen.o zobrist.o

# clean now has to include .d files as well
clean:
	rm -rf $(BINS) $(TESTS) *.o *.d

# this runs the resulting test file
test: $(TESTS)
	./$(TESTS)

.PHONY: test clean all

# this includes all .d files emitted by the compiler which guarantees changes to headers also lead to recompilation of the files that depend on them
-include *.d
