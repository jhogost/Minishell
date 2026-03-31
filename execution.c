/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:32:55 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/28 13:32:55 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_error(t_shell *shell, char *cmd, char *path)
{
	if (!path)
		printf("minishell: command not found: %s\n", cmd);
	else
		perror("minishell");
	free(path);
	free_cmds(shell);
	free_everything(shell);
	exit(127);
}

static void	wait_all(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*tmp;
	int		status;

	tmp = cmds;
	while (tmp)
	{
		waitpid(tmp->pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status);
		tmp = tmp->next;
	}
}

static void	execute_child(t_shell *shell, t_cmd *cmd, int p[2], int prev)
{
	char	*path;

	if (prev != STDIN_FILENO)
	{
		dup2(prev, STDIN_FILENO);
		close(prev);
	}
	if (cmd->next)
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
	}
	path = find_path(shell->paths, cmd->argv[0]);
	if (!path || execve(path, cmd->argv, shell->envp) == -1)
		child_error(shell, cmd->argv[0], path);
}

void	execute_pipeline(t_shell *shell)
{
	t_cmd	*curr;
	int		p[2];
	int		prev_fd;

	curr = shell->cmds;
	prev_fd = STDIN_FILENO;
	while (curr)
	{
		if (curr->next)
			pipe(p);
		curr->pid = fork();
		if (curr->pid == 0)
			execute_child(shell, curr, p, prev_fd);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		if (curr->next)
		{
			close(p[1]);
			prev_fd = p[0];
		}
		curr = curr->next;
	}
	wait_all(shell->cmds, shell);
}
