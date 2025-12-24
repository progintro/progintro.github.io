#include "search.h"

#include <stdlib.h>

#include "board.h"
#include "constants.h"
#include "eval.h"
#include "moves.h"
#include "transposition.h"
#include "zobrist.h"

// recursion calls count for timeout
int count;

// compares moves by score for sorting, returns highest score move
int compare_moves(const void *a, const void *b) {
    return ((const Move *)b)->score - ((const Move *)a)->score;
}

// checks if two moves are equal
int equal_moves(const Move *m1, const Move *m2) {
    return (m1->from == m2->from) && (m1->to == m2->to) && (m1->promo == m2->promo);
}

// depth-limited search (dls) with alpha-beta pruning
int dls_search(Board *board, int depth, int is_root, Move *best_move, int alpha, int beta, MoveList start_list, Move previous_best, int timeout) {
    count++; // increment recursion calls count

    // STEP 1: initialize alpha, beta for transposition table and current side
    int side = board->turn;
    int initial_alpha = alpha;
    int initial_beta = beta;

    // STEP 2: probe the transposition table
    // NOTE: tt's depth has to be bigger depth or there's no point in getting that entry
    TTentry *tt_entry = probe_tt(board->key);

    // check if tt entry is valid
    if (tt_entry != NULL && tt_entry->depth >= depth) {
        if (tt_entry->node_type == EXACT) {
            return tt_entry->score; // return exact score
        } else if (tt_entry->node_type == LOWER) {
            alpha = (alpha > tt_entry->score) ? alpha : tt_entry->score; // update alpha
        } else if (tt_entry->node_type == UPPER) {
            beta = (beta < tt_entry->score) ? beta : tt_entry->score; // update beta
        }
        if (beta <= alpha) return tt_entry->score; // prune search
    }

    // STEP 3: return evaluation in case of recursion base case or timeout
    if (depth == 0 || count > HEURISTIC_THRESHOLD * timeout) {
        return eval(board);
    }

    // STEP 4: generate moves based on root status
    MoveList list;
    list.count = 0;

    if (!is_root) {
        generate_moves(board, &list); // generate legal moves

        // prioritize best move from transposition table
        if (tt_entry != NULL) {
            for (int j = 0; j < list.count; j++) {
                if (equal_moves(&list.moves[j], &tt_entry->best_move)) {
                    list.moves[j].score = BEST_MOVE_BOOST; // highest priority
                    break;
                }
            }
        }
    } else {
        #if DEBUG == 1
            generate_moves(board, &list); // generate moves manually in debug mode
        #else
            list = start_list; // use starting move list otherwise
        #endif

        // boost previous best move score
        if (previous_best.score == PREVIOUS_BEST_BOOST) {
            for (int j = 0; j < list.count; j++) {
                if (equal_moves(&list.moves[j], &previous_best)) {
                    list.moves[j].score = PREVIOUS_BEST_BOOST;  // boost score
                    break;
                }
            }
        }
    }

    // STEP 5: sort moves based on heuristic scores
    qsort(list.moves, list.count, sizeof(Move), compare_moves);

    // STEP 6: handle end game conditions
    if (list.count == 0 && generate_checkers(board) != 0) {
        return (board->turn ? INF : -INF); // checkmate (cooked)
    } else if (list.count == 0) {
        return 0; // stalemate
    }

    // STEP 7: iterate through generated moves
    int best_current_score = (side == WHITE) ? -INF : INF; // initialize best score
    Move best_current_move = list.moves[0]; // initialize best move

    // minimax logic for white and black respectively
    // NOTE: the code repetitiveness in handling white and black moves is intentional for optimization purposes
    if (side == WHITE) {
        for (int i = 0; i < list.count; i++) {
            apply_move(board, &list.moves[i]); // apply the move
            fast_board_key(board, &list.moves[i]); // update zobrist key

            int rec_score = dls_search(board, depth - 1, 0, NULL, alpha, beta, start_list, previous_best, timeout); // recursive call

            fast_board_key(board, &list.moves[i]); // reset zobrist key
            undo_move(board, &list.moves[i]); // undo the move

            // update best move if a better score is found
            if (rec_score > best_current_score) {
                best_current_move = list.moves[i];
                best_current_score = rec_score;
            }

            if (rec_score > alpha) alpha = rec_score; // update alpha

            if (beta <= alpha) break; // prune the search
        }
    } else {
        for (int i = 0; i < list.count; i++) {
            apply_move(board, &list.moves[i]); // apply the move
            fast_board_key(board, &list.moves[i]); // update zobrist key

            int rec_score = dls_search(board, depth - 1, 0, NULL, alpha, beta, start_list, previous_best, timeout); // recursive call

            fast_board_key(board, &list.moves[i]); // reset zobrist key
            undo_move(board, &list.moves[i]); // undo the move

            // update best move if a better score is found
            if (rec_score < best_current_score) {
                best_current_move = list.moves[i];
                best_current_score = rec_score;
            }
            if (rec_score < beta) beta = rec_score; // update beta

            if (beta <= alpha) break; // prune the search
        }
    }

    // STEP 8: store the best move and score in the transposition table
    Node node_type;
    if (best_current_score <= initial_alpha) {
        node_type = UPPER; // upper bound
    } else if (best_current_score >= initial_beta) {
        node_type = LOWER; // lower bound
    } else {
        node_type = EXACT; // exact
    }

    store_tt(board->key, depth, best_current_score, best_current_move, node_type); // store in tt

    if (is_root == 1) *best_move = best_current_move; // update best move only at root

    return best_current_score;
}

// iterative deepening search (ids) for a given board
Move ids_search(Board *board, int max_depth, MoveList start_list, int timeout){
    count = 0; // reset recursion calls count
    Move best_move = {0};
    Move previous_best = {0};

    // iterate through each depth
    for (int depth = 1; depth <= max_depth; depth++) {

        Move curr_move;
        dls_search(board, depth, 1, &curr_move, -INF, INF, start_list, previous_best, timeout); // call dls

        if (count > HEURISTIC_THRESHOLD * timeout) break; // timeout check
        best_move = curr_move; // update best move
        previous_best = curr_move; // update previous best move
        previous_best.score = PREVIOUS_BEST_BOOST; // boost last best move
    }

    return best_move;
}
