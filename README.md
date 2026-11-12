# Tic-Tac-Toe vs. the Computer

A tic-tac-toe game in C where you play against the computer. You are **O** and go first. The computer is **X** and picks random moves.

## How to Run

```
gcc tic.c -o tic
./tic
```

## How to Play

The squares are numbered 0 to 8:

```
 0 | 1 | 2
---+---+---
 3 | 4 | 5
---+---+---
 6 | 7 | 8
```

- Type the number of an empty square and press Enter.
- Get three in a row (across, down, or diagonal) to win.
- If the board fills up with no winner, it's a draw.
- After each game, type `y` to play again or `q` to quit.

## Functions

| Function | What it does |
|---|---|
| `init_board` | Sets all 9 squares to empty |
| `display_board` | Prints the board, showing numbers for empty squares |
| `is_winner` | Returns true if a player has three in a row |
| `other_player` | Returns the other player's symbol |
| `get_human_move` | Asks until the player enters a valid square |
| `get_computer_move` | Picks a random empty square |
| `take_turn` | Gets a move from the current player and places it |
| `play_game` | Plays one full game |
| `play_again` | Asks whether to play another game |
