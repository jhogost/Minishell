/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_white_char_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:21:22 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/13 18:29:41 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	i_white_char_str(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'
			|| line[i] == '\r' || line[i] == '\v' || line[i] == '\f')
			return (i);
		i++;
	}
	return (-1);
}
