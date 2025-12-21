#include "print.h"

#include <stdio.h>

#include "types.h"
#include "utils.h"

// NOTE: these functions were used only for debugging purposes

// prints a board struct
void print_board(const Board *board) {
    printf("\n");
    for (int rank = 7; rank >= 0; rank--) {
        printf("%d   ", rank + 1);  // rank numbers
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            char piece_char = ' ';
            const char *piece_color = "\033[0m";  // reset color
            const char *bg_color = (rank + file) % 2 ? "\033[47m" : "\033[40m";

            const char piece_chars[12] = {'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k'};

            // check if any piece is in square and assign its char
            for (int i = 0; i < 6; i++) {
                if (board->pieces[0][i] & ((U64)1 << square)) {
                    piece_char = piece_chars[i];
                    piece_color = "\033[34m";
                } else if (board->pieces[1][i] & ((U64)1 << square)) {
                    piece_char = piece_chars[i + 6];
                    piece_color = "\033[31m";
                }
            }

            printf("%s\033[1m%s %c \033[0m", piece_color, bg_color, piece_char);  // print square
        }

        // print board details
        switch (rank) {
            case 7:
                printf("\tTo move: %s", board->turn == 0 ? "White" : "Black");
                break;
            case 6:
                printf("\tCastling rights: %s %s %s %s", board->castle_white & 1 ? "K" : "-", board->castle_white & 2 ? "Q" : "-",
                    board->castle_black & 1 ? "k" : "-", board->castle_black & 2 ? "q" : "-");
                break;
            case 5:
                if (board->ep_square != 64) {
                    printf("\tEn passant: %c%d", 'a' + (board->ep_square % 8), 1 + board->ep_square / 8);
                    break;
                }
                printf("\tEn passant: -");
                break;
            case 4:
                printf("\tHalfmove clock: %d", board->half_move);
                break;
            case 3:
                printf("\tFullmove number: %d", board->full_move);
                break;
        }

        printf("\n");
    }
    printf("\n     a  b  c  d  e  f  g  h\n");  // file letters
}

// prints a bitboard
void print_bitboard(const U64 board) {
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            if (is_set_bit(board, 8 * rank + file)) {
                putchar('1');
                continue;
            }
            putchar('.');
        }
        putchar('\n');
    }
    putchar('\n');
}

// prints a move struct
void print_move(Move *move) {
    const char *pieces[] = {"Pawn", "Knight", "Bishop", "Rook", "Queen", "King"};

    // print piece type
    printf("%-6s", pieces[move->piece]);

    // print move details
    printf(" %c%d -> %c%d", 'a' + (move->from % 8), 1 + move->from / 8, 'a' + (move->to % 8), 1 + move->to / 8);

    // handle capture
    if (move->flags & CAPTURE_MOVE) {
        printf(" | Capture");
    }

    // handle castling
    if (move->flags & CASTLING) {
        printf(" | Castling");
    }

    // handle en passant
    if (move->flags & EN_PASSANT) {
        printf(" | En passant");
    }

    // handle promotion
    if (move->promo != 0) {
        printf(" | Promotion: %s", pieces[move->promo]);
    }

    // handle double pawn push
    if (move->flags & DOUBLE_PAWN_PUSH) {
        printf(" | Double pawn push");
    }

    printf(" |\n");
}

// prints a move list struct
void print_move_list(MoveList *list) {
    printf("\n");
    for (int i = 0; i < list->count; i++) {
        printf("%-2d. ", i);
        print_move(&list->moves[i]);
    }
}

// prints a PeSTO table
void print_pesto_tables(int table[6][64]) {
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 64; j++) printf("%d ", table[i][j]);
        printf("\n");
    }
    return;
}
