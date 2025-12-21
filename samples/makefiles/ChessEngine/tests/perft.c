#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "board.h"
#include "fen.h"
#include "moves.h"

typedef struct {
    char *name;
    char *fen;
    char *depth;
} PerftTestCase;

PerftTestCase testcases[] = {
    // https://www.chessprogramming.net/perfect-perft/
    {"Illegal en passant move #1", "3k4/3p4/8/K1P4r/8/8/8/8 b - - 0 1", ";D6 1134888"},
    {"Illegal en passant move #2", "8/8/4k3/8/2p5/8/B2P2K1/8 w - - 0 1", ";D6 1015133"},
    {"En passant capture checks oppenent", "8/8/1k6/2b5/2pP4/8/5K2/8 b - d3 0 1", ";D6 1440467"},
    {"Short castling gives check", "5k2/8/8/8/8/8/8/4K2R w K - 0 1", ";D6 661072"},
    {"Long castling gives check", "3k4/8/8/8/8/8/8/R3K3 w Q - 0 1", ";D6 803711"},
    {"Castle rights", "r3k2r/1b4bq/8/8/8/8/7B/R3K2R w KQkq - 0 1", ";D4 1274206"},
    {"Castling prevented", "r3k2r/8/3Q4/8/8/5q2/8/R3K2R b KQkq - 0 1", ";D4 1720476"},
    {"Promote out of check", "2K2r2/4P3/8/8/8/8/8/3k4 w - - 0 1", ";D6 3821001"},
    {"Discovered check", "8/8/1P2K3/8/2n5/1q6/8/5k2 b - - 0 1", ";D5 1004658"},
    {"Promote to give check", "4k3/1P6/8/8/8/8/K7/8 w - - 0 1", ";D6 217342"},
    {"Under promote to give check", "8/P1k5/K7/8/8/8/8/8 w - - 0 1", ";D6 92683"},
    {"Self stalemate", "K1k5/8/P7/8/8/8/8/8 w - - 0 1", ";D6 2217"},
    {"Stalemate and checkmate #1", "8/k1P5/8/1K6/8/8/8/8 w - - 0 1", ";D7 567584"},
    {"Stalemate and checkmate #2", "8/8/2k5/5q2/5n2/8/5K2/8 b - - 0 1", ";D4 23527"},

    // https://gist.github.com/peterellisjones/8c46c28141c162d1d8a0f0badbc9cff9?permalink_comment_id=3775288
    {"Peterellisjones position 1", "r6r/1b2k1bq/8/8/7B/8/8/R3K2R b KQ - 3 2", ";D1 8"},
    {"Peterellisjones position 2", "8/8/8/2k5/2pP4/8/B7/4K3 b - d3 0 3", ";D1 8"},
    {"Peterellisjones position 3", "r1bqkbnr/pppppppp/n7/8/8/P7/1PPPPPPP/RNBQKBNR w KQkq - 2 2", ";D1 19"},
    {"Peterellisjones position 4", "r3k2r/p1pp1pb1/bn2Qnp1/2qPN3/1p2P3/2N5/PPPBBPPP/R3K2R b KQkq - 3 2", ";D1 5"},
    {"Peterellisjones position 5", "2kr3r/p1ppqpb1/bn2Qnp1/3PN3/1p2P3/2N5/PPPBBPPP/R3K2R b KQ - 3 2", ";D1 44"},
    {"Peterellisjones position 6", "rnb2k1r/pp1Pbppp/2p5/q7/2B5/8/PPPQNnPP/RNB1K2R w KQ - 3 9", ";D1 39"},
    {"Peterellisjones position 7", "2r5/3pk3/8/2P5/8/2K5/8/8 w - - 5 4", ";D1 9"},
    {"Peterellisjones position 8", "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8", ";D3 62379"},
    {"Peterellisjones position 9", "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10", ";D3 89890"},
    {"Peterellisjones position 10", "3k4/3p4/8/K1P4r/8/8/8/8 b - - 0 1", ";D6 1134888"},
    {"Peterellisjones position 11", "8/8/4k3/8/2p5/8/B2P2K1/8 w - - 0 1", ";D6 1015133"},
    {"Peterellisjones position 12", "8/8/1k6/2b5/2pP4/8/5K2/8 b - d3 0 1", ";D6 1440467"},
    {"Peterellisjones position 13", "5k2/8/8/8/8/8/8/4K2R w K - 0 1", ";D6 661072"},
    {"Peterellisjones position 14", "3k4/8/8/8/8/8/8/R3K3 w Q - 0 1", ";D6 803711"},
    {"Peterellisjones position 15", "r3k2r/1b4bq/8/8/8/8/7B/R3K2R w KQkq - 0 1", ";D4 1274206"},
    {"Peterellisjones position 16", "r3k2r/8/3Q4/8/8/5q2/8/R3K2R b KQkq - 0 1", ";D4 1720476"},
    {"Peterellisjones position 17", "2K2r2/4P3/8/8/8/8/8/3k4 w - - 0 1", ";D6 3821001"},
    {"Peterellisjones position 18", "8/8/1P2K3/8/2n5/1q6/8/5k2 b - - 0 1", ";D5 1004658"},
    {"Peterellisjones position 19", "4k3/1P6/8/8/8/8/K7/8 w - - 0 1", ";D6 217342"},
    {"Peterellisjones position 20", "8/P1k5/K7/8/8/8/8/8 w - - 0 1", ";D6 92683"},
    {"Peterellisjones position 21", "K1k5/8/P7/8/8/8/8/8 w - - 0 1", ";D6 2217"},
    {"Peterellisjones position 22", "8/k1P5/8/1K6/8/8/8/8 w - - 0 1", ";D7 567584"},
    {"Peterellisjones position 23", "8/8/2k5/5q2/5n2/8/5K2/8 b - - 0 ", ";D4 23527"},

    // http://www.rocechess.ch/perft.html
    {"Start position", "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", ";D1 20 ;D2 400 ;D3 8902 ;D4 197281 ;D5 4865609"},
    {"Good test position", "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1", ";D1 48 ;D2 2039 ;D3 97862 ;D4 4085603"},
    {"Discover promotion bugs", "n1n5/PPPk4/8/8/8/8/4Kppp/5N1N b - - 0 1", ";D1 24 ;D2 496 ;D3 9483 ;D4 182838 ;D5 3605103"},
    {"Rocechess position 1", "4k3/8/8/8/8/8/8/4K2R w K - 0 1", ";D1 15 ;D2 66 ;D3 1197 ;D4 7059 ;D5 133987 ;D6 764643"},
    {"Rocechess position 2", "4k3/8/8/8/8/8/8/R3K3 w Q - 0 1", ";D1 16 ;D2 71 ;D3 1287 ;D4 7626 ;D5 145232 ;D6 846648"},
    {"Rocechess position 3", "4k2r/8/8/8/8/8/8/4K3 w k - 0 1", ";D1 5 ;D2 75 ;D3 459 ;D4 8290 ;D5 47635 ;D6 899442"},
    {"Rocechess position 4", "r3k3/8/8/8/8/8/8/4K3 w q - 0 1", ";D1 5 ;D2 80 ;D3 493 ;D4 8897 ;D5 52710 ;D6 1001523"},
    {"Rocechess position 5", "4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1", ";D1 26 ;D2 112 ;D3 3189 ;D4 17945 ;D5 532933 ;D6 2788982"},
    {"Rocechess position 6", "r3k2r/8/8/8/8/8/8/4K3 w kq - 0 1", ";D1 5 ;D2 130 ;D3 782 ;D4 22180 ;D5 118882 ;D6 3517770"},
    {"Rocechess position 7", "8/8/8/8/8/8/6k1/4K2R w K - 0 1", ";D1 12 ;D2 38 ;D3 564 ;D4 2219 ;D5 37735 ;D6 185867"},
    {"Rocechess position 8", "8/8/8/8/8/8/1k6/R3K3 w Q - 0 1", ";D1 15 ;D2 65 ;D3 1018 ;D4 4573 ;D5 80619 ;D6 413018"},
    {"Rocechess position 9", "4k2r/6K1/8/8/8/8/8/8 w k - 0 1", ";D1 3 ;D2 32 ;D3 134 ;D4 2073 ;D5 10485 ;D6 179869"},
    {"Rocechess position 10", "r3k3/1K6/8/8/8/8/8/8 w q - 0 1", ";D1 4 ;D2 49 ;D3 243 ;D4 3991 ;D5 20780 ;D6 367724"},
    {"Rocechess position 11", "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1", ";D1 26 ;D2 568 ;D3 13744 ;D4 314346 ;D5 7594526"},
    {"Rocechess position 12", "r3k2r/8/8/8/8/8/8/1R2K2R w Kkq - 0 1", ";D1 25 ;D2 567 ;D3 14095 ;D4 328965 ;D5 8153719"},
    {"Rocechess position 13", "r3k2r/8/8/8/8/8/8/2R1K2R w Kkq - 0 1", ";D1 25 ;D2 548 ;D3 13502 ;D4 312835 ;D5 7736373"},
    {"Rocechess position 14", "r3k2r/8/8/8/8/8/8/R3K1R1 w Qkq - 0 1", ";D1 25 ;D2 547 ;D3 13579 ;D4 316214 ;D5 7878456"},
    {"Rocechess position 15", "1r2k2r/8/8/8/8/8/8/R3K2R w KQk - 0 1", ";D1 26 ;D2 583 ;D3 14252 ;D4 334705 ;D5 8198901"},
    {"Rocechess position 16", "2r1k2r/8/8/8/8/8/8/R3K2R w KQk - 0 1", ";D1 25 ;D2 560 ;D3 13592 ;D4 317324 ;D5 7710115"},
    {"Rocechess position 17", "r3k1r1/8/8/8/8/8/8/R3K2R w KQq - 0 1", ";D1 25 ;D2 560 ;D3 13607 ;D4 320792 ;D5 7848606"},
    {"Rocechess position 18", "4k3/8/8/8/8/8/8/4K2R b K - 0 1", ";D1 5 ;D2 75 ;D3 459 ;D4 8290 ;D5 47635 ;D6 899442"},
    {"Rocechess position 19", "4k3/8/8/8/8/8/8/R3K3 b Q - 0 1", ";D1 5 ;D2 80 ;D3 493 ;D4 8897 ;D5 52710 ;D6 1001523"},
    {"Rocechess position 20", "4k2r/8/8/8/8/8/8/4K3 b k - 0 1", ";D1 15 ;D2 66 ;D3 1197 ;D4 7059 ;D5 133987 ;D6 764643"},
    {"Rocechess position 21", "r3k3/8/8/8/8/8/8/4K3 b q - 0 1", ";D1 16 ;D2 71 ;D3 1287 ;D4 7626 ;D5 145232 ;D6 846648"},
    {"Rocechess position 22", "4k3/8/8/8/8/8/8/R3K2R b KQ - 0 1", ";D1 5 ;D2 130 ;D3 782 ;D4 22180 ;D5 118882 ;D6 3517770"},
    {"Rocechess position 23", "r3k2r/8/8/8/8/8/8/4K3 b kq - 0 1", ";D1 26 ;D2 112 ;D3 3189 ;D4 17945 ;D5 532933 ;D6 2788982"},
    {"Rocechess position 24", "8/8/8/8/8/8/6k1/4K2R b K - 0 1", ";D1 3 ;D2 32 ;D3 134 ;D4 2073 ;D5 10485 ;D6 179869"},
    {"Rocechess position 25", "8/8/8/8/8/8/1k6/R3K3 b Q - 0 1", ";D1 4 ;D2 49 ;D3 243 ;D4 3991 ;D5 20780 ;D6 367724"},
    {"Rocechess position 26", "4k2r/6K1/8/8/8/8/8/8 b k - 0 1", ";D1 12 ;D2 38 ;D3 564 ;D4 2219 ;D5 37735 ;D6 185867"},
    {"Rocechess position 27", "r3k3/1K6/8/8/8/8/8/8 b q - 0 1", ";D1 15 ;D2 65 ;D3 1018 ;D4 4573 ;D5 80619 ;D6 413018"},
    {"Rocechess position 28", "r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1", ";D1 26 ;D2 568 ;D3 13744 ;D4 314346"},
    {"Rocechess position 29", "r3k2r/8/8/8/8/8/8/1R2K2R b Kkq - 0 1", ";D1 26 ;D2 583 ;D3 14252 ;D4 334705"},
    {"Rocechess position 30", "r3k2r/8/8/8/8/8/8/2R1K2R b Kkq - 0 1", ";D1 25 ;D2 560 ;D3 13592 ;D4 317324"},
    {"Rocechess position 31", "r3k2r/8/8/8/8/8/8/R3K1R1 b Qkq - 0 1", ";D1 25 ;D2 560 ;D3 13607 ;D4 320792"},
    {"Rocechess position 32", "1r2k2r/8/8/8/8/8/8/R3K2R b KQk - 0 1", ";D1 25 ;D2 567 ;D3 14095 ;D4 328965"},
    {"Rocechess position 33", "2r1k2r/8/8/8/8/8/8/R3K2R b KQk - 0 1", ";D1 25 ;D2 548 ;D3 13502 ;D4 312835"},
    {"Rocechess position 34", "r3k1r1/8/8/8/8/8/8/R3K2R b KQq - 0 1", ";D1 25 ;D2 547 ;D3 13579 ;D4 316214"},
    {"Rocechess position 35", "8/1n4N1/2k5/8/8/5K2/1N4n1/8 w - - 0 1", ";D1 14 ;D2 195 ;D3 2760 ;D4 38675 ;D5 570726"},
    {"Rocechess position 36", "8/1k6/8/5N2/8/4n3/8/2K5 w - - 0 1", ";D1 11 ;D2 156 ;D3 1636 ;D4 20534 ;D5 223507 ;D6 2594412"},
    {"Rocechess position 37", "8/8/4k3/3Nn3/3nN3/4K3/8/8 w - - 0 1", ";D1 19 ;D2 289 ;D3 4442 ;D4 73584 ;D5 1198299"},
    {"Rocechess position 38", "K7/8/2n5/1n6/8/8/8/k6N w - - 0 1", ";D1 3 ;D2 51 ;D3 345 ;D4 5301 ;D5 38348 ;D6 588695"},
    {"Rocechess position 39", "k7/8/2N5/1N6/8/8/8/K6n w - - 0 1", ";D1 17 ;D2 54 ;D3 835 ;D4 5910 ;D5 92250 ;D6 688780"},
    {"Rocechess position 40", "8/1n4N1/2k5/8/8/5K2/1N4n1/8 b - - 0 1", ";D1 15 ;D2 193 ;D3 2816 ;D4 40039 ;D5 582642"},
    {"Rocechess position 41", "8/1k6/8/5N2/8/4n3/8/2K5 b - - 0 1", ";D1 16 ;D2 180 ;D3 2290 ;D4 24640 ;D5 288141"},
    {"Rocechess position 42", "8/8/3K4/3Nn3/3nN3/4k3/8/8 b - - 0 1", ";D1 4 ;D2 68 ;D3 1118 ;D4 16199 ;D5 281190"},
    {"Rocechess position 43", "K7/8/2n5/1n6/8/8/8/k6N b - - 0 1", ";D1 17 ;D2 54 ;D3 835 ;D4 5910 ;D5 92250 ;D6 688780"},
    {"Rocechess position 44", "k7/8/2N5/1N6/8/8/8/K6n b - - 0 1", ";D1 3 ;D2 51 ;D3 345 ;D4 5301 ;D5 38348 ;D6 588695"},
    {"Rocechess position 45", "B6b/8/8/8/2K5/4k3/8/b6B w - - 0 1", ";D1 17 ;D2 278 ;D3 4607 ;D4 76778 ;D5 1320507"},
    {"Rocechess position 46", "8/8/1B6/7b/7k/8/2B1b3/7K w - - 0 1", ";D1 21 ;D2 316 ;D3 5744 ;D4 93338 ;D5 1713368"},
    {"Rocechess position 47", "k7/B7/1B6/1B6/8/8/8/K6b w - - 0 1", ";D1 21 ;D2 144 ;D3 3242 ;D4 32955 ;D5 787524"},
    {"Rocechess position 48", "K7/b7/1b6/1b6/8/8/8/k6B w - - 0 1", ";D1 7 ;D2 143 ;D3 1416 ;D4 31787 ;D5 310862"},
    {"Rocechess position 49", "B6b/8/8/8/2K5/5k2/8/b6B b - - 0 1", ";D1 6 ;D2 106 ;D3 1829 ;D4 31151 ;D5 530585"},
    {"Rocechess position 50", "8/8/1B6/7b/7k/8/2B1b3/7K b - - 0 1", ";D1 17 ;D2 309 ;D3 5133 ;D4 93603 ;D5 1591064"},
    {"Rocechess position 51", "k7/B7/1B6/1B6/8/8/8/K6b b - - 0 1", ";D1 7 ;D2 143 ;D3 1416 ;D4 31787 ;D5 310862"},
    {"Rocechess position 52", "K7/b7/1b6/1b6/8/8/8/k6B b - - 0 1", ";D1 21 ;D2 144 ;D3 3242 ;D4 32955 ;D5 787524"},
    {"Rocechess position 53", "7k/RR6/8/8/8/8/rr6/7K w - - 0 1", ";D1 19 ;D2 275 ;D3 5300 ;D4 104342 ;D5 2161211"},
    {"Rocechess position 54", "R6r/8/8/2K5/5k2/8/8/r6R w - - 0 1", ";D1 36 ;D2 1027 ;D3 29215 ;D4 771461 ;D5 20506480"},
    {"Rocechess position 55", "7k/RR6/8/8/8/8/rr6/7K b - - 0 1", ";D1 19 ;D2 275 ;D3 5300 ;D4 104342 ;D5 2161211"},
    {"Rocechess position 56", "R6r/8/8/2K5/5k2/8/8/r6R b - - 0 1", ";D1 36 ;D2 1027 ;D3 29227 ;D4 771368 ;D5 20521342"},
    {"Rocechess position 57", "6kq/8/8/8/8/8/8/7K w - - 0 1", ";D1 2 ;D2 36 ;D3 143 ;D4 3637 ;D5 14893 ;D6 391507"},
    {"Rocechess position 58", "6KQ/8/8/8/8/8/8/7k b - - 0 1", ";D1 2 ;D2 36 ;D3 143 ;D4 3637 ;D5 14893 ;D6 391507"},
    {"Rocechess position 59", "K7/8/8/3Q4/4q3/8/8/7k w - - 0 1", ";D1 6 ;D2 35 ;D3 495 ;D4 8349 ;D5 166741"},
    {"Rocechess position 60", "6qk/8/8/8/8/8/8/7K b - - 0 1", ";D1 22 ;D2 43 ;D3 1015 ;D4 4167 ;D5 105749 ;D6 419369"},
    {"Rocechess position 61", "6KQ/8/8/8/8/8/8/7k b - - 0 1", ";D1 2 ;D2 36 ;D3 143 ;D4 3637 ;D5 14893 ;D6 391507"},
    {"Rocechess position 62", "K7/8/8/3Q4/4q3/8/8/7k b - - 0 1", ";D1 6 ;D2 35 ;D3 495 ;D4 8349 ;D5 166741"},
    {"Rocechess position 63", "8/8/8/8/8/K7/P7/k7 w - - 0 1", ";D1 3 ;D2 7 ;D3 43 ;D4 199 ;D5 1347 ;D6 6249"},
    {"Rocechess position 64", "8/8/8/8/8/7K/7P/7k w - - 0 1", ";D1 3 ;D2 7 ;D3 43 ;D4 199 ;D5 1347 ;D6 6249"},
    {"Rocechess position 65", "K7/p7/k7/8/8/8/8/8 w - - 0 1", ";D1 1 ;D2 3 ;D3 12 ;D4 80 ;D5 342 ;D6 2343"},
    {"Rocechess position 66", "7K/7p/7k/8/8/8/8/8 w - - 0 1", ";D1 1 ;D2 3 ;D3 12 ;D4 80 ;D5 342 ;D6 2343"},
    {"Rocechess position 67", "8/2k1p3/3pP3/3P2K1/8/8/8/8 w - - 0 1", ";D1 7 ;D2 35 ;D3 210 ;D4 1091 ;D5 7028 ;D6 34834"},
    {"Rocechess position 68", "8/8/8/8/8/K7/P7/k7 b - - 0 1", ";D1 1 ;D2 3 ;D3 12 ;D4 80 ;D5 342 ;D6 2343"},
    {"Rocechess position 69", "8/8/8/8/8/7K/7P/7k b - - 0 1", ";D1 1 ;D2 3 ;D3 12 ;D4 80 ;D5 342 ;D6 2343"},
    {"Rocechess position 70", "K7/p7/k7/8/8/8/8/8 b - - 0 1", ";D1 3 ;D2 7 ;D3 43 ;D4 199 ;D5 1347 ;D6 6249"},
    {"Rocechess position 71", "7K/7p/7k/8/8/8/8/8 b - - 0 1", ";D1 3 ;D2 7 ;D3 43 ;D4 199 ;D5 1347 ;D6 6249"},
    {"Rocechess position 72", "8/2k1p3/3pP3/3P2K1/8/8/8/8 b - - 0 1", ";D1 5 ;D2 35 ;D3 182 ;D4 1091 ;D5 5408 ;D6 34822"},
    {"Rocechess position 73", "8/8/8/8/8/4k3/4P3/4K3 w - - 0 1", ";D1 2 ;D2 8 ;D3 44 ;D4 282 ;D5 1814 ;D6 11848"},
    {"Rocechess position 74", "4k3/4p3/4K3/8/8/8/8/8 b - - 0 1", ";D1 2 ;D2 8 ;D3 44 ;D4 282 ;D5 1814 ;D6 11848"},
    {"Rocechess position 75", "8/8/7k/7p/7P/7K/8/8 w - - 0 1", ";D1 3 ;D2 9 ;D3 57 ;D4 360 ;D5 1969 ;D6 10724"},
    {"Rocechess position 76", "8/8/k7/p7/P7/K7/8/8 w - - 0 1", ";D1 3 ;D2 9 ;D3 57 ;D4 360 ;D5 1969 ;D6 10724"},
    {"Rocechess position 77", "8/8/3k4/3p4/3P4/3K4/8/8 w - - 0 1", ";D1 5 ;D2 25 ;D3 180 ;D4 1294 ;D5 8296 ;D6 53138"},
    {"Rocechess position 78", "8/3k4/3p4/8/3P4/3K4/8/8 w - - 0 1", ";D1 8 ;D2 61 ;D3 483 ;D4 3213 ;D5 23599 ;D6 157093"},
    {"Rocechess position 79", "8/8/3k4/3p4/8/3P4/3K4/8 w - - 0 1", ";D1 8 ;D2 61 ;D3 411 ;D4 3213 ;D5 21637 ;D6 158065"},
    {"Rocechess position 80", "k7/8/3p4/8/3P4/8/8/7K w - - 0 1", ";D1 4 ;D2 15 ;D3 90 ;D4 534 ;D5 3450 ;D6 20960"},
    {"Rocechess position 81", "8/8/7k/7p/7P/7K/8/8 b - - 0 1", ";D1 3 ;D2 9 ;D3 57 ;D4 360 ;D5 1969 ;D6 10724"},
    {"Rocechess position 82", "8/8/k7/p7/P7/K7/8/8 b - - 0 1", ";D1 3 ;D2 9 ;D3 57 ;D4 360 ;D5 1969 ;D6 10724"},
    {"Rocechess position 83", "8/8/3k4/3p4/3P4/3K4/8/8 b - - 0 1", ";D1 5 ;D2 25 ;D3 180 ;D4 1294 ;D5 8296 ;D6 53138"},
    {"Rocechess position 84", "8/3k4/3p4/8/3P4/3K4/8/8 b - - 0 1", ";D1 8 ;D2 61 ;D3 411 ;D4 3213 ;D5 21637 ;D6 158065"},
    {"Rocechess position 85", "8/8/3k4/3p4/8/3P4/3K4/8 b - - 0 1", ";D1 8 ;D2 61 ;D3 483 ;D4 3213 ;D5 23599 ;D6 157093"},
    {"Rocechess position 86", "k7/8/3p4/8/3P4/8/8/7K b - - 0 1", ";D1 4 ;D2 15 ;D3 89 ;D4 537 ;D5 3309 ;D6 21104"},
    {"Rocechess position 87", "7k/3p4/8/8/3P4/8/8/K7 w - - 0 1", ";D1 4 ;D2 19 ;D3 117 ;D4 720 ;D5 4661 ;D6 32191"},
    {"Rocechess position 88", "7k/8/8/3p4/8/8/3P4/K7 w - - 0 1", ";D1 5 ;D2 19 ;D3 116 ;D4 716 ;D5 4786 ;D6 30980"},
    {"Rocechess position 89", "k7/8/8/7p/6P1/8/8/K7 w - - 0 1", ";D1 5 ;D2 22 ;D3 139 ;D4 877 ;D5 6112 ;D6 41874"},
    {"Rocechess position 90", "k7/8/7p/8/8/6P1/8/K7 w - - 0 1", ";D1 4 ;D2 16 ;D3 101 ;D4 637 ;D5 4354 ;D6 29679"},
    {"Rocechess position 91", "k7/8/8/6p1/7P/8/8/K7 w - - 0 1", ";D1 5 ;D2 22 ;D3 139 ;D4 877 ;D5 6112 ;D6 41874"},
    {"Rocechess position 92", "k7/8/6p1/8/8/7P/8/K7 w - - 0 1", ";D1 4 ;D2 16 ;D3 101 ;D4 637 ;D5 4354 ;D6 29679"},
    {"Rocechess position 93", "k7/8/8/3p4/4p3/8/8/7K w - - 0 1", ";D1 3 ;D2 15 ;D3 84 ;D4 573 ;D5 3013 ;D6 22886"},
    {"Rocechess position 94", "k7/8/3p4/8/8/4P3/8/7K w - - 0 1", ";D1 4 ;D2 16 ;D3 101 ;D4 637 ;D5 4271 ;D6 28662"},
    {"Rocechess position 95", "7k/3p4/8/8/3P4/8/8/K7 b - - 0 1", ";D1 5 ;D2 19 ;D3 117 ;D4 720 ;D5 5014 ;D6 32167"},
    {"Rocechess position 96", "7k/8/8/3p4/8/8/3P4/K7 b - - 0 1", ";D1 4 ;D2 19 ;D3 117 ;D4 712 ;D5 4658 ;D6 30749"},
    {"Rocechess position 97", "k7/8/8/7p/6P1/8/8/K7 b - - 0 1", ";D1 5 ;D2 22 ;D3 139 ;D4 877 ;D5 6112 ;D6 41874"},
    {"Rocechess position 98", "k7/8/7p/8/8/6P1/8/K7 b - - 0 1", ";D1 4 ;D2 16 ;D3 101 ;D4 637 ;D5 4354 ;D6 29679"},
    {"Rocechess position 99", "k7/8/8/6p1/7P/8/8/K7 b - - 0 1", ";D1 5 ;D2 22 ;D3 139 ;D4 877 ;D5 6112 ;D6 41874"},
    {"Rocechess position 100", "k7/8/6p1/8/8/7P/8/K7 b - - 0 1", ";D1 4 ;D2 16 ;D3 101 ;D4 637 ;D5 4354 ;D6 29679"},
    {"Rocechess position 101", "k7/8/8/3p4/4p3/8/8/7K b - - 0 1", ";D1 5 ;D2 15 ;D3 102 ;D4 569 ;D5 4337 ;D6 22579"},
    {"Rocechess position 102", "k7/8/3p4/8/8/4P3/8/7K b - - 0 1", ";D1 4 ;D2 16 ;D3 101 ;D4 637 ;D5 4271 ;D6 28662"},
    {"Rocechess position 103", "7k/8/8/p7/1P6/8/8/7K w - - 0 1", ";D1 5 ;D2 22 ;D3 139 ;D4 877 ;D5 6112 ;D6 41874"},
    {"Rocechess position 104", "7k/8/p7/8/8/1P6/8/7K w - - 0 1", ";D1 4 ;D2 16 ;D3 101 ;D4 637 ;D5 4354 ;D6 29679"},
    {"Rocechess position 105", "7k/8/8/1p6/P7/8/8/7K w - - 0 1", ";D1 5 ;D2 22 ;D3 139 ;D4 877 ;D5 6112 ;D6 41874"},
    {"Rocechess position 106", "7k/8/1p6/8/8/P7/8/7K w - - 0 1", ";D1 4 ;D2 16 ;D3 101 ;D4 637 ;D5 4354 ;D6 29679"},
    {"Rocechess position 107", "k7/7p/8/8/8/8/6P1/K7 w - - 0 1", ";D1 5 ;D2 25 ;D3 161 ;D4 1035 ;D5 7574 ;D6 55338"},
    {"Rocechess position 108", "k7/6p1/8/8/8/8/7P/K7 w - - 0 1", ";D1 5 ;D2 25 ;D3 161 ;D4 1035 ;D5 7574 ;D6 55338"},
    {"Rocechess position 109", "3k4/3pp3/8/8/8/8/3PP3/3K4 w - - 0 1", ";D1 7 ;D2 49 ;D3 378 ;D4 2902 ;D5 24122 ;D6 199002"},
    {"Rocechess position 110", "7k/8/8/p7/1P6/8/8/7K b - - 0 1", ";D1 5 ;D2 22 ;D3 139 ;D4 877 ;D5 6112 ;D6 41874"},
    {"Rocechess position 111", "7k/8/p7/8/8/1P6/8/7K b - - 0 1", ";D1 4 ;D2 16 ;D3 101 ;D4 637 ;D5 4354 ;D6 29679"},
    {"Rocechess position 112", "7k/8/8/1p6/P7/8/8/7K b - - 0 1", ";D1 5 ;D2 22 ;D3 139 ;D4 877 ;D5 6112 ;D6 41874"},
    {"Rocechess position 113", "7k/8/1p6/8/8/P7/8/7K b - - 0 1", ";D1 4 ;D2 16 ;D3 101 ;D4 637 ;D5 4354 ;D6 29679"},
    {"Rocechess position 114", "k7/7p/8/8/8/8/6P1/K7 b - - 0 1", ";D1 5 ;D2 25 ;D3 161 ;D4 1035 ;D5 7574 ;D6 55338"},
    {"Rocechess position 115", "k7/6p1/8/8/8/8/7P/K7 b - - 0 1", ";D1 5 ;D2 25 ;D3 161 ;D4 1035 ;D5 7574 ;D6 55338"},
    {"Rocechess position 116", "3k4/3pp3/8/8/8/8/3PP3/3K4 b - - 0 1", ";D1 7 ;D2 49 ;D3 378 ;D4 2902 ;D5 24122 ;D6 199002"},
    {"Rocechess position 117", "8/Pk6/8/8/8/8/6Kp/8 w - - 0 1", ";D1 11 ;D2 97 ;D3 887 ;D4 8048 ;D5 90606 ;D6 1030499"},
    {"Rocechess position 118", "n1n5/1Pk5/8/8/8/8/5Kp1/5N1N w - - 0 1", ";D1 24 ;D2 421 ;D3 7421 ;D4 124608 ;D5 2193768"},
    {"Rocechess position 119", "8/PPPk4/8/8/8/8/4Kppp/8 w - - 0 1", ";D1 18 ;D2 270 ;D3 4699 ;D4 79355 ;D5 1533145"},
    {"Rocechess position 120", "n1n5/PPPk4/8/8/8/8/4Kppp/5N1N w - - 0 1", ";D1 24 ;D2 496 ;D3 9483 ;D4 182838"},
    {"Rocechess position 121", "8/Pk6/8/8/8/8/6Kp/8 b - - 0 1", ";D1 11 ;D2 97 ;D3 887 ;D4 8048 ;D5 90606 ;D6 1030499"},
    {"Rocechess position 122", "n1n5/1Pk5/8/8/8/8/5Kp1/5N1N b - - 0 1", ";D1 24 ;D2 421 ;D3 7421 ;D4 124608"},
    {"Rocechess position 123", "8/PPPk4/8/8/8/8/4Kppp/8 b - - 0 1", ";D1 18 ;D2 270 ;D3 4699 ;D4 79355"}
};

