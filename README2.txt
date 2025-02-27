Abstract that explains the extension of the project for extra points in the labs.

This abstract roughly explains the extension of the project that i did for the functions show_best_move and recursive_best_score to calculate the next
best move in the current game state.

Basically, the what the recursive function does, is it simulates up to MAX_DEPTH (10) turns, where it does every possible combination of moves for that
game state. and with that, adds "points" to the return of recursive_best_score to find the best possible move.

"points" are added when a line is achieved, or when a lower blocked cell placement is achieved.

Examples:

If a line is able to be scored, that is automatically the best possible move, because it keeps the game going longer and it lowers all blocked cells by 1
technically.

But, if no lines are able to be scored (score technically doesn't increase), then the function decides to choose the best move based on how high the rows
are cell blocked.

For a more concrete example; imagine a move leaves cells blocked all the way to the 4th row, but then another move leaves only until the 3rd row, that
second move is better because it technically lets you play longer because you are further from losing the game.

All of this is also explained a bit in the comments of the actual program.
