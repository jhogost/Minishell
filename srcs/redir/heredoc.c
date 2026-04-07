/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:33:06 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/07 20:12:48 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_heredoc(t_redir *redir)
{
	char	*content;
	char	*line;

	content = NULL;
	content = ft_strdup("");
	while(1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, redir->file) == 0)
			return (free(line), content);
		if (redir->quoted)
			content = strjoin_free(content, line);
		else
			content = strjoin_free(content, line); //TODO expand var !!!!!!!!!!!
		content = strjoin_free(content, ft_strdup("\n"));
	}
	return (content);
}
