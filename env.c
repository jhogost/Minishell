/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:50:19 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/24 11:50:19 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_shlvl(t_shell *shell)
{
	size_t	i;
	int		lvl;
	char	*num_ptr;
	char	*new_var;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], "SHLVL=", 6) == 0)
		{
			lvl = ft_atoi(shell->envp[i] + 6) + 1;
			num_ptr = ft_itoa(lvl);
			if (!num_ptr)
				return ;
			new_var = strjoin_free(ft_strdup("SHLVL="), num_ptr);
			if (!new_var)
				return ;
			free(shell->envp[i]);
			shell->envp[i] = new_var;
			return ;
		}
		i++;
	}
}

int	get_env(char **envp, t_shell *shell)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	shell->envp = malloc(sizeof(char *) * (i + 1));
	if (!shell->envp)
		return (-42);
	i = -1;
	while (envp[++i])
	{
		shell->envp[i] = ft_strdup(envp[i]);
		if (!shell->envp[i])
		{
			while (--i >= 0)
				free(shell->envp[i]);
			free(shell->envp);
			return (-42);
		}
	}
	shell->envp[i] = NULL;
	update_shlvl(shell);
	return (0);
}
//TODO atoi to itoa to change SHLVL to SHLVL+1