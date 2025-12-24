#ifndef EVAL_H
#define EVAL_H

#include "types.h"

// evaluation tables
extern const int mg_value[6];
extern const int eg_value[6];

extern const int mg_pawn_table[64];
extern const int eg_pawn_table[64];

extern const int mg_knight_table[64];
extern const int eg_knight_table[64];

extern const int mg_bishop_table[64];
extern const int eg_bishop_table[64];

extern const int mg_rook_table[64];
extern const int eg_rook_table[64];

extern const int mg_queen_table[64];
extern const int eg_queen_table[64];

extern const int mg_king_table[64];
extern const int eg_king_table[64];

extern const int *mg_pesto_table[6];
extern const int *eg_pesto_table[6];

extern const int gamephase_inc[6];
extern int mg_table_white[6][64];
extern int mg_table_black[6][64];
extern int eg_table_white[6][64];
extern int eg_table_black[6][64];

extern int king_shield[2][64];

// function prototypes
void init_eval(void);
int eval(const Board *board);

#endif
