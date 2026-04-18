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

static void	handle_child_redir(t_cmd *cmd, int prev_fd)
{
	if (prev_fd != STDIN_FILENO)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(cmd->pipe[1], STDOUT_FILENO);
		close(cmd->pipe[0]);
		close(cmd->pipe[1]);
	}
}

static void	handle_parent_fds(int *prev_fd, t_cmd *curr)
{
	if (*prev_fd != STDIN_FILENO)
		close(*prev_fd);
	if (curr->next)
	{
		close(curr->pipe[1]);
		*prev_fd = curr->pipe[0];
	}
}

static void	execute_child(t_shell *shell, t_cmd *cmd, int prev_fd)
{
	char	*path;

	exec_signals();
	handle_child_redir(cmd, prev_fd);
	if (apply_redirections(cmd, shell) == -42)
	{
		if (g_last_signal == 130)
			exit(130);
		exit(1);
	}
	if (!cmd->argv[0] || cmd->argv[0][0] == '\0')
		exit(0);
	if (isbuiltin(cmd->argv[0]) == 0)
		exit(built_in(cmd, shell));
	if (ft_strchr(cmd->argv[0], '/'))
	{
		if (is_directory(cmd, cmd->argv[0]))
			exit(126);
		path = ft_strdup(cmd->argv[0]);
	}
	else
		path = find_path(shell->paths, cmd->argv[0]);
	if (!path)
		child_error(shell, cmd->argv[0], path);
	if (execve(path, cmd->argv, shell->envp) == -1)
		execve_error(cmd, shell, path);
}

int	run_builtin_parent(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin < 0 || saved_stdout < 0)
		return (perror("dup"), 1);
	if (apply_redirections(cmd, shell) == -42)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		if (g_last_signal == 130)
			return (130);
		else
			return (1);
	}
	status = built_in(cmd, shell);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (shell->exit_code = status, status);
}

void	execute_pipeline(t_shell *shell)
{
	t_cmd	*curr;
	int		prev_fd;

	curr = shell->cmds;
	if (!curr)
		return ;
	if (!curr->next && isbuiltin(curr->argv[0]) == 0)
	{
		shell->exit_code = run_builtin_parent(curr, shell);
		return ;
	}
	prev_fd = STDIN_FILENO;
	while (curr)
	{
		if (curr->next)
			pipe(curr->pipe);
		curr->pid = fork();
		ignore_signals();
		if (curr->pid == 0)
			execute_child(shell, curr, prev_fd);
		handle_parent_fds(&prev_fd, curr);
		curr = curr->next;
	}
	wait_all(shell->cmds, shell);
	general_signals();
}
