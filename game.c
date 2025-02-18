#include "main.h"

// LAB 2 New functionalities

void	make_board(GameState *gs)
{
	if (gs->board != NULL)
	{
		for (int i = 0; i < gs->rows; i++)
			free(gs->board[i]);
		free(gs->board);
	}

	gs->board = (char **)malloc(gs->rows * sizeof(char *));
	if (gs->board == NULL)
		exit(EXIT_FAILURE);
	for (int i = 0; i < gs->rows; i++)
	{
		gs->board[i] = (char *)malloc(gs->columns * sizeof(char));
		if (gs->board[i] == NULL)
		{
			for (int j = 0; j < i; ++j)
				free(gs->board[j]);
			free(gs->board);
			exit(EXIT_FAILURE);
		}
	}
}

void	free_game_state(GameState *gs)
{
	if (gs->board != NULL)
	{
		for (int i = 0; i < gs->rows; i++)
			free(gs->board[i]);
		free(gs->board);
		gs->board = NULL;
	}
}

void set_default_game_state(GameState *gs)
{
	gs->score = 0;
	for (int i = 0; i < gs->rows; i++)
		for (int j = 0; j < gs->columns; j++)
			gs->board[i][j] = '.';
	get_new_random_piece(gs);
}

void restart_game_state(GameState *gs)
{
	int	rows;
	int	cols;
	printf("Enter rows (MIN = %d): ", MIN_ROWS);
	scanf(" %d", &rows);
	printf("Enter cols (MIN = %d): ", MIN_COLUMNS);
	scanf(" %d", &cols);

	if (rows < MIN_ROWS)
		rows = MIN_ROWS;
	if (cols < MIN_ROWS)
		rows = MIN_ROWS;

	gs->rows = rows;
	gs->columns = cols;
	make_board(gs);
	set_default_game_state(gs);
}

/**** LAB 1 - given functions ****/
void print_game_state(GameState *gs){
    printf("*** Game State ***\n");
    printf("Score=%d\n", gs->score);
    print_board(gs);
}

void print_options(){
    printf("Options:\n");
    printf("\t%d. Move left\n", MOVE_LEFT);
    printf("\t%d. Move right\n", MOVE_RIGHT);
    printf("\t%d. Rotate clockwise\n", ROTATE_CW);
    printf("\t%d. Rotate counter clockwise\n", ROTATE_CCW);
    printf("\t%d. None\n", NONE);
    printf("\t%d. Show best move\n", SHOW_BEST_MOVE);
    printf("\t%d. Quit game\n", QUIT_GAME);
}

bool is_valid_option(int option){
    return ((MOVE_LEFT <= option) && (option<=QUIT_GAME));
}


void print_line(int columns)
{
    for(int c = -1; c < columns + 1; ++c) 
    	printf("-");    
    printf("\n");
}

void print_board(GameState *game_state){
    Piece *piece = &game_state->current_piece.p;
    int p_row_size = piece->rows;
    int p_col_size = piece->cols;
    int current_row = game_state->current_piece.at_row;
    int current_col = game_state->current_piece.at_col;
    print_line(current_row);
    for(int r = 0; r < game_state->rows; ++r){
        if(r == 4) print_line(current_row);
        printf("|");
        for(int c=0; c < game_state->columns; ++c){
            if((game_state->board[r][c] == '.') &&
               (current_row <= r) && (r < current_row + p_row_size) && 
               (current_col <= c) && (c < current_col + p_col_size)){
                printf("%c", piece->board[r-current_row][c-current_col]);
            }
            else printf("%c", game_state->board[r][c]);
        }
        printf("|\n");
    }
	print_line(current_row);
    printf("\n");
}

void get_new_random_piece(GameState *game_state){
    // Random piece
    switch (rand()%MAX_NUM_PIECES){
    case 0:
        game_state->current_piece.p = make_I();
        break;    
    case 1:
        game_state->current_piece.p = make_J();
        break;
    case 2:
        game_state->current_piece.p = make_L();
        break;
    case 3:
        game_state->current_piece.p = make_O();
        break;
    case 4:
        game_state->current_piece.p = make_S();
        break;
    case 5:
        game_state->current_piece.p = make_T();
        break;
    case 6:
        game_state->current_piece.p = make_Z();
        break;
    default:
        break;
    }

    // Random orientation
    int rotations = rand()%3;
    for(int r = 0; r < rotations; ++r)
        rotate_clockwise(&(game_state->current_piece.p));

    // Random location
    game_state->current_piece.at_row = 4 - game_state->current_piece.p.rows;
    game_state->current_piece.at_col = rand() % (game_state->columns + 1 - game_state->current_piece.p.cols);
}

