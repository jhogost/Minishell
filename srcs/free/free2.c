/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:37:21 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/22 15:43:59 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;
	t_redir	*next;

	tmp = redir;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->heredoc_content)
			free(tmp->heredoc_content);
		if (tmp->file)
			free(tmp->file);
		free(tmp);
		tmp = next;
	}
	redir = NULL;
}

void	wait_all(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*tmp;
	int		status;

	tmp = cmds;
	while (tmp)
	{
		waitpid(tmp->pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_code = 128 + WTERMSIG(status);
		tmp = tmp->next;
	}
	general_signals();
}
