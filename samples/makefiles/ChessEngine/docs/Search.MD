## Basic Idea

First, it should be established that a chess game can be represented as a massive tree of a very large number of nodes, where each node represents a chess position, and all the legal moves at that position lead to the children nodes, which are new chess positions.
Searching for the "sub-tree" of moves that lead to the most beneficial outcome for the current player is the core of every chess engine, and at the heart of this search algorithm is [Minimax](https://en.wikipedia.org/wiki/Minimax).

## Minimax

Minimax is a recursive algorithm which calculates the best possible outcome for one player by looking through all the possible sub-trees of moves and returning the one that leads to a chess position with the most beneficial static evaluation, at a given max depth.
As one can deduce from the Evaluation function that is used, white is always trying to maximize the evaluation of the position, while black is trying to minimize it (hence the name Minimax). It should of course be mentioned that minimax is called up to a certain
depth, since the tree is very large. Therefore, a higher depth means that the engine is looking "further" into the future of the chess position, and therefore more accurate, but more computationally expensive.

The pseudocode for minimax (from wikipedia), looks something like this:
```
function minimax(node, depth, maximizingPlayer) is
    if depth = 0 or node is a terminal node then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, minimax(child, depth − 1, FALSE))
        return value
    else (* minimizing player *)
        value := +∞
        for each child of node do
            value := min(value, minimax(child, depth − 1, TRUE))
        return value
```

Where the maximizing player is white, and the miniminzg player is black. Each recursive call decrements the depth by one, and when depth 0 is reached, we call our evaluation function to give us the static evaluation of the chess position.
(Of course, slight modification to this pseudocode is done in order to save the actual move as well)

At this point, **FeohZero** is now a functional chess engine that can consistently run at about depth 4 at a sub-5 second runtime.

## AB-Prune

A very significant optimization for minimax can be made through the use of [Alpha-Beta Pruning](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning). The idea of the AB-Prune is that not all sub-trees of a chess position need to be searched.
This is true because as one can see, from a tree such as [this](https://prnt.sc/m6LeY_CL9sTw), by saving an upper (alpha) or lower (beta) value of the current most favourable evaluation, based on whose turn it is, there is no need to search sub-trees
which are guaranteed to give a less favourable evaluation. (In the example shown, White has a move where the evaluation is atleast 6, and in the right-most sub-tree, black has an evaluation of at most 5, therefore white would always choose the middle move).

The pseudocode of AB-Prune is the following (wiki), which results from simply storing an upper/lower bound of the score.
```
function alphabeta(node, depth, α, β, maximizingPlayer) is
    if depth == 0 or node is terminal then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, alphabeta(child, depth − 1, α, β, FALSE))
            if value > β then
                break (* β cutoff *)
            α := max(α, value)
        return value
    else
        value := +∞
        for each child of node do
            value := min(value, alphabeta(child, depth − 1, α, β, TRUE))
            if value < α then
                break (* α cutoff *)
            β := min(β, value)
        return value
```

For reference, the use of AB-Prune instead of minimax gave **FeohZero** a depth increase of 2 (for the same runtime), which is very significant.

One important thing to note here is that, in the above example, had the nodes containing 8 and 5 in the right-most sub-tree been inverted, pruning would not have been possible. From this, we can deduce that the correct ordering of the moves, from best to worse,
will lead to more prunes, and therefore a way more efficient search. This brings us to our next chapter:

## Move Ordering

A most vital aspect for an efficient AB-Prune search is correct move ordering. That being said, it is difficult to judge a move as "good" or "bad", without actually searching them. Therefore, the move ordering is done using heuristics. **FeohZero** relies on a couple of smart heuristics in order to maximize pruning. Each move has a score assigned to it upon generation. Capture moves and castling are considered "likely to be good moves", whereas en passant is much worse in comparison. The best move-ordering trick though is undoubtedly through the use of [Iterative-Deepening Search](https://en.wikipedia.org/wiki/Iterative_deepening_depth-first_search).

Just from this simple move-ordering, we got a good speed increase through doubling of the prunes.

## Iterative-Deepening Search

Iterative-Deepening Search (IDS) is the algorithm we will use to traverse the chess tree. It is quite simple in nature, as it essentially consists of a depth-limited DFS (depth-first search), that is ran *depth* times, for each depth up to a max depth. While we originally thought this would hinder performance, it is necessary to use in order to satisfy the timeout requirement, and as it turns out, it actually improves the move-ordering, hence more speed. Essentially, since we do not know when the program will exit, it is necessary to start at a low depth, and call the depth limited search for that depth, in order to store a good move, in case the program needs to time out because of the time restrictions, and then gradually increase that depth limit. The neat trick here is that
we can use the best move from one iteration for the next, because it is very likely to be a good move, which would result in a very good prune. Therefore, we place this move at the "left-most" part of the tree.

## Closing Thoughts

At this point, the engine is pretty much complete and pretty neatly optimized. The engine at this point can probably run at about depth 7 at a reasonable time.

For further performance use, we also use a transposition table (Analysed at a different file). If one wishes to improve upon the search even more, it is advisable that they implement more heuristics, such as the [Killer Heuristic](https://www.chessprogramming.org/Killer_Heuristic), the [History Heuristic](https://www.chessprogramming.org/History_Heuristic), or techniques such as the [Quiescence Search](https://www.chessprogramming.org/Quiescence_Search).


## Sources
1. [Minimax](https://www.chessprogramming.org/Minimax)
2. [Minimax Visualized](https://www.youtube.com/watch?v=l-hh51ncgDI)
3. [AB-Prune](https://www.chessprogramming.org/Alpha-Beta#:~:text=The%20Alpha%2DBeta%20algorithm%20Alpha,of%20overlooking%20a%20better%20move.)
4. [Move-Ordering](https://www.chessprogramming.org/Move_Ordering)
5. [Iterative Deepening Search](https://www.chessprogramming.org/Iterative_Deepening)
