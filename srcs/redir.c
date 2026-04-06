/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:19:40 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/06 19:20:21 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redir_back(t_redir **redirs, t_redir *new)
{
	t_redir	*tmp;

	if (!*redirs)
	{
		*redirs = new;
		return ;
	}
	tmp = *redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_redir	*new_redir(t_token **lexer)
{
	t_redir *redir;

	if (!(*lexer)->next)
		return (NULL);
	if ((*lexer)->next->type != WORD && (*lexer)->next->type != BUILTIN)
		return (NULL);
	redir = init_redir_struct();
	if (!redir)
		return (NULL);
	redir->type = (*lexer)->type;
	if ((*lexer)->type == HEREDOC)
	{
		if ((*lexer)->next->word[0] == '\'')
		{
			redir->quoted = 1;
			redir->heredoc_content = ft_strdup_no_quotes((*lexer)->next->word);
		}
		else
			redir->heredoc_content = ft_strdup((*lexer)->next->word);
	}
	else
		redir->file = ft_strdup((*lexer)->next->word);
	return (redir);
}

void	apply_redirections(t_cmd *cmd)
{
	t_redir	*tmp;
	int		fd;

	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->type == REDIR_OUT)
		{
			fd = open(tmp->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				perror("open");
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (tmp->type == APPEND)
		{
			fd = open(tmp->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
				perror("open");
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (tmp->type == REDIR_IN)
		{
			fd = open(tmp->file, O_RDONLY);
			if (fd < 0)
				perror("open");
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		// heredoc plus tard
		tmp = tmp->next;
	}
}
