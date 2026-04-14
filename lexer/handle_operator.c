/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:27:01 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/14 16:39:40 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*handle_and(char *s, int *i)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->expand = 0;
	if (s[*i + 1])
	{
		if (s[*i] == '&' && s[*i + 1] == '&')
		{
			(*i) += 2;
			word->str = ft_strdup("&&");
			return (new_token(AND, word));
		}
	}
	return (NULL);
}

t_token	*handle_pipe_or(char *s, int *i)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->expand = 0;
	if (s[*i + 1])
	{
		if (s[*i] == '|' && s[*i + 1] == '|')
		{
			(*i) += 2;
			word->str = ft_strdup("||");
			return (new_token(OR, word));
		}
	}
	if (s[*i] == '|')
	{
		(*i)++;
		word->str = ft_strdup("|");
		return (new_token(PIPE, word));
	}
	return (NULL);
}

t_token	*handle_redir_in(char *s, int *i)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->expand = 0;
	if (s[*i + 1])
	{
		if (s[*i] == '<' && s[*i + 1] == '<')
		{
			(*i) += 2;
			word->str = ft_strdup("<<");
			return (new_token(HEREDOC, word));
		}
	}
	if (s[*i] == '<')
	{
		(*i)++;
		word->str = ft_strdup("<");
		return (new_token(REDIR_IN, word));
	}
	return (NULL);
}

t_token	*handle_redir_out(char *s, int *i)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->expand = 0;
	if (s[*i + 1])
	{
		if (s[*i] == '>' && s[*i + 1] == '>')
		{
			(*i) += 2;
			word->str = ft_strdup(">>");
			return (new_token(APPEND, word));
		}
	}
	if (s[*i] == '>')
	{
		(*i)++;
		word->str = ft_strdup(">");
		return (new_token(REDIR_OUT, word));
	}
	return (NULL);
}
