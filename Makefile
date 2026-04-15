# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/09 15:17:12 by jbayet            #+#    #+#              #
#    Updated: 2026/04/09 15:17:12 by jbayet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = minishell

SRCS += srcs/minishell.c
SRCS += srcs/free.c
SRCS += srcs/free2.c
SRCS += srcs/signal.c
SRCS += srcs/env.c
SRCS += srcs/init_struct.c
SRCS += srcs/path.c
SRCS += srcs/command.c
SRCS += srcs/execution.c
SRCS += srcs/error.c
SRCS += srcs/expand_token.c
SRCS += srcs/expand_lexer.c

SRCS += srcs/redir/apply_redir.c
SRCS += srcs/redir/create_redir.c
SRCS += srcs/redir/heredoc.c

SRCS += builtin/built_in.c
SRCS += builtin/pwd.c
SRCS += builtin/exit.c
SRCS += builtin/env.c
SRCS += builtin/cd.c
SRCS += builtin/echo.c
SRCS += builtin/export.c
SRCS += builtin/unset.c

SRCS += utils/ft_split.c
SRCS += utils/ft_strchri.c
SRCS += utils/ft_strcmp.c
SRCS += utils/ft_strdup_no_quotes.c
SRCS += utils/ft_strdup.c
SRCS += utils/ft_strlen.c
SRCS += utils/ft_substr.c
SRCS += utils/is_operator.c
SRCS += utils/is_space.c
SRCS += utils/strjoin_free.c
SRCS += utils/ft_putchar_fd.c
SRCS += utils/ft_putstr_fd.c
SRCS += utils/ft_strchr.c
SRCS += utils/ft_itoa.c
SRCS += utils/ft_atoi.c
SRCS += utils/ft_isalnum.c
SRCS += utils/i_white_char_str.c
SRCS += utils/ft_strjoin.c

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
