/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:51:27 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/26 13:43:00 by jbayet           ###   ########.fr       */
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
	WORD,
	PIPE,
	OR,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	AND
}	t_token_type;
// Enumeration, starts at 0, so WORD = 0, and increments by 1 at each line

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef struct s_token
{
	int				type;
	char			*word;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;
// token is the element identified and extracted from the input string
// (commands and flags etc...)

typedef struct s_cmd
{
	char			**argv;
	int				pipe_in;
	int				pipe_out;
	t_redir_type	type;
	char			*content_redir;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;
// cmd is the logic command extracted from the list of token

typedef struct s_shell
{
	int		exit_code;
	char	*input;
	char	**envp;
	char	**paths; //char *path devient char **paths
	t_token	*lexer;
	t_cmd	*cmds;
}	t_shell;

/* --Free functions-- */
void	free_things(void);
void	free_interactive(t_shell *shell);
void	free_env(t_shell *shell);
void	free_paths(t_shell *shell);
void	free_everything(t_shell *shell);

/* --Utils functions-- */
char	**ft_split(char *str, char *charset);
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

/* --parsing-- */
int		quote_closed(char *s);
int		verify_line(char *line);
int		count_tokens(char *word);

/* --Built in commands-- */
int		builtin_pwd(void);
void	builtin_cmd_or_else(char *line);

/* --Lexer-- */
t_token	*new_token(int type, char *word);
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

/* --signal-- */
void	handle_sigint(int sig);
void	setup_signals(void);

/* --env-- */
int		get_env(char **envp, t_shell *shell);

/* --path-- */
char	*join_path(char *dir, char *cmd);
char	*find_path(char **paths, char *cmd);

/* --struct-- */
int		init_struct(t_shell *shell, char **envp);

#endif
