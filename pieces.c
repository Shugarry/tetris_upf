#include "main.h"

void init_piece(Piece *p)
{
	p->rows = 0;
	p->cols = 0;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			p->board[i][j] = '.';
		}
	}
}
// set row/col to 0 and every index in the double array to '.'

void print_piece(Piece p)
{
    printf("Name: %c; Size: %dx%d\n", p.name, p.rows, p.cols);
    for(int i=0; i<PIECE_SIZE; ++i)
	{
        for(int j=0; j<PIECE_SIZE; ++j)
		{
            printf("%c", p.board[i][j]);
        }
        printf("\n");
    }
}

void rotate_clockwise(Piece *p)
{
    char temp[4][4] = {{0}};

    for (int i = 0; i < p->rows; i++)
	{
        for (int j = 0; j < p->cols; j++)
		{
            int new_row = j;
            int new_col = p->rows - 1 - i;
            temp[new_row][new_col] = p->board[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
	{
        for (int j = 0; j < 4; j++)
		{
            p->board[i][j] = temp[i][j];
        }
    }

    int original_rows = p->rows;
    p->rows = p->cols;
    p->cols = original_rows;
}
// the functionality of rotate clockwise is the following, create a tmp double
// array to do the rotation. and perform the rotation by essentially swapping
// rows and cols via new_col = p->rows - 1 - i; and new_row = j; so the shape
// is rotate 90 degrees clockwise. then, the function just copies the tmp
// array into the actual piece board and replaces rows and cols.

void rotate_counter_clockwise(Piece *p)
{
    char temp[4][4] = {{0}};

    for (int i = 0; i < p->rows; i++)
	{
        for (int j = 0; j < p->cols; j++)
		{
            int new_row = p->cols - 1 - j;
            int new_col = i;
            temp[new_row][new_col] = p->board[i][j];
		}
	}

    for (int i = 0; i < 4; i++)
	{
        for (int j = 0; j < 4; j++)
		{
            p->board[i][j] = temp[i][j];
        }
    }

    int original_rows = p->rows;
    p->rows = p->cols;
    p->cols = original_rows;
}
// rotate counter clockwise has the same logic as rotate clockwise but swapping
// the logic for rows and cols.

Piece make_O()
{
	Piece tmp;
	tmp.name = 'O';
	init_piece(&tmp);
	tmp.rows = 2;
	tmp.cols = 2;

	tmp.board[0][0] = '#';
	tmp.board[0][1] = '#';
	tmp.board[1][0] = '#';
	tmp.board[1][1] = '#';
	return (tmp);
}
// for every piece making function, declare a tmp variable, give it a name,
// initialize the board to 0, initialize rows, cols, and draw the shape.

Piece make_I()
{
	Piece tmp;
	tmp.name = 'I';
	init_piece(&tmp);
	tmp.rows = 1;
	tmp.cols = 4;

	tmp.board[0][0] = '#';
	tmp.board[0][1] = '#';
	tmp.board[0][2] = '#';
	tmp.board[0][3] = '#';
	return (tmp);
}


Piece make_S()
{
	Piece tmp;
	tmp.name = 'S';
	init_piece(&tmp);
	tmp.rows = 2;
	tmp.cols = 3;

	tmp.board[0][1] = '#';
	tmp.board[0][2] = '#';
	tmp.board[1][0] = '#';
	tmp.board[1][1] = '#';
	return (tmp);
}


Piece make_Z()
{
	Piece tmp;
	tmp.name = 'Z';
	init_piece(&tmp);
	tmp.rows = 2;
	tmp.cols = 3;

	tmp.board[0][0] = '#';
	tmp.board[0][1] = '#';
	tmp.board[1][1] = '#';
	tmp.board[1][2] = '#';
	return (tmp);
}

Piece make_L()
{
	Piece tmp;
	tmp.name = 'L';
	init_piece(&tmp);
	tmp.rows = 2;
	tmp.cols = 3;

	tmp.board[0][2] = '#';
	tmp.board[1][0] = '#';
	tmp.board[1][1] = '#';
	tmp.board[1][2] = '#';
	return (tmp);
}

Piece make_J()
{
	Piece tmp;
	tmp.name = 'J';
	init_piece(&tmp);
	tmp.rows = 2;
	tmp.cols = 3;

	tmp.board[0][0] = '#';
	tmp.board[1][0] = '#';
	tmp.board[1][1] = '#';
	tmp.board[1][2] = '#';
	return (tmp);
}

Piece make_T()
{
	Piece tmp;
	tmp.name = 'T';
	init_piece(&tmp);
	tmp.rows = 2;
	tmp.cols = 3;

	tmp.board[0][1] = '#';
	tmp.board[1][0] = '#';
	tmp.board[1][1] = '#';
	tmp.board[1][2] = '#';
	return (tmp);
}
