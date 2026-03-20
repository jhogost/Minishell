/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:27:01 by jbayet            #+#    #+#             */
/*   Updated: 2026/03/20 19:28:55 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*handle_and(char *s, int *i)
{
	if (s[*i] == '&' && s[*i + 1] == '&')
	{
		(*i) += 2;
		return (new_token(AND, ft_strdup("&&")));
	}
	return (NULL);
}

t_token	*handle_pipe_or(char *s, int *i)
{
	if (s[*i] == '|' && s[*i + 1] == '|')
	{
		(*i) += 2;
		return (new_token(OR, ft_strdup("||")));
	}
	if (s[*i] == '|')
	{
		(*i)++;
		return (new_token(PIPE, ft_strdup("|")));
	}
	return (NULL);
}

t_token	*handle_redir_in(char *s, int *i)
{
	if (s[*i] == '<' && s[*i + 1] == '<')
	{
		(*i) += 2;
		return (new_token(HEREDOC, ft_strdup("<<")));
	}
	if (s[*i] == '<')
	{
		(*i)++;
		return (new_token(REDIR_IN, ft_strdup("<")));
	}
	return (NULL);
}

t_token	*handle_redir_out(char *s, int *i)
{
	if (s[*i] == '>' && s[*i + 1] == '>')
	{
		(*i) += 2;
		return (new_token(APPEND, ft_strdup(">>")));
	}
	if (s[*i] == '>')
	{
		(*i)++;
		return (new_token(REDIR_OUT, ft_strdup(">")));
	}
	return (NULL);
}
