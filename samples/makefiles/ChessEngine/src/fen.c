#include "fen.h"

#include "utils.h"
#include "zobrist.h"

// loads a chess position in FEN format to a board
int loadFEN(Board *board, char *fen) {
    *board = (Board){0};
    int rank = 7, file = 0, last = 0;

    // STEP 1: parse pieces' positions
    char c;
    // loop through each rank
    while (rank >= 0) {
        int index = 8 * rank + file;
        c = fen[last];

        if (c == '\0') {
            return 0;
        }
        if (c == ' ' || c == '/') {
            file = 0;
            rank--;
            last++;
            continue;
        } else if ('1' <= c && c <= '8') {
            file += c - '0';
            last++;
            continue;
        }
        int color = ('a' <= c && c <= 'z') ? BLACK : WHITE;
        int piece;
        switch (c | 32) {  // equivalent to tolower()
            case 'p':
                piece = PAWN;
                break;
            case 'n':
                piece = KNIGHT;
                break;
            case 'b':
                piece = BISHOP;
                break;
            case 'r':
                piece = ROOK;
                break;
            case 'q':
                piece = QUEEN;
                break;
            case 'k':
                piece = KING;
                break;
            default:
                last++;
                continue;
        }
        board->pieces[color][piece] |= ((U64)1 << index);
        file++;
        last++;
    }

    if (fen[last] == '\0') return 0;

    // STEP 2: parse turn
    board->turn = (fen[last] == 'w') ? WHITE : BLACK;
    last++;
    while (fen[last] == ' ') last++;

    // STEP 3: parse castling rights
    board->castle_white = board->castle_black = CANNOT_CASTLE;
    while (fen[last] != ' ') {
        switch (fen[last]) {
            case '-':
                break;
            case 'K':
                board->castle_white |= CAN_CASTLE_OO;
                break;
            case 'Q':
                board->castle_white |= CAN_CASTLE_OOO;
                break;
            case 'k':
                board->castle_black |= CAN_CASTLE_OO;
                break;
            case 'q':
                board->castle_black |= CAN_CASTLE_OOO;
                break;
            default:  // includes '\0'
                return 0;
        }
        last++;
    }
    while (fen[last] == ' ') last++;

    // STEP 4: parse en passant square
    board->ep_square = 64;
    while (fen[last] == '-') last++;
    if (fen[last] && fen[last + 1] && 'a' <= fen[last] && fen[last] <= 'h' && '1' <= fen[last + 1] && fen[last + 1] <= '8') {
        file = fen[last] - 'a';
        rank = fen[last + 1] - '1';
        board->ep_square = 8 * rank + file;
        last += 2;
    }
    while (fen[last] == ' ') last++;

    // STEP 5: parse halfmove counter
    board->half_move = 0;
    while ('0' <= fen[last] && fen[last] <= '9') {
        board->half_move = 10 * board->half_move + (fen[last] - '0');
        last++;
    }
    while (fen[last] == ' ') last++;

    // STEP 6: parse fullmove counter
    board->full_move = 0;
    while ('0' <= fen[last] && fen[last] <= '9') {
        board->full_move = 10 * board->full_move + (fen[last] - '0');
        last++;
    }

    // STEP 7: update occupied and zobrist key
    for (int i = 0; i < 6; i++) {
        board->occupied[WHITE] |= board->pieces[WHITE][i];
        board->occupied[BLACK] |= board->pieces[BLACK][i];
        board->occupied[2] |= board->pieces[WHITE][i] | board->pieces[BLACK][i];
    }

    // STEP 8: update zobrist key
    board->key = (U64)0;
    for (int piece = PAWN; piece <= KING; piece++) {
        U64 pieces = board->pieces[WHITE][piece];
        while (pieces) {
            int sq = pop_lsb(&pieces);
            board->key ^= zobrist_pieces[WHITE][piece][sq];
        }
        pieces = board->pieces[BLACK][piece];
        while (pieces) {
            int sq = pop_lsb(&pieces);
            board->key ^= zobrist_pieces[BLACK][piece][sq];
        }
    }
    board->key ^= zobrist_castling[((int)board->castle_white << 2) | (int)board->castle_black];
    board->key ^= zobrist_enpassant[board->ep_square];
    if (board->turn == BLACK) {
        board->key ^= zobrist_side;
    }

    return 1;
}
