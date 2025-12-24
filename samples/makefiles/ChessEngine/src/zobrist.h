#ifndef ZOBRIST_H
#define ZOBRIST_H

#include "types.h"

// zobrist hashing keys
extern U64 zobrist_pieces[2][6][64];
extern U64 zobrist_castling[16];
extern U64 zobrist_enpassant[65];
extern U64 zobrist_side;

// function prototypes
U64 rand64(void);
void init_zobrist(void);
void fast_board_key(Board *board, const Move *move);

#endif
