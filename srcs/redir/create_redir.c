/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:19:40 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/14 16:38:07 by jbayet           ###   ########.fr       */
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
	t_redir	*redir;

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
		if ((*lexer)->next->word->expand)
			redir->expand = 1;
		redir->file = ft_strdup((*lexer)->next->word->str);
	}
	else
		redir->file = ft_strdup((*lexer)->next->word->str);
	return (redir);
}
