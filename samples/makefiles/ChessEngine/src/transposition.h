#ifndef TRANSPOSITION_H
#define TRANSPOSITION_H

#include <stddef.h>

#include "types.h"

// variables for transposition table and its size
extern TTentry *transposition_table;
extern size_t tt_size;

// function prototypes
void init_tt(size_t size);
void store_tt(U64 key, int depth, int score, Move best_move, Node node_type);
TTentry *probe_tt(U64 key);
void clear_tt(void);

#endif
