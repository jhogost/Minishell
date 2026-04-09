/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:10:49 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/09 19:11:22 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_lexer(t_shell *shell, t_token *lexer)
{
	t_token	*tmp;

	tmp = lexer;
	while (tmp)
	{
		while (ft_strchr(tmp->word->str, '$') && tmp->word->expand)
			tmp->word->str = expand_token(shell, tmp->word->str);
		tmp = tmp->next;
	}
}
