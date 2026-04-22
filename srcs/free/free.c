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
	rl_clear_history();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
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
	if (shell->export)
	{
		i = 0;
		while (shell->export[i])
		{
			free(shell->export[i]);
			i++;
		}
		free(shell->export);
		shell->export = NULL;
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
			free(tmp->word->str);
			free(tmp->word);
			free(tmp);
			tmp = next;
		}
		shell->lexer = NULL;
	}
	free_cmds(shell);
}

void	free_cmds(t_shell *shell)
{
	t_cmd	*tmp;
	int		i;

	if (!shell->cmds)
		return ;
	while (shell->cmds)
	{
		tmp = shell->cmds->next;
		i = 0;
		if (shell->cmds->argv)
		{
			while (shell->cmds->argv[i])
				free(shell->cmds->argv[i++]);
			free(shell->cmds->argv);
		}
		if (shell->cmds->redir)
			free_redir(shell->cmds->redir);
		free(shell->cmds);
		shell->cmds = tmp;
	}
	shell->cmds = NULL;
}
