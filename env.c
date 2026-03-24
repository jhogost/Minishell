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

int	get_env(char **envp, t_shell *shell)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	shell->envp = malloc(sizeof(char *) * (i + 1));
	if (!shell->envp)
		return (-42);
	i = 0;
	while (envp[i])
	{
		shell->envp[i] = strdup(envp[i]);
		if (!shell->envp[i])
		{
			while (i >= 0)
			{
				free(shell->envp[i]);
				i--;
			}
			return (-42);
		}
		i++;
	}
	shell->envp[i] = NULL;
	return (0);
}
