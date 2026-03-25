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
SRCS += signal.c
SRCS += env.c
SRCS += init_struct.c
SRCS += path.c
SRCS += command.c

SRCS += builtin/built_in.c
SRCS += builtin/pwd.c

SRCS += utils/ft_split.c
SRCS += utils/ft_strchri.c
SRCS += utils/ft_strcmp.c
SRCS += utils/ft_strdup.c
SRCS += utils/ft_strlen.c
SRCS += utils/ft_substr.c
SRCS += utils/is_operator.c
SRCS += utils/is_space.c
SRCS += utils/strjoin_free.c

SRCS += lexer/handle_operator.c
SRCS += lexer/handle_text_and_quote.c
SRCS += lexer/lexer.c
SRCS += lexer/parsing.c

OBJ = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes -g
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
