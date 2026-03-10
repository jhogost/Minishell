/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 16:55:52 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/10 16:55:52 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_things(char *line)
{
	if (line)
		free(line);
	rl_clear_history();
}
//TODO update whenever the struct is ready to free everything