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

# srcs
SRCS += srcs/minishell.c
SRCS += srcs/env.c
SRCS += srcs/init_struct.c

#	->srcs/builtin
SRCS += srcs/builtin/built_in.c
SRCS += srcs/builtin/pwd.c
SRCS += srcs/builtin/exit.c
SRCS += srcs/builtin/env.c
SRCS += srcs/builtin/cd.c
SRCS += srcs/builtin/echo.c
SRCS += srcs/builtin/export.c
SRCS += srcs/builtin/export_utils.c
SRCS += srcs/builtin/unset.c

# 	->srcs/exec
SRCS += srcs/exec/execution_utils.c
SRCS += srcs/exec/execution.c
SRCS += srcs/exec/path.c
SRCS += srcs/exec/error.c

# 	->srcs/free
SRCS += srcs/free/free.c
SRCS += srcs/free/free2.c

# 	->srcs/redir
SRCS += srcs/redir/apply_redir.c
SRCS += srcs/redir/create_redir.c
SRCS += srcs/redir/heredoc.c

# 	->srcs/sig
SRCS += srcs/sig/set_signals.c
SRCS += srcs/sig/signal.c

# 	->srcs/structuring
SRCS += srcs/structuring/command.c
SRCS += srcs/structuring/parsing.c
SRCS += srcs/structuring/parsing2.c

# 		->srcs/structuring/expand
SRCS += srcs/structuring/expand/expand_token.c
SRCS += srcs/structuring/expand/expand_lexer.c

# 		->srcs/structuring/lexer
SRCS += srcs/structuring/lexer/handle_operator.c
SRCS += srcs/structuring/lexer/handle_text_and_quote.c
SRCS += srcs/structuring/lexer/lexer.c

# utils
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
SRCS += utils/ft_isdigit.c
SRCS += utils/blank_line.c

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
