#include "transposition.h"

#include <stdlib.h>

// global variables for the transposition table and its size
TTentry *transposition_table;
size_t tt_size;

// initializes transposition table
void init_tt(size_t size) {
    tt_size = size;
    transposition_table = malloc(tt_size * sizeof(TTentry));
}

// stores an entry in the transposition table, replaces old entries if necessary
void store_tt(U64 key, int depth, int score, Move best_move, Node node_type) {
    if (tt_size == 0 || transposition_table == NULL) return;

    size_t index = key % tt_size;
    if (index >= tt_size) return;

    TTentry *entry = &transposition_table[index];

    // update entry if new depth is greater
    if (entry->depth <= depth) {
        entry->key = key;
        entry->depth = depth;
        entry->score = score;
        entry->best_move = best_move;
        entry->node_type = node_type;
    }
}

// probes the transposition table for a key
TTentry *probe_tt(U64 key) {
    size_t index = key % tt_size;
    TTentry *entry = &transposition_table[index];
    return (entry->key == key) ? entry : NULL;
}

// frees the transposition table memory
void clear_tt(void) {
    free(transposition_table);
}
