/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_exit_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 10:49:45 by hhervieu          #+#    #+#             */
/*   Updated: 2026/04/13 10:49:45 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_part(char *res, char *word, int start, int end)
{
	char	*tmp;

	if (start >= end)
		return (res);
	tmp = ft_substr(word, start, end - start);
	return (strjoin_free(res, tmp));
}

char	*replace_exit_code_in_word(char *word, int exit_code)
{
	char	*res;
	char	*code;
	int		i;
	int		start;

	i = -1;
	start = 0;
	res = NULL;
	if (!(code = ft_itoa(exit_code)))
		return (NULL);
	while (word[++i])
	{
		if (word[i] == '$' && word[i + 1] == '?')
		{
			res = append_part(res, word, start, i);
			res = strjoin_free(res, ft_strdup(code));
			start = i + 2;
			i++;
		}
	}
	if (!res)
		res = ft_strdup(word);
	else
		res = append_part(res, word, start, i);
	return (free(code), res);
}
// Transform the string "$?" into the last exit code of the
// last command executed