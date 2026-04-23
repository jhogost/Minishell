/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:14:29 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/23 15:01:41 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wrong_last_token(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	i--;
	if (line[i] == '<' || line[i] == '>')
		return (1);
	else
		return (0);
}

static int	in_quote(char *line, int i, int state)
{
	int		j;
	char	quote;

	j = 0;
	while (j < i)
	{
		if (line[j] == '"' || line[j] == '\'')
		{
			if (state == 0)
			{
				quote = line[j];
				state = 1;
			}
			else
			{
				if (line[j] == quote)
				{
					quote = '\0';
					state = 0;
				}
			}
		}
		j++;
	}
	return (state);
}

int	two_pipe_in_a_row(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			i++;
			while (line[i] && is_space(line[i]))
				i++;
			if (line[i] == '|' && !in_quote(line, i, 0))
				return (1);
			continue ;
		}
		i++;
	}
	return (0);
}
