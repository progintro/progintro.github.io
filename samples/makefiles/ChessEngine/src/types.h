#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

// typedefs for integer types
typedef uint64_t U64;
typedef uint32_t U32;
typedef uint16_t U16;
typedef uint8_t U8;

// enum for piece types
typedef enum { PAWN = 0, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE } PieceType;

// enum for castling rights (2 bits for each player)
typedef enum {
    CANNOT_CASTLE = 0,   // 00
    CAN_CASTLE_OO = 1,   // 01
    CAN_CASTLE_OOO = 2,  // 10
    CAN_CASTLE = 3       // 11 (both sides)
} CastleRights;

// enum for which to move
typedef enum { WHITE = 0, BLACK = 1 } Turn;

// enum for move flags (One-hot)
typedef enum {
    NORMAL_MOVE = 0,       // 00000
    CAPTURE_MOVE = 1,      // 00001
    EN_PASSANT = 2,        // 00010
    CASTLING = 4,          // 00100
    PROMOTION = 8,         // 01000
    DOUBLE_PAWN_PUSH = 16  // 10000
} MoveFlags;

// structure for representing the board state
typedef struct {
    // use 2 arrays of 6 piece types for black (1) and white (0)
    U64 pieces[2][6];

    // 0 for white, 1 for black, 2 for both
    U64 occupied[3];

    Turn turn : 1;                  // 1 bit
    CastleRights castle_white : 2;  // 2 bits
    CastleRights castle_black : 2;  // 2 bits

    U8 ep_square;   // store en passant square (64 for none)
    U8 half_move;   // half move counter
    U64 key;        // zobrist key
    U16 full_move;  // full move counter
} Board;

// structure for representing a move
typedef struct {
    // do move
    U8 from;   // start square (0-63)
    U8 to;     // final square (0-63)
    U8 promo;  // promotion piece type

    // undo move
    U8 piece;         // moved piece type
    U8 captured;      // captured piece type
    U8 flags;         // special move flags (One-hot)
    U8 ep;            // en passant square (if any)
    U8 castle_white;  // previous white castling rights
    U8 castle_black;  // previous black castling rights
    int score;        // heuristic score of a move
} Move;

// structure for generated moves
typedef struct {
    Move moves[256];  // array of moves
    int count;        // number of moves stored
} MoveList;

// struct for attack mask tables
typedef struct {
    U64 knight[64];
    U64 king[64];
    U64 pawn[2][64];
    U64 rook[102400];
    U64 bishop[5248];
} LUT;

// node types for transposition table entries
typedef enum { EXACT, LOWER, UPPER } Node;

// entry for the transposition table
typedef struct {
    U64 key;         // zobrist hashing key
    int depth;       // depth of position
    int score;       // evaluation score
    Move best_move;  // best move found
    Node node_type;  // type of position
} TTentry;

#endif
