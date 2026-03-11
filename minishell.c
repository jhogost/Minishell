/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:51:10 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/10 14:51:10 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	**line;

	while (1)
	{
		line = ft_split(readline("chocolat shell: "), " ");
		if (!line || (ft_strcmp(*line, "exit") == 0 && ft_strlen(*line) == 4))
			break ;
		builtin_cmd_or_else(*line);
		add_history(*line);
		free_line(line);
	}
	return (free_things(), free_line(line), 0);
}
//TODO built in commands | struct for every var | chained list to get the
//order of what to do for each lines