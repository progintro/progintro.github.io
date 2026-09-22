#!/usr/bin/env python3
"""Render the Go panel of the landing-page montage (assets/img/montage-25.png).

The 2025-26 final assignment was a Go engine (progintro/hw3), and the montage had
nothing from it. The tournament data the arena publishes - ~uoabot/go_scores.json -
records only per-game metadata: `moves` is a count, not a move list, and the sibling
paths that would hold game records are not public. So there is no real student game
to draw. This script synthesises one instead.

The position is *illustrative*, and the alt text in _layouts/default.html says so. It
is not a game any team played. What it is not is nonsense: the stones come from a
playout of legal moves, and `assert_alive` refuses to render a board where some group
has no liberties, which is the thing a Go player would notice immediately.

Deterministic: SEED fixes the position, so re-running reproduces the committed PNG
byte for byte. Change SEED to draw a different one.

    python3 tools/goboard.py

Palette is sampled from the chessboard already in the montage rather than invented -
see PALETTE below.
"""

import random

from PIL import Image, ImageDraw

SIZE = 19                     # 19x19, as the assignment specifies
SEED = 20260922
TARGET_STONES = 140           # busy enough to read as a real game, not a wall of stone
OUT = "assets/img/montage-25.png"

# Sampled from montage-23-24.png: the chess board is the lichess pair, light #f0d9b5
# on dark #b58863. The board field sits between the two so the Go panel reads as part
# of the same band rather than a new colour scheme.
PALETTE = {
    "panel": (255, 255, 255),
    "field": (232, 199, 154),     # #e8c79a
    "line": (107, 74, 47),        # #6b4a2f, a darkened #b58863
    "black": (26, 26, 26),        # #1a1a1a, the chess set's black
    "white": (247, 244, 238),     # #f7f4ee
}

SCALE = 2                     # render at 2x and downsample; cheap antialiasing
OUT_PX = 460                  # matches montage-23-24.png's height
MARGIN = 9                    # small inset; the other montage panels are full-bleed

EMPTY, BLACK, WHITE = 0, 1, 2


# --------------------------------------------------------------------------- rules

def neighbours(x, y):
    if x > 0:
        yield x - 1, y
    if x < SIZE - 1:
        yield x + 1, y
    if y > 0:
        yield x, y - 1
    if y < SIZE - 1:
        yield x, y + 1


def group_and_liberties(board, x, y):
    """The solidly-connected group containing (x, y), and its liberty count."""
    colour = board[y][x]
    seen = {(x, y)}
    stack = [(x, y)]
    liberties = set()
    while stack:
        cx, cy = stack.pop()
        for nx, ny in neighbours(cx, cy):
            if board[ny][nx] == EMPTY:
                liberties.add((nx, ny))
            elif board[ny][nx] == colour and (nx, ny) not in seen:
                seen.add((nx, ny))
                stack.append((nx, ny))
    return seen, len(liberties)


def play(board, x, y, colour):
    """Try to play a stone. Returns the captured stones, or None if the move is illegal.

    Handles capture and forbids suicide. Ko is handled by the caller, which refuses to
    recreate the immediately-previous position.
    """
    if board[y][x] != EMPTY:
        return None
    board[y][x] = colour
    opponent = BLACK if colour == WHITE else WHITE

    captured = set()
    for nx, ny in neighbours(x, y):
        if board[ny][nx] == opponent:
            group, libs = group_and_liberties(board, nx, ny)
            if libs == 0:
                captured |= group
    for cx, cy in captured:
        board[cy][cx] = EMPTY

    if not captured:
        _, libs = group_and_liberties(board, x, y)
        if libs == 0:            # suicide
            board[y][x] = EMPTY
            return None
    return captured


def snapshot(board):
    return tuple(tuple(row) for row in board)


# The 4-4, 3-4 and 4-3 points of each corner. Real games open in the corners, and
# starting there is most of what stops a playout looking like scattered confetti.
def opening_points():
    near, far = 3, SIZE - 4
    corners = [(near, near), (far, near), (near, far), (far, far)]
    extra = [(2, 3), (SIZE - 3, 3), (2, SIZE - 4), (SIZE - 3, SIZE - 4)]
    return corners + extra


def fills_own_eye(board, x, y, colour):
    """True if every neighbour is already our own stone.

    Engines avoid filling their own eyes and so do humans; allowing it produces solid
    blobs with no shape, which is the other half of why naive playouts look fake.
    """
    ns = list(neighbours(x, y))
    return all(board[ny][nx] == colour for nx, ny in ns)


def weights(board, colour, rng):
    """Score empty points, preferring play near existing stones.

    Uniformly random legal moves spread evenly over the board and never build a group.
    Weighting by proximity to stones already played - own stones to extend, the
    opponent's to make contact - is what produces connected shapes and territory.
    """
    stones = [(x, y, board[y][x])
              for y in range(SIZE) for x in range(SIZE) if board[y][x] != EMPTY]
    scored = []
    for y in range(SIZE):
        for x in range(SIZE):
            if board[y][x] != EMPTY or fills_own_eye(board, x, y, colour):
                continue
            w = 0.05                       # small floor, so a new area can still start
            for sx, sy, sc in stones:
                d = max(abs(sx - x), abs(sy - y))
                if d <= 3:
                    w += (4.0 if sc != colour else 3.0) / (d * d)
            # Keep play off the very edge unless something is already nearby.
            if x in (0, SIZE - 1) or y in (0, SIZE - 1):
                w *= 0.25
            scored.append(((x, y), w))
    return scored


def playout(seed, target):
    """Play legal, plausibly-shaped moves until the board carries roughly `target` stones."""
    rng = random.Random(seed)
    board = [[EMPTY] * SIZE for _ in range(SIZE)]
    previous = None               # for the simple ko rule
    colour = BLACK
    passes = 0

    # Open in the corners, alternating, the way a real game does.
    opening = opening_points()
    rng.shuffle(opening)
    for x, y in opening[:6]:
        if play(board, x, y, colour) is not None:
            colour = WHITE if colour == BLACK else BLACK

    while sum(c != EMPTY for row in board for c in row) < target and passes < 2:
        scored = weights(board, colour, rng)
        if not scored:
            break
        points = [p for p, _ in scored]
        ws = [w for _, w in scored]
        played = False
        # Draw candidates by weight; fall back through them if a draw is illegal.
        for _ in range(60):
            x, y = rng.choices(points, weights=ws, k=1)[0]
            before = snapshot(board)
            captured = play(board, x, y, colour)
            if captured is None:
                continue
            if snapshot(board) == previous:      # ko: would repeat the last position
                for cx, cy in captured:
                    board[cy][cx] = BLACK if colour == WHITE else WHITE
                board[y][x] = EMPTY
                continue
            previous = before
            played = True
            break
        passes = 0 if played else passes + 1
        colour = WHITE if colour == BLACK else BLACK

    return board


def assert_alive(board):
    """Every group on the board must have at least one liberty.

    A dead group left sitting on the board is exactly what makes a synthesised position
    look fake, so this is a hard failure rather than a warning.
    """
    checked = set()
    for y in range(SIZE):
        for x in range(SIZE):
            if board[y][x] == EMPTY or (x, y) in checked:
                continue
            group, libs = group_and_liberties(board, x, y)
            checked |= group
            assert libs > 0, f"group at {(x, y)} has no liberties"


# ------------------------------------------------------------------------- drawing

def render(board):
    px = OUT_PX * SCALE
    margin = MARGIN * SCALE
    img = Image.new("RGB", (px, px), PALETTE["panel"])
    d = ImageDraw.Draw(img)

    # The board field, inset from the panel edge.
    d.rectangle([margin, margin, px - margin, px - margin], fill=PALETTE["field"])

    # Grid. `step` is the distance between adjacent lines; the outermost lines sit half
    # a step inside the field so stones on the first line are not clipped by the edge.
    inner = px - 2 * margin
    step = inner / (SIZE + 1)
    origin = margin + step

    def pos(i):
        return origin + i * step

    width = max(1, round(1.1 * SCALE))
    for i in range(SIZE):
        d.line([(pos(0), pos(i)), (pos(SIZE - 1), pos(i))], fill=PALETTE["line"], width=width)
        d.line([(pos(i), pos(0)), (pos(i), pos(SIZE - 1))], fill=PALETTE["line"], width=width)

    # Star points at lines 4, 10 and 16 - the nine hoshi of a 19x19 board.
    r_star = max(2, round(0.10 * step))
    for sy in (3, 9, 15):
        for sx in (3, 9, 15):
            cx, cy = pos(sx), pos(sy)
            d.ellipse([cx - r_star, cy - r_star, cx + r_star, cy + r_star], fill=PALETTE["line"])

    # Stones, just under half a step across so neighbours nearly touch.
    r = 0.46 * step
    for y in range(SIZE):
        for x in range(SIZE):
            if board[y][x] == EMPTY:
                continue
            cx, cy = pos(x), pos(y)
            black = board[y][x] == BLACK
            fill = PALETTE["black"] if black else PALETTE["white"]
            # White stones need an outline to separate them from the field; black ones
            # read on their own.
            outline = PALETTE["line"] if not black else None
            d.ellipse([cx - r, cy - r, cx + r, cy + r], fill=fill, outline=outline,
                      width=max(1, round(0.9 * SCALE)))

    return img.resize((OUT_PX, OUT_PX), Image.LANCZOS)


def main():
    board = playout(SEED, TARGET_STONES)
    assert_alive(board)
    stones = sum(c != EMPTY for row in board for c in row)
    black = sum(c == BLACK for row in board for c in row)
    render(board).save(OUT)
    print(f"{OUT}: {stones} stones ({black} black, {stones - black} white), seed {SEED}")


if __name__ == "__main__":
    main()
