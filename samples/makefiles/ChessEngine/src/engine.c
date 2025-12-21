#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "eval.h"
#include "fen.h"
#include "moves.h"
#include "search.h"
#include "transposition.h"
#include "zobrist.h"

#if DEBUG == 1
    #include "print.h" // include debug utilities
#endif

// chooses the best move based on a position in FEN notation, a move list in Algebraic notation, and a timeout
int choose_move(char *fen, char *moves, int timeout) {
    // seed RNG for reproducibility
    // NOTE: the id's of the students have been used as seeds for extra luck
    srand(2400118 + 2400141);

    // initialize tables and data structures
    init_moves(); // move generation LUTs
    init_eval(); // evaluation piece-square tables
    init_zobrist(); // zobrist hashing keys
    init_tt(16 * 1024 * 1024 / sizeof(TTentry)); // 16 MB transposition table

    Board board;
    board.key = (U64)0;
    loadFEN(&board, fen); // load board from FEN

    MoveList list = initial_list(&board, moves); // translate moves string to an initial list
    Move best = ids_search(&board, 50, list, timeout); // find best move

    // print board, moves, and best move in debug mode
    #if DEBUG == 1
        print_board(&board);
        print_move_list(&list);
        print_move(&best);
    #endif

    clear_tt(); // free transposition table

    // find and return the index of the best move in the initial list
    for (int i = 0; i < list.count; i++) {
        if (equal_moves(&best, &list.moves[i])) {
            return i;
        }
    }

    return 0; // default to first move
}

// main function used in the cli program
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: <fen> <moves> <timeout>\n");
        return 1; // error if arguments are incorrect
    }

    // parse timeout argument
    char *endptr;
    int timeout = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Provide a valid integer!\n");
        return 1; // error if timeout is invalid
    }

    // print best move index
    printf("%d\n", choose_move(argv[1], argv[2], timeout));

    return 0;
}
