## Basic Idea
At the core of any chess engine is the ability to generate all legal moves for a given position. This is a critical step because the engine must explore a vast tree of possible moves to determine the best course of action. The move generator is responsible for computing all possible moves for each piece on the board, while ensuring that the moves are legal (e.g., they don't leave the king in check). This program implements an efficient move generator using magic bitboards, a technique that leverages precomputed attack tables to quickly compute sliding piece moves (bishops, rooks, and queens).

## Magic Bitboards
Magic bitboards are a highly optimized method for generating sliding piece moves. The key idea is to use **magic numbers** to hash the occupancy of squares (i.e., which squares are blocked by other pieces) into a compact index, which is then used to look up precomputed attack tables. This allows the program to compute sliding piece moves in constant time, making it extremely efficient.

The magic bitboard implementation in this program is inspired by [MisterQueen](https://github.com/fogleman/MisterQueen/blob/master/src/bb.c), with additional optimizations and customizations.

## Move Generation
The program generates moves for all pieces, including pawns, knights, bishops, rooks, queens, and kings. It also handles special moves such as castling, en passant, and promotions.
- **Sliding Pieces (Bishops, Rooks, Queens):**
Moves are generated using magic bitboards. The program computes the attack mask for each sliding piece based on the current board state and looks up the precomputed attack table to determine valid moves.
- **Pawns:**
Pawn moves include single pushes, double pushes, captures, and promotions. The `generate_pawn_moves` function computes all possible pawn moves for a given position, ensuring that they are legal.
- **Knights and Kings**:
Moves for knights and kings are computed using precomputed lookup tables (LUTs). Each square has a precomputed bitboard representing all possible moves for the knight or king, which is then filtered based on the current board state.
- **Castling**:
The program checks if castling is legal based on the current board state, including whether the king or rook has moved, whether the squares between them are empty, and whether the king is in check.
The `generate_castling` function handles the generation of castling moves.
- **En Passant**:
The program checks if an en passant capture is possible based on the current board state and the position of the opponent's pawn.
The `generate_en_passant` function handles the generation of en passant moves.

## Pinned Pieces and Legal Move Generation
The program uses an optimized approach to generate legal moves by first generating pseudo-legal moves (moves that don't account for pins or checks) and then filtering out invalid ones by applying them. This method is inspired by [Peter Ellis Jones' article](https://peterellisjones.com/posts/generating-legal-chess-moves-efficiently/), which emphasizes efficiency and correctness.

Pinned pieces are identified by checking if a sliding piece (bishop, rook, or queen) is attacking the king along a line. Moves of pinned pieces are restricted to squares that maintain the pin, ensuring the king remains safe. If the king is in check, only moves that block the check, capture the attacker, or move the king are legal. The program identifies all pieces giving check and computes the squares that can block or capture the attacker. This approach is efficient because generating pseudo-legal moves is fast, and only moves that might expose the king are validated, reducing the number of expensive legality checks. By combining pseudo-legal move generation with efficient filtering, the program ensures all moves are legal without sacrificing performance.

## Perft tests
To ensure the correctness of the move generator, the program includes Perft tests (performance tests). These tests count the number of legal moves at a given depth and compare the results to known values. This helps verify that the move generator is working correctly and efficiently.
Here are the benchmarks from the perft tests of the **FeohZero** engine's move generation:
```
[TESTS SUMMARY]
|----------------------------------------------|
| Total Moves  | Total Time (s) | Average NPS  |
|----------------------------------------------|
| 200345215    | 4.7119         | 42518689     |
|----------------------------------------------|
```

## Sources
1. [Magic bitboards info](https://www.chessprogramming.org/Magic_Bitboards)
2. [Magic bitboards explanation](http://pradu.us/old/Nov27_2008/Buzz/research/magic/Bitboards.pdf)
3. [Magic bitboards hashing keys source](https://github.com/fogleman/MisterQueen/blob/master/src/bb.c)
4. [Further insights about magic bitboards](https://backscattering.de/magics2.pdf)
5. [Legal move generation info](https://www.chessprogramming.org/Move_Generation#:~:text=In%20Legal%20move%20generation%2C%20as,when%20en%20passant%20is%20involved.)
6. [Legal move generation insparation article](https://peterellisjones.com/posts/generating-legal-chess-moves-efficiently/)
7. [An interactive FEN board viewer helped in debugging](https://www.redhotpawn.com/chess/chess-fen-viewer.php)
8. [Perft tests info](https://www.chessprogramming.org/Perft_Results)
9. [Perft tests source 1](https://www.chessprogramming.net/perfect-perft/)
10. [Perft tests source 2](http://www.rocechess.ch/perft.html)
11. [Perft tests source 3](https://gist.github.com/peterellisjones/8c46c28141c162d1d8a0f0badbc9cff9?permalink_comment_id=3775288)
