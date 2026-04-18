/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_text_and_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:46:28 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/09 14:52:25 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_quote(char *s, int *i, char *res)
{
	char	quote;
	int		start;
	char	*tmp;

	quote = s[*i];
	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (!s[*i])
		return (free(res), NULL);
	tmp = ft_substr(s, start, *i - start);
	if (!tmp)
		return (free(res), NULL);
	res = strjoin_free(res, tmp);
	(*i)++;
	return (res);
}

char	*handle_plain_text(char *s, int *i, char *res)
{
	int		start;
	char	*tmp;

	start = *i;
	while (s[*i] && !is_space(s[*i])
		&& !is_operator(s[*i])
		&& s[*i] != '\'' && s[*i] != '"')
		(*i)++;
	tmp = ft_substr(s, start, *i - start);
	if (!tmp)
		return (free(res), NULL);
	res = strjoin_free(res, tmp);
	return (res);
}
