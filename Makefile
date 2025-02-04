COMPILE = cc #-Wall -Wextra -Werror -g
NAME = tetris_upf
SRC = game.c main.c pieces.c session.c utils.c
OBJ = $(SRC:.c=.o)
all: $(NAME)

$(NAME): Makefile $(OBJ) $(wildcard *.h)
	@$(COMPILE) $(SRC) -o $(NAME) 
clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean flclean
