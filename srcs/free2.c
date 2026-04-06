/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:37:21 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/06 14:31:00 by jbayet           ###   ########.fr       */
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
