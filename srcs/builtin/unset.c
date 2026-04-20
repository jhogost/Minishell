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

void	remove_env_var(char **array, int index)
{
	if (index == -1 || !array)
		return ;
	free(array[index]);
	while (array[index + 1])
	{
		array[index] = array[index + 1];
		index++;
	}
	array[index] = NULL;
}

int	builtin_unset(char **argv, t_shell *shell)
{
	int	i;
	int	index;

	i = 1;
	if (!argv[i])
		return (0);
	while (argv[i])
	{
		index = get_env_index(shell->export, argv[i]);
		if (index >= 0)
			remove_env_var(shell->export, index);
		index = get_env_index(shell->envp, argv[i]);
		if (index >= 0)
			remove_env_var(shell->envp, index);
		i++;
	}
	return (0);
}
