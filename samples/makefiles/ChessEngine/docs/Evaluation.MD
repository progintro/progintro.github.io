## Basic Idea

In order to finally search through all of the possible legal moves, we need to be able to judge how beneficial a move is for the player. In order to do so, we're going to need to evaluate a chess position to figure out which player is winning.
Evaluating a chess position can be really complex. In real analysis of a position, one must take into account a plethora of factors, such as total material, development of pieces, king safety, and much more.

**FeohZero** analyses a position based on:
- Material count
- Quality of each piece
- Game Phase (Tapered eval)
- Doubled pawns
- King safety

## Material Count and PSTs

Material count is pretty straight forward. We assign a certain value to each piece and sum these values for each side. The quality of each piece is judged through the use of [Piece-Square Tables](https://www.chessprogramming.org/Piece-Square_Tables).
These are 64 integer arrays that store a value for each piece, for each square. This means that we assign a bonus or a penalty to each piece, depending on its position on the board. For example, a knight on the edge of the board is deemed to be quite bad,
so we assign a penalty to it. If it's closer to the center, we deem it to be better, so we assign it a bonus. The same logic is done for each piece.

## Tapered Eval
We actually have 2 of these tables for each piece, an MG (middle game) table and an EG (endgame) table, in order to more accurately assign these bonuses based on the phase of the game. This is more well-known as
[Tapered Eval](https://www.chessprogramming.org/Tapered_Eval#:~:text=a%20technique%20used%20in%20evaluation,of%20captured%20pieces%20so%20far). The Game Phase is calculated by giving a game_phase_value to each piece and adding them.
For example, a queen is worth 4 game_phase_points, and so it brings the "phase" of the game closer to a middlegame than an endgame. In the end, we will use a simple formula to give more "significance" to either the middle game or endgame table.

- The final evaluation of the position is calculated by substracting from the total white "score" the black "score".

## Doubled Pawns / King Safety
An extra criteria for assigning bonuses and penalties is counting doubled pawns and calculating king's safety. These two are calculated quite naively, but experimentally they seemed to increase the engine's elo by quite a bit. The mechanism is quite simple,
simply "loop" through every file on the board and count the amount of pawns in each one. Having multiple pawns on one file makes them doubled, and therefore a penalty is assigned for "bad pawn strucutre". King safety is calculated by looking for pawns in front of
the king, and checking if the file the king is in is "open" and therefore more vulnerable.

## Closing Thoughts
The current evaluation function is generally quite simple and could be improved quite a bit, by adding more criteria to the evaluation of a position. Significant improvements can be made through the use of [Texel Tuning](https://www.chessprogramming.org/Texel%27s_Tuning_Method) or much better, [NNUE](https://www.chessprogramming.org/NNUE). That being said, a complex evaluation function means a negative impact on the depth the engine runs at, because of slower computation time.
Having said that, we decided that a simple evaluation function is better for a simple chess engine, so as to maintain a relatively high depth.

## Sources
1. [Evaluation](https://www.chessprogramming.org/Evaluation)
2. [PeSTO's evaluation function](https://www.chessprogramming.org/PeSTO%27s_Evaluation_Function)
3. [Piece-Square Tables (from PeSTO)](http://www.talkchess.com/forum3/viewtopic.php?f=2&t=68311&start=19)
4. [Tapered Evaluation](https://www.chessprogramming.org/Tapered_Eval#:~:text=a%20technique%20used%20in%20evaluation,of%20captured%20pieces%20so%20far.)
