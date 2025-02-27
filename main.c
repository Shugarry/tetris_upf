#include "main.h"

// refactored run_game a bit, for lab 3 to print the best possible move for the current state
void run_game(Session *session){
	GameState *game_state = &session->current_game_state;

	bool finish_game; 

	do{
		// 1. Print data
		printf("Best score: %d\n", session->best_score);
		print_game_state(game_state);

		// 2. Select a move
		int game_option;
		do{
			print_options(game_state->board);
			printf("Enter a game option: ");
			game_option = read_int();
		}while(!is_valid_option(game_option));

		// 3.a Quit game
		if(game_option == QUIT_GAME)
			return;
		// 3.b Show best move
		if(game_option == SHOW_BEST_MOVE)
		{
			printf("Calculating best move...\n");
			int best_move = show_best_move(game_state);
			printf("Best move: ");
			if (best_move == MOVE_LEFT)
				printf("Move left\n");
			if (best_move == MOVE_RIGHT)
				printf("Move right\n");
			if (best_move == ROTATE_CW)
				printf("Rotate clockwise\n");
			if (best_move == ROTATE_CCW)
				printf("Rotate counter-clockwise\n");
			if (NONE)
				printf("None\n");
			continue;
		}

		// 3.c Run one turn with the given option
		run_turn(game_state, game_option, false);

		// 4. Update scores
		session->best_score = max(session->best_score, game_state->score);

		// 5. Add new number
		finish_game = is_terminal(game_state);
	}while(!finish_game);

	printf("*** GAME OVER ***\n");
	print_game_state(game_state);
}

void new_game(Session *session){
    restart_session_game_state(session);
    run_game(session);
}

void save_game(Session *session)
{
	// CREATES FILE
	char filename[MAX_STR_LENGTH];
	printf("Enter filename to save: ");
	read_filename(filename);
	FILE *file = fopen(filename, "w");
	if (!file) return;

	GameState *gs = &session->current_game_state;
	fprintf(file, "Score: %d\n\n", gs->score);

	// SAVES PIECE INFORMATOIN
	PieceInfo *p = &gs->current_piece;
	fprintf(file, "%d %d\n", p->at_row, p->at_col);
	fprintf(file, "%c\n", p->p.name);
	fprintf(file, "%d %d\n", p->p.rows, p->p.cols);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fprintf(file, "%c", p->p.board[i][j]);
		}
		fprintf(file, "\n");
	}

	// SAVES CURRENT BOARD
	fprintf(file, "%d %d\n", gs->rows, gs->columns);
	for (int i = 0; i < gs->rows; i++)
	{
		for (int j = 0; j < gs->columns; j++)
		{
			fprintf(file, "%c", gs->board[i][j]);
		}
		fprintf(file, "\n");
	}
	fclose(file);
}
// creates a file and adds the information into it by printing it

void load_game(Session *session)
{
	char filename[MAX_STR_LENGTH];
	printf("Enter filename to load: ");
	read_filename(filename);
	FILE *file = fopen(filename, "r");
	if (!file) return;

	// FREES CURRENT BOARD
	GameState *gs = &session->current_game_state;
	free_game_state(gs);

	fscanf(file, "Score: %d\n\n", &gs->score);

	// READS CURR PIECE INFORMATION
	PieceInfo *p = &gs->current_piece;
	fscanf(file, "%d %d\n", &p->at_row, &p->at_col);
	fscanf(file, " %c\n", &p->p.name);
	fscanf(file, "%d %d\n", &p->p.rows, &p->p.cols);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fscanf(file, " %c", &p->p.board[i][j]);
		}
	}

	// ALLOCATES MEMORY FOR BOARD
	fscanf(file, "%d %d\n", &gs->rows, &gs->columns);
	make_board(gs);

	// ADDS BOARD DATA
	for (int i = 0; i < gs->rows; i++)
	{
		for (int j = 0; j < gs->columns; j++)
		{
			fscanf(file, " %c", &gs->board[i][j]);
		}
	}
	fclose(file);
}
// reads the file information and changes info accordingly

void resume_game(Session *session)
{
	if (is_terminal(&session->current_game_state))
	{
		printf("Game is already over!\n");
		return;
	}
	run_game(session);
}
// check if game is over just in case, and just runs the game

void print_menu(){
    printf("Menu options:\n");
    printf("\t1. New game.\n");  // LAB1 - basic lab for creating board, pieces and movements
                                 // LAB1 - extend game with GameState data structure, current score, best score
                                 //      - also add standard (4x4) with a posible extension, read board from command line  
    printf("\t2. Save game.\n"); // LAB2 - Writing file
    printf("\t3. Load game.\n"); // LAB2 - Reading file
    printf("\t4. Resume game.\n"); // LAB2 - Continue game after reading file
    printf("\t5. Exit.\n");  // Free all reserved memory!
}


void run(Session *session){
    int option;
    do{
        print_menu();
        do{
            printf("Enter an integer (%d-%d): ", NEW_GAME, EXIT);
            option = read_int();
        }while(option < NEW_GAME || option > EXIT);

        switch (option){
        case NEW_GAME:
            new_game(session);
            break;
        case SAVE_GAME:
            save_game(session);
            break;
        case LOAD_GAME:
            load_game(session);
            break;
        case RESUME_GAME:
            resume_game(session);
            break;
        case EXIT:
            break;
        }
    }while(option != EXIT);
	free_game_state(&session->current_game_state);
}
// Had to change a bit so it works for Lab 2, most importantly, I free at the end to avoid leaks

int main()
{
    Session session;
    init_session(&session);
    run(&session);
}
