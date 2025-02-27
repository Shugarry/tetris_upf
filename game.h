#ifndef _GAME_H_
#define _GAME_H_

#include "common.h"
#include "utils.h"
#include "pieces.h"

#define MIN_ROWS 10
#define MIN_COLUMNS 6
#define MAX_DEPTH 10

// ToDo in LAB 1 - define macros MAX_ROWS and MAX_COLUMNS

typedef struct
{
	Piece	p;
	int		at_row;
	int		at_col;
} PieceInfo;

typedef struct
{
	int		score;
	char	**board;
	int		rows;
	int		columns;
	PieceInfo current_piece;
} GameState;

/// Implemented functions
void	print_game_state(GameState *gs);
void	print_options();
bool	is_valid_option(int option);
void	print_line(int columns);
void	print_board(GameState *game_state);
void	get_new_random_piece(GameState *game_state);
void	block_current_piece(GameState *game_state);
bool	is_collision(GameState *gs);

/**** LAB 1 - functions to program (start here) ****/
void	init_game_state(GameState *game_state);
bool	is_terminal(GameState *gs); // True if contains X values in TOP-4 rows
void	move(GameState *gs, int option, bool is_recursive);
void	rotate(GameState *gs, int option, bool is_recursive);
/**** LAB 1 - functions to program (end here) ****/

/// Implemented functions
bool	run_turn(GameState *game_state, int option, bool is_recursive);

// LAB 2 New functionalites
void	make_board(GameState *gs);
void	free_game_state(GameState *gs);
void	set_default_game_state(GameState *gs);
void	restart_game_state(GameState *gs);

// LAB 3 New functionalities
GameState	copy(GameState *game_state);
int			recursive_best_score(GameState *game_state, int depth);
int			show_best_move(GameState *game_state);
int			get_highest_blocked_row(GameState *gs);
#endif