void block_current_piece(GameState *game_state){
    Piece *piece = &game_state->current_piece.p;
    int row = game_state->current_piece.at_row;
    int col = game_state->current_piece.at_col;
    for(int i=0; i<piece->rows; ++i)
        for(int j=0; j<piece->cols; ++j)
            if(piece->board[i][j] == '#')
                game_state->board[row+i][col+j] = 'X';
}

bool is_collision(GameState *gs)
{
	Piece *piece = &gs->current_piece.p;
	int row = gs->current_piece.at_row;
	int col = gs->current_piece.at_col;

	if (row < 0 || col < 0 || (row + piece->rows > gs->rows) || (col + piece->cols > gs->columns))
		return true;

	for (int i = 0; i < piece->rows; i++)
	{
		for (int j = 0; j < piece->cols; j++)
		{
			if (piece->board[i][j] == '#' && gs->board[row + i][col + j] == 'X')
				return true;
		}
	}
	return false;
}

int remove_completed_lines(GameState *gs)
{
	int		lines = 0;
	bool	completed_line;

	for (int r = 4; r < gs->rows; ++r)
	{
		completed_line = true;
		for (int c = 0; c < gs->columns; ++c)
		{
			if (gs->board[r][c] != 'X')
			{
				completed_line = false; 
				break;
			}
		}

		if (completed_line)
		{
			++lines;
			// Move all rows above, once down
			for (int r2 = r; r2 > 3; --r2)
			{
				for (int c = 0; c < gs->columns; ++c)
				{
					gs->board[r2][c] = gs->board[r2-1][c];
				}
			}
		}
	}
	return lines;
}

/********************************************************/
/******* LAB 1 - functions to program (start here) ******/
/********************************************************/

void init_game_state(GameState *game_state)
{
	game_state->score = 0;
	game_state->columns = MIN_COLUMNS;
	game_state->rows = MIN_ROWS;
	game_state->board = NULL;

	make_board(game_state);
	set_default_game_state(game_state);
}
// just a function that initializes game_state.score, and a double loop which
// sets the entire boards to '.', also call for a new piece at the start of the
// game


bool is_terminal(GameState *gs)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < gs->columns; j++)
		{
			if (gs->board[i][j] == 'X')
				return true;
		}
	}
    return false;
}
// checks whether there is a blocked cell in the top 4 rows of the board.


void move(GameState *gs, int option)
{
	PieceInfo original = gs->current_piece;
	int dir;

	if (option == MOVE_LEFT)
		dir = -1;
	else if (option == MOVE_RIGHT)
		dir = 1;
	else
		return ;

	gs->current_piece.at_col += dir;

	if (is_collision(gs))
	{
		gs->current_piece = original;
		printf("Can't move that direction\n");
	}
}
// move_piece first checks if movement is valid (is equals to move left or 
// right), then creates a tmp new_col variable to see if placing the piece at
// that new spot is valid or not. if no collision is detected, update board and
// piece position

void rotate(GameState *gs, int option)
{
    PieceInfo original = gs->current_piece;

	if (option == ROTATE_CW)
		rotate_clockwise(&gs->current_piece.p);
	else if (option == ROTATE_CCW)
		rotate_counter_clockwise(&gs->current_piece.p);
	else
		return ;

	if (is_collision(gs))
	{
		gs->current_piece = original;
		printf("Rotation causes collision. Piece not rotated.\n");
	}
}
// rotate_piece has a very similar logic to move_piece, checks validity of move
// whether it collides or not, and then updates position if everything is
// correct

/********************************************************/
/******* LAB 1 - functions to program (end here) ********/
/********************************************************/

void run_turn(GameState *game_state, int option){
	PieceInfo *p_inf = &(game_state->current_piece);
	if(option == MOVE_LEFT || option == MOVE_RIGHT) 
		move(game_state, option);
	else if(option == ROTATE_CW || option == ROTATE_CCW)
		rotate(game_state, option);
    else if(option == NONE){} // do nothing
    else{ printf("[ERROR] Invalid option %d.\n", option); exit(-3); }

	// Move down if possible, otherwise block the piece and remove
    // the completed lines, aggregating them to the current score.
    // If it is not in a terminal state, add a new random piece to the board.
	p_inf->at_row++;
	if(is_collision(game_state)){
		p_inf->at_row--;
		block_current_piece(game_state);
        game_state->score += remove_completed_lines(game_state);
        if(!is_terminal(game_state))
            get_new_random_piece(game_state);
	}
}

