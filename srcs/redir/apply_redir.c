/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:36:31 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/22 12:46:06 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_redir_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-42);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redir_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-42);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-42);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	apply_redir_heredoc(t_redir *redir)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -42);
	write(pipefd[1], redir->heredoc_content, ft_strlen(redir->heredoc_content));
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (0);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*tmp;
	int		status;

	status = 0;
	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->type == REDIR_OUT)
			status = apply_redir_out(tmp);
		else if (tmp->type == APPEND)
			status = apply_redir_append(tmp);
		else if (tmp->type == REDIR_IN)
			status = apply_redir_in(tmp);
		else if (tmp->type == HEREDOC)
			status = apply_redir_heredoc(tmp);
		if (status == -42)
			return (-42);
		tmp = tmp->next;
	}
	return (0);
}
