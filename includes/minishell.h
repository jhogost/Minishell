/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:51:27 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/19 16:07:46 by hhervieu         ###   ########.fr       */
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

enum e_what
{
	CONTROL,
	PIPE,
	REDIRECTION,
	ARGUMENT,
	COMMAND
};
// Enumeration, starts at 0, so CONTROL = 0, and increments by 1 at each line

typedef struct s_shell
{
	int				whatisit;
	char			*word;
	char			*whole_line;
	struct s_shell	*next;
	struct s_shell	*prev;
}	t_shell;
// Lexer that will be used to split the line into commands and flags etc...

// Free functions
void	free_things(void);
void	free_line(char *line, t_shell **lexer);
void	free_splitted(char **splitted);

// Utils functions
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_strlen(char *str);
char	**ft_split(char *str, char *charset);
int		ft_strchri(const char *s, int c);
char	*ft_strdup(char *s);
int		ft_countchar(char *str, char c);

// Built in commands
int		builtin_pwd(void);
void	builtin_cmd_or_else(char *line);

// Lxer functions
int		lexical(char *line, t_shell **lexer);

#endif