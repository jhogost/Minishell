/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:51:27 by hhervieu          #+#    #+#             */
/*   Updated: 2026/04/21 14:32:40 by jbayet           ###   ########.fr       */
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
# include <errno.h>

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

typedef struct s_word
{
	char	*str;
	int		expand;
}	t_word;

typedef struct s_token
{
	int				type;
	t_word			*word;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	char			*heredoc_content;
	int				expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	int				pipe[2];
	t_redir			*redir;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	int		exit_code;
	char	*input;
	char	**envp;
	char	**export;
	char	**paths;
	int		count_line;
	t_token	*lexer;
	t_cmd	*cmds;
}	t_shell;

extern volatile sig_atomic_t	g_last_signal;

/* --Free-- */
void	free_everything(t_shell *shell);
void	free_env(t_shell *shell);
void	free_paths(t_shell *shell);
void	free_interactive(t_shell *shell);
void	free_cmds(t_shell *shell);

/* --Free 2-- */
void	free_redir(t_redir *redir);
void	wait_all(t_cmd *cmds, t_shell *shell);

/* --Utils functions-- */
char	**ft_split(char *str, char *charset);
int		ft_strchri(const char *s, int c);
int		ft_countchar(char *str, char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strdup_no_quotes(char *s);
char	*ft_strdup(char *s);
int		ft_strlen(char *str);
char	*ft_substr(char *s, int start, size_t len);
int		is_operator(char c);
int		is_space(char c);
char	*strjoin_free(char *s1, char *s2);
int		create_cmds(t_shell *shell);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_itoa(int n);
int		ft_atoi(const char *nptr);
int		ft_isalnum(int c);
int		i_white_char_str(char *line);
char	*ft_strjoin(char *s1, char *s2);
int		ft_isdigit(int c);
int		blank_line(char *line);
int		ft_isalpha(int c);

/* --execution-- */
void	execute_pipeline(t_shell *shell);

/* --execution_utils-- */
int		is_directory(t_cmd *cmd, char *path);
void	set_signals_parent(t_cmd *curr);
void	exit_child_signal(t_shell *shell);
void	exit_child(t_shell *shell, t_cmd *cmd, int code);

/* --parsing-- */
int		quote_closed(char *s);
int		verify_line(char *line, t_shell *shell);
int		count_tokens(char *word);
int		count_heredoc(char *line);
int		wrong_last_token(char	*line);

/* --Built in commands-- */
int		isbuiltin(char *word);
int		built_in(t_cmd *cmd, t_shell *shell);
int		builtin_exit(char **argv, t_shell *shell);
int		builtin_unset(char **argv, t_shell *shell);
int		builtin_env(char **envp, char **argv);
int		builtin_cd(char **argv, t_shell *shell);
int		builtin_echo(char **argv);
int		verify_export(char *str);
int		builtin_export(char **argv, t_shell *shell);
int		builtin_pwd(void);
void	add_export_var(t_shell *shell, char *var);
void	env_but_with_quotes(char **var);

/* --Lexer-- */
t_token	*new_token(int type, t_word *word);
void	add_token(t_token **lexer, t_token *new);
t_token	*extract_operator(char *s, int *i);
t_word	*extract_word(char *s, int *i);
t_token	*build_lexer(char *input, t_token *lexer);

/* --expand_token-- */
char	*extract_key(char *str, int i, int *end);
char	*get_env_value(char **envp, char *key);
char	*build_expanded(char *str, int i, int end, char *value);
char	*expand_token(t_shell *shell, char *str, int i);
char	*get_value(t_shell *shell, char *key);

/* --expand_lexer-- */
void	split_token(t_token *tok, t_token **new_lexer);
void	process_token(t_shell *shell, t_token *tmp, t_token **new_lexer);
int		need_expand(char *str, int expand);
t_token	*expand_lexer(t_shell *shell, t_token *lexer);

/* --handle_operator-- */
t_token	*handle_pipe(char *s, int *i);
t_token	*handle_redir_in(char *s, int *i);
t_token	*handle_redir_out(char *s, int *i);
int		handle_heredoc(char *delimiter);

/* --handle_text_and_quote-- */
char	*handle_quote(char *s, int *i, char *res);
char	*handle_plain_text(char *s, int *i, char *res);

/* --signal-- */
void	handler_sigint(int sig);
void	handler_ignor(int sig);
void	handler_heredoc_sigint(int sig);

/* --set_signal-- */
void	exec_signals(void);
void	general_signals(void);
void	ignore_signals(void);
void	ignore_signals_heredoc(void);
void	heredoc_signals(void);

/* --env-- */
int		get_env(char **envp, t_shell *shell);
int		get_env_index(char **envp, char *var);
void	replace_env_var(t_shell *shell, char *var, int index, int whichone);
void	add_env_var(t_shell *shell, char *var);
int		get_export(char **envp, t_shell *shell);

/* --path-- */
char	*join_path(char *dir, char *cmd);
char	*find_path(char **paths, char *cmd);
char	**get_path(t_shell *shell);

/* --command-- */
int		count_args(t_token *tok);
t_cmd	*fill_cmd(t_token **lexer, t_cmd *cmd);
t_cmd	*new_cmd(t_token **lexer);
void	add_cmd_back(t_cmd **cmds, t_cmd *new);
int		create_cmds(t_shell *shell);

/* --create_redir-- */
void	add_redir_back(t_redir **redirs, t_redir *new);
t_redir	*new_redir(t_token **lexer);

/* --apply_redir-- */
int		apply_redir_out(t_redir *redir);
int		apply_redir_append(t_redir *redir);
int		apply_redir_in(t_redir *redir);
int		apply_redir_heredoc(t_redir *redir, t_shell *shell);
int		apply_redirections(t_cmd *cmd, t_shell *shell);

/* --heredoc-- */
char	*read_heredoc(t_redir *redir, t_shell *shell);

/* --init struct-- */
t_word	*init_word(void);
t_redir	*init_redir_struct(void);
t_cmd	*init_cmd_struct(void);
t_cmd	*init_cmd(t_token *tok);
int		init_struct(t_shell *shell, char **envp);

/* --main-- */
void	print_lexer(t_token *lexer);
void	print_cmd(t_cmd *cmd);
int		run_interactive(t_shell *shell);

/* --error-- */
void	child_error(t_shell *shell, char *cmd, char *path, int code);
void	execve_error(t_cmd *cmd, t_shell *shell, char *path);

#endif
