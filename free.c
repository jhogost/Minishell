/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:28:53 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/19 12:28:53 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_everything(t_shell *shell)
{
	free_things();
	free_interactive(shell);
	free_env(shell);
	free_paths(shell);
}

void	free_env(t_shell *shell)
{
	int	i;

	if (shell->envp)
	{
		i = 0;
		while (shell->envp[i])
		{
			free(shell->envp[i]);
			i++;
		}
		free(shell->envp);
		shell->envp = NULL;
	}
}

void	free_paths(t_shell *shell)
{
	int	i;

	if (shell->paths)
	{
		i = 0;
		while (shell->paths[i])
		{
			free(shell->paths[i]);
			i++;
		}
		free(shell->paths);
		shell->paths = NULL;
	}
}

void	free_interactive(t_shell *shell)
{
	t_token	*tmp;
	t_token	*next;

	if (shell->input)
		free(shell->input);
	if (shell->lexer)
	{
		tmp = shell->lexer;
		while (tmp)
		{
			next = tmp->next;
			free(tmp->word);
			free(tmp);
			tmp = next;
		}
		shell->lexer = NULL;
	}
}

void	free_things(void)
{
	rl_clear_history();
}
// TODO update whenever the struct is ready to free everything
