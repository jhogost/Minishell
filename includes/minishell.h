/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:51:27 by hhervieu          #+#    #+#             */
/*   Updated: 2026/04/02 18:21:03 by jbayet           ###   ########.fr       */
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
	BUILTIN,
	PIPE,
	OR,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	AND
}	t_token_type;
// Enumeration, starts at 0, so WORD = 0, and increments by 1 at each line

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
	int				pipe[2];
	t_token_type	type;
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
	char	**paths;
	t_token	*lexer;
	t_cmd	*cmds;
}	t_shell;

/* --Free functions-- */
void	free_everything(t_shell *shell);
void	free_env(t_shell *shell);
void	free_paths(t_shell *shell);
void	free_interactive(t_shell *shell);
void	free_cmds(t_shell *shell);

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
int		create_cmds(t_shell *shell);
void	execute_pipeline(t_shell *shell);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_itoa(int n);
int		ft_atoi(const char *nptr);

/* --parsing-- */
int		quote_closed(char *s);
int		verify_line(char *line);
int		count_tokens(char *word);

/* --Built in commands-- */
int		isbuiltin(char *word);
int		built_in(t_cmd *cmd, t_shell *shell);
void	exiting_minishell(t_shell *shell);
int		builtin_unset(char **argv, t_shell *shell);
int		builtin_env(char **envp);
int		builtin_cd(char **argv);
int		builtin_echo(char **argv);
int		builtin_export(char **argv, t_shell *shell);
int		builtin_pwd(void);

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
int		handle_heredoc(char *delimiter);

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

/* --command-- */
int		count_args(t_token *tok);
t_cmd	*fill_cmd(t_token **lexer, t_cmd *cmd);
t_cmd	*new_cmd(t_token **lexer);
void	add_cmd_back(t_cmd **cmds, t_cmd *new);
int		create_cmds(t_shell *shell);

/* --init struct-- */
int		init_struct(t_shell *shell, char **envp);
t_cmd	*init_cmd(t_token *tok);
t_cmd	*init_cmd_struct(void);

/* --main-- */
void	print_lexer(t_token *lexer);
void	print_cmd(t_cmd *cmd);
int		run_interactive(t_shell *shell);

/* --error-- */
void	child_error(t_shell *shell, char *cmd, char *path);

#endif
