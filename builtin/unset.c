/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:44:23 by hhervieu          #+#    #+#             */
/*   Updated: 2026/04/01 15:44:23 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_index(char **envp, char *var)
{
	int	i;
	int	key_len;

	key_len = 0;
	while (var[key_len] && var[key_len] != '=')
		key_len++;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, key_len) == 0
			&& envp[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	remove_env_var(t_shell *shell, char *var)
{
	int	index;

	index = get_env_index(shell->envp, var);
	if (index != -1)
	{
		free(shell->envp[index]);
		while (shell->envp[index + 1])
		{
			shell->envp[index] = shell->envp[index + 1];
			index++;
		}
		shell->envp[index] = NULL;
	}
}

int	builtin_unset(char **argv, t_shell *shell)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		remove_env_var(shell, argv[i]);
		i++;
	}
	return (0);
}
