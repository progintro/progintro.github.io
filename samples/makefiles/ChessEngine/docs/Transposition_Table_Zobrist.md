## Basic Idea

While searching through the chess tree, it is quite likely that we reach a position that we have reached before, but from a different sequene of moves (a transposition). Hence, similiar to dynamic programming, there is no need to evaluate that position again,
assuming we have stored the result earlier. The chances of encountering the same position again is especially likely in an iterative deepening framework, and as such, fits greatly into FeohZero. Therefore, all we have to do is store the results of a search
inside a [Transposition Table](https://www.chessprogramming.org/Transposition_Table), and probe it during search to see if a chess position has been stored in it in the past

## Zobrist Hashing

In order to be able to identify a chess position, we need to hash its information into a key that we will later look up during the search, to identify if we've reached that position before. This is done through [Zobrist Hashing](https://www.chessprogramming.org/Zobrist_Hashing)
The idea is quite simple, we firstly initialize some random keys for the information of the board (piece positions, castling rights, turn, etc) and then make a key by XORing that information in and out after each move. This way, we have an (almost) unique key for each position.
This hashing method is not perfect, as a 64bit key is obviously not large enough to distinguish between every possible chess position.

Collisions are handled by replacing old entries with newer ones, if the depth is higher/equal. Note that there is a way to improve this collision handling, by using two tables, where one always replaces older entries, while the other one replaces if the depth is higher.
While this was not tested in FeohZero, it presumably gives better performance and it is advised that it be implemented, should someone wish to improve this engine further.

## Transposition Table

The transposition table in FeohZero is 16 megabytes (subject to change) and has two basic functions: A function to store entries (moves) and a function to "probe" the table, which means check for the existence of a key, or in other words, if a position has been evaluated
before. Each move stored has a flag, UPPER, LOWER, or EXACT, depending on whether it caused or a prune and therefore it's evaluation was not calculated or not. UPPER means it was pruned and its value is *at most* alpha, LOWER means its value is *at least* beta, and exact
means the value is the value of that node (its static evaluation). If it's exact, we simply return that value, otherwise, we update alpha and beta, if that value is higher than current alpha or lower the current beta and check for a prune again. So this way,
instead of discarding moves that have caused a prune, we can utilize them through the Transposition table. If a prune does not occur, we still do use the best move from the TT table for that position in the move ordering, searching it first, as it is more likely to give
a good result, and therefore more prunes.

## Sources

The following sources from Bruce Moreland were incredibly useful for implementing the transposition table in **FeohZero**!
1. [Zobrist Hashing](https://web.archive.org/web/20071031100138/http://www.brucemo.com/compchess/programming/zobrist.htm)
2. [Transposition Table](https://web.archive.org/web/20071031100051/http://www.brucemo.com/compchess/programming/hashing.htm)
