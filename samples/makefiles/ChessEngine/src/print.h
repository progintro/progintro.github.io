#ifndef PRINT_H
#define PRINT_H

#include "types.h"

// function prototypes
void print_board(const Board *board);
void print_bitboard(const U64 board);
void print_move(Move *move);
void print_move_list(MoveList *list);
void print_pesto_tables(int table[6][64]);

#endif
