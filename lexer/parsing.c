/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:19:34 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/23 17:30:34 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_closed(char *s)
{
	int		i;
	char	quote;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i];
			count++;
			i++;
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] == quote)
				count++;
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (count % 2 == 0);
}

int	verify_line(char *line)
{
	if (!line)
		return (-1);
	if (count_tokens(line) == -1)
		return (free(line), printf("Syntax error: too many operators\n"), -1);
	if (line[0] == '|' || line[0] == '&')
		return (printf("Syntax error: unexpected token `%c'\n", line[0]),
			free(line), -1);
	if (quote_closed(line) == 0)
		return (free(line), printf("Syntax error: unclosed quote\n"), -1);
	return (0);
}

int	count_tokens(char *word)
{
	int		i;
	int		count;
	char	operator;

	i = 0;
	count = 0;
	while (word[i])
	{
		count = 0;
		if (is_operator(word[i]))
		{
			operator = word[i];
			count++;
			while (is_operator(word[i]) && word[i] == operator)
			{
				count++;
				i++;
			}
			if (count > 3)
				return (-1);
		}
		else
			i++;
	}
	return (0);
}
/// Check if operator are more than 3 in a row