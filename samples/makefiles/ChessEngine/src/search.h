#ifndef SEARCH_H
#define SEARCH_H

#include "types.h"

// recursion calls counter for timeout
extern int count;

// function prototypes
int equal_moves(const Move *m1, const Move *m2);
int compare_moves(const void *a, const void *b);
int dls_search(Board *board, int depth, int is_root, Move *best_move, int alpha, int beta, MoveList start_list, Move previous_best, int timeout);
Move ids_search(Board *board, int max_depth, MoveList start_list, int timeout);

#endif
