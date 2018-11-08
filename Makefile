##
## EPITECH PROJECT, 2018
## PSU_lemipc_2017
## File description:
## Makefile
##

SRC		=	src/main.c	\
			src/game.c	\
			src/move.c	\
			src/map.c	\
			src/strategy.c	\
			src/end.c	\
			src/death.c	\
			src/tools_semaphore.c

OBJ		=	$(SRC:.c=.o)

NAME		=	lemipc

FLAGS		=	-W -Wextra

all:	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(FLAGS) -g

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

author: echo $(USER) > author
