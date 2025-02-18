COMPILE = cc -g #-Wall -Wextra -Werror
NAME = tetris_upf
SRC = game.c main.c pieces.c session.c utils.c
HDR = game.h main.h pieces.h session.h utils.h common.h
OBJ = $(SRC:.c=.o)
all: $(NAME)

$(NAME): Makefile $(OBJ) $(HDR)
	@$(COMPILE) $(SRC) -o $(NAME) 
clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean flclean
