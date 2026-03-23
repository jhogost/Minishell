/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:51:27 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/23 14:30:04 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

typedef enum e_token_type
{
	WORD,		// command, text, file... On identifie plus tard
	PIPE,		// |
	OR,			// ||
	REDIR_IN,	// <
	REDIR_OUT,	// >
	APPEND,		// >>
	HEREDOC,	// <<
	AND			// &&
}	t_token_type;
// Enumeration, starts at 0, so WORD = 0, and increments by 1 at each line

typedef struct s_token
{
	int				type;
	char			*word;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;
// token is the element identified and extracted from the input string (commands and flags etc...)

typedef struct s_shell
{
	char	*input;
}	t_shell;

/* --Free functions-- */
void	free_things(void);
void	free_line(char *line, t_token **lexer);
void	free_splitted(char **splitted);

/* --Utils functions-- */
int		ft_strchri(const char *s, int c);
int		ft_countchar(char *str, char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strdup(char *s);
int		ft_strlen(char *str);
char	*ft_substr(char *s, int start, size_t len);
int		is_operator(char c);
int		is_space(char c);
char	*strjoin_free(char *s1, char *s2);

/* --Built in commands-- */
int		builtin_pwd(void);
void	builtin_cmd_or_else(char *line);

/* --Lexer-- */
t_token	*new_token(t_token_type type, char *word);
void	add_token(t_token **lexer, t_token *new);
t_token	*extract_operator(char *s, int *i);
char	*extract_word(char *s, int *i);
t_token	*build_lexer(char *input, t_token *lexer);

/* --handle_operator-- */
t_token	*handle_and(char *s, int *i);
t_token	*handle_pipe_or(char *s, int *i);
t_token	*handle_redir_in(char *s, int *i);
t_token	*handle_redir_out(char *s, int *i);

/* --handle_text_and_quote-- */
char	*handle_quote(char *s, int *i, char *res);
char	*handle_plain_text(char *s, int *i, char *res);

#endif
