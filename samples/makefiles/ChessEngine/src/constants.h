#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <limits.h>

// set DEBUG to 1 to enable debug mode, which includes additional logging and diagnostics,
// or set DEBUG to 0 to disable debug mode, which removes debug related code
#define DEBUG 0

// define bitboards for A, B, G, H file
#define FILE_A 0x0101010101010101ULL
#define FILE_B 0x0202020202020202ULL
#define FILE_G 0x4040404040404040ULL
#define FILE_H 0x8080808080808080ULL

// define combined files bitboards
#define FILE_GH (FILE_G | FILE_H)
#define FILE_AB (FILE_A | FILE_B)

// define bitboards for 1, 2, 7, 8 rank
#define RANK_1 0x00000000000000FFULL
#define RANK_2 0x000000000000FF00ULL
#define RANK_7 0x00FF000000000000ULL
#define RANK_8 0xFF00000000000000ULL

// define the castling masks
#define WSHORT 0x70ULL
#define BSHORT 0x7000000000000000ULL
#define WLONG_OCCUPIED 0x1EULL
#define WLONG_ATTACKED 0x1CULL
#define BLONG_OCCUPIED 0x1E00000000000000ULL
#define BLONG_ATTACKED 0x1C00000000000000ULL

// define evaluation bonuses and penalties
#define INF INT_MAX
#define DOUBLED_PAWN_MG_PENALTY 10
#define DOUBLED_PAWN_EG_PENALTY 20
#define KING_SAFETY_BONUS_MG 20
#define KING_SAFETY_BONUS_EG 15
#define OPEN_FILE_KING_MG_PENALTY 25
#define OPEN_FILE_KING_EG_PENALTY 40

// define search bonuses and constants
#define BEST_MOVE_BOOST 40000
#define PREVIOUS_BEST_BOOST 20000
#define HEURISTIC_THRESHOLD 3500000

#endif
