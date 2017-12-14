##
## Makefile for malloc in /home/daine/EPI/rendu/C/PSU_2016_malloc
## 
## Made by david.maidenberg@epitech.eu
## Login   <david.maidenberg@epitech.eu>
## 
## Started on  Sun Feb 12 15:01:29 2017 david.maidenberg@epitech.eu
## Last update Sun Feb 12 15:01:30 2017 david.maidenberg@epitech.eu
##


CC=		gcc

NAME=		libmy_malloc.so

SRC=		src/malloc.c \
		src/realloc.c \
		src/calloc.c \
		src/tree_handler.c \
		src/annexe.c \
		src/free.c

OBJ=		$(SRC:.c=.o)

RM=		rm -f

CFLAGS=		-Wall -Wextra -Werror -Iinclude -fPIC

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -shared -o $(NAME) $(OBJ) -lm

clean:
		$(RM) $(OBJ)


fclean:		clean
		$(RM) $(NAME)


re:		fclean all

.PHONY:		all clean fclean re