const int len = sizeof(testcases) / sizeof(testcases[0]);

int perft(Board *board, int depth) {
    if (depth == 0)
        return 1;

    MoveList list;
    list.count = 0;
    generate_moves(board, &list);

    int nodes = 0;
    for (int i = 0; i < list.count; i++) {
        Move *move = &list.moves[i];
        apply_move(board, move);
        nodes += perft(board, depth - 1);
        undo_move(board, move);
    }

    return nodes;
}

void perft_tests(void) {
    double total_time = 0;
    long long int total_moves = 0;

    for (int i = 0; i < len; i++) {
        PerftTestCase *test = &testcases[i];
        Board board;

        printf("\n[TEST %d] \nTest name: %s\nFEN: %s\n", i + 1, test->name, test->fen);
        if (!loadFEN(&board, test->fen)) {
            fprintf(stderr, "Failed to load FEN\n");
            exit(1);
        }

        printf("|----------------------------------------------------------------------|\n");
        printf("| %-8s | %-12s | %-12s | %-12s | %-12s |\n",
                       "Depth", "Generated", "Expected", "Time (s)", "NPS");
        printf("|----------------------------------------------------------------------|\n");

        char depth[256];
        strcpy(depth, test->depth);
        char *token = strtok(depth, ";");
        while (token) {
            int depth, expected;
            if (sscanf(token, "D%d %d", &depth, &expected) != 2) {
                fprintf(stderr, "Failed to parse depth and expected result\n");
                exit(1);
            }

            clock_t start = clock();
            int moves = perft(&board, depth);
            clock_t end = clock();
            double time = (double)(end - start) / CLOCKS_PER_SEC;
            double nps = (moves / time);
            total_time += time;
            total_moves += moves;
            printf("| %-8d | %-12d | %-12d | %-12.4f | %-12.0f |\n",
                               depth, moves, expected, time, nps);
            printf("|----------------------------------------------------------------------|\n");

            assert(moves == expected);
            token = strtok(NULL, ";");
        }

    }

    printf("\n[TESTS SUMMARY]");
    printf("\n|----------------------------------------------|\n");
    printf("| %-12s | %-12s | %-12s |\n",
                "Total Moves", "Total Time (s)", "Average NPS");
    printf("|----------------------------------------------|\n");
    printf("| %-12lld | %-14.4f | %-12.0f |\n", total_moves, total_time, (double)total_moves / total_time);
    printf("|----------------------------------------------|\n\n");
}

int main(void) {
    init_moves();
    perft_tests();

    return 0;
}
