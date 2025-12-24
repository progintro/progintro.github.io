#ifndef BOARD_H
#define BOARD_H

#include "types.h"

// function prototypes
void apply_move(Board *board, Move *move);
void undo_move(Board *board, Move *move);

#endif
