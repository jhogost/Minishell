/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:14:29 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/23 12:47:13 by jbayet           ###   ########.fr       */
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

int	two_pipe_in_a_row(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			i++;
			while(line[i] && is_space(line[i]))
				i++;
			if (line[i] == '|')
				return (1);
			continue ;
		}
		i++;
	}
	return (0);
}
