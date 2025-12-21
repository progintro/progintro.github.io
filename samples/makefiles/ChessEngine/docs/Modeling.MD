## Basic Idea

There are many ways to represent a chess board. One of the most efficient ways to do so is through the use of [Bitboards](https://www.chessprogramming.org/Bitboards). The idea is that since we have an 8x8 board, we can represent each piece's position through the use of a
64-bit unsigned integer, with a `1` in the i-th bit signifying that there's a piece of that type on the i-th square (Similiar logic to one-hot encoding). This means that the represantion of our board happens through the use of 12 bitboards, one for each piece of each colour.
This way of representing the chess board allows for memory efficiency, since we only need 12 U64 (unsigned 64 integers) to represent our board, as well as speed, since we will be using bitwise operations.

The aforementioned bitboards will be stored in a struct `Board`, along with other useful information, such as castling rights, a possible en passant square, a Zobrist key, as well as other miscellaneous information obtained from the [FEN](https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation).
In this structs are included additional bitboards to store the squares occupied by white, black or both.

## FEN

Before continuing, a brief mention of FENs: we made a very simple function that reads the FEN and stores all the information given in a struct Board. The implementation of the function is fairly simple, it simply reads the string from start to finish, looking at each
character individually, and expects a strict format, meaning invalid FEN formats will not be detected, and the engine will likely crash. It is called at the very beginning of the program.

## Moves

Modelization of Moves is quite simple: In a struct `Move` we store the type of the piece moving, its original and final position. Other information is also stored, such as a bit of information about the board before the making of move, such as castling rights and en passant
square, as well as MoveFlags (for Castling, En passant, captures, etc) that will be useful later.

## Making-Unmaking Moves

The process of making-unmaking moves is straight-forward. In an appropriate function `apply_move()` we change the bitboards of the moving or potentially captured/promoted pieces, as well as the relevant information, such as castling rights, EP square and turn to play.
Unmaking moves mirrors this logic.

## Sources
1. [Bitboards](https://www.chessprogramming.org/Bitboards)
