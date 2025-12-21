## Abstract

The `docs` folder contains MD (Markdown) files that document the process followed for the implementation of our chess engine, **FeohZero** (written in C). It also references sources that were used during the implementation, as well possible improvements that could be made.

In summary, the implementation of the engine consists of the following parts:
- **Modeling:** A foundamental task, where we have to encode the chess board as well as various chess rules in our engine.
- **Move Generation:** All possible (legal) moves have to be generated in order eventually choose one of them.
- **Evaluation:** The static evaluation of a chess position must be calculated, or in other words, which player the current position favours the most, in order to judge the strength of a move.
- **Search:**  The engine searches through the generated moves to identify the one that maximizes the player's advantage, using the evaluation mentioned above.
