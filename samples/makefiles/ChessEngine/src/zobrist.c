#include "zobrist.h"

#include <stdlib.h>

#include "types.h"

// zobrist hashing keys
U64 zobrist_pieces[2][6][64];
U64 zobrist_castling[16];
U64 zobrist_enpassant[65];
U64 zobrist_side;

// generates random U64 number
U64 rand64(void) {
    return rand() ^ ((U64)rand() << 15) ^ ((U64)rand() << 30) ^ ((U64)rand() << 45) ^ ((U64)rand() << 60);
}

// initializes zobrist hashing keys
void init_zobrist(void) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 64; k++) {
                zobrist_pieces[i][j][k] = rand64(); // randomize piece keys
            }
        }
    }
    for (int i = 0; i < 16; i++) {
        zobrist_castling[i] = rand64(); // randomize castling keys
    }
    for (int i = 0; i < 65; i++) {
        zobrist_enpassant[i] = rand64(); // randomize en passant keys
    }
    zobrist_side = rand64(); // randomize side key
}

// updates the board key using XOR operations
void fast_board_key(Board *board, const Move *move) {
    // STEP 1: remove key for the piece's source square
    board->key ^= zobrist_pieces[board->turn][move->piece][move->from];

    // STEP 2: update en passant key (XOR out old, XOR in new)
    board->key ^= zobrist_enpassant[move->ep];
    board->key ^= zobrist_enpassant[board->ep_square];

    // STEP 3: update castling rights, if any
    // NOTE: temp board is needed to xor the old ones
    if (((board->castle_black ^ move->castle_black) != 0) || ((board->castle_white ^ move->castle_white) != 0)) {
        Board temp;
        temp.castle_black = move->castle_black;
        temp.castle_white = move->castle_white;
        board->key ^= zobrist_castling[((int)temp.castle_white << 2) | (int)temp.castle_black];
        board->key ^= zobrist_castling[((int)board->castle_white << 2) | (int)board->castle_black];
    }

    // STEP 4: update pieces keys
    // NOTE: special cases for pawn and king moves are handled separately
    switch (move->piece) {
        case PAWN:
            if (move->flags & EN_PASSANT) {
                //board->key ^= zobrist_pieces[board->turn][move->piece][move->to];
                int sq = board->turn ? move->to + 8 : move->to - 8;
                board->key ^= zobrist_pieces[!board->turn][move->piece][sq];
            }
            if (move->flags & PROMOTION) {
                board->key ^= zobrist_pieces[board->turn][move->promo][move->to];
            }
            else {
                board->key ^= zobrist_pieces[board->turn][move->piece][move->to];
            }
            if (move->captured != NONE) {
                board->key ^= zobrist_pieces[!board->turn][move->captured][move->to];
            }
        break;

        case KING:
            if (move->flags & CASTLING) {
                if (move->to == (board->turn ? 62 : 6)) {
                    board->key ^= zobrist_pieces[board->turn][KING][move->to];
                    board->key ^= zobrist_pieces[board->turn][ROOK][move->to + 1];
                    board->key ^= zobrist_pieces[board->turn][ROOK][move->to - 1];
                }
                else if (move->to == (board->turn ? 58 : 2)) {
                    board->key ^= zobrist_pieces[board->turn][KING][move->to];
                    board->key ^= zobrist_pieces[board->turn][ROOK][move->to + 1];
                    board->key ^= zobrist_pieces[board->turn][ROOK][move->to - 2];
                }
                break;
            }
            // no break cause may not be castle

            // NOTE: don't remove the comment below, it is genuinely needed or it fails
            /* fall through */
        default:
            board->key ^= zobrist_pieces[board->turn][move->piece][move->to];
            if (move->captured != NONE) {
                board->key ^= zobrist_pieces[!board->turn][move->captured][move->to];
            }
    }
    board->key ^= zobrist_side;
}
