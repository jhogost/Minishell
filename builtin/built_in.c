/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 18:04:23 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/10 18:04:23 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isbuiltin(char *word)
{
	if (!word)
		return (-42);
	if (ft_strncmp(word, "exit", 5) == 0 && ft_strlen(word) == 4)
		return (0);
	if (ft_strncmp(word, "echo", 5) == 0 && ft_strlen(word) == 4)
		return (0);
	if (ft_strncmp(word, "cd", 3) == 0 && ft_strlen(word) == 2)
		return (0);
	if (ft_strncmp(word, "pwd", 4) == 0 && ft_strlen(word) == 3)
		return (0);
	if (ft_strncmp(word, "export", 7) == 0 && ft_strlen(word) == 6)
		return (0);
	if (ft_strncmp(word, "unset", 6) == 0 && ft_strlen(word) == 5)
		return (0);
	if (ft_strncmp(word, "env", 4) == 0 && ft_strlen(word) == 3)
		return (0);
	return (-42);
}

int	built_in(t_cmd *cmd, t_shell *shell)
{
	char	*word;

	word = cmd->argv[0];
	if (ft_strncmp(word, "exit", 5) == 0)
		exiting_minishell(shell);
	if (ft_strncmp(word, "echo", 5) == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strncmp(word, "cd", 3) == 0)
		return (builtin_cd(cmd->argv));
	if (ft_strncmp(word, "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(word, "env", 4) == 0)
		return (builtin_env(shell->envp));
	if (ft_strncmp(word, "export", 7) == 0)
		return (builtin_export(cmd->argv, shell));
	if (ft_strncmp(word, "unset", 6) == 0)
		return (builtin_unset(cmd->argv, shell));
	return (0);
}
//check if it's one of the built-in cmd of shell and execute it