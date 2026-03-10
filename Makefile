# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/10 10:04:30 by hhervieu          #+#    #+#              #
#    Updated: 2026/02/18 14:12:10 by hhervieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = minishell

SRCS += minishell.c
SRCS += free.c
SRCS += built_in.c

OBJ = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
CLIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CLIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
