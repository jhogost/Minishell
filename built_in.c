/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 18:04:23 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/10 18:04:23 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_cmd(char *line)
{
	if (strcmp(line, "echo") == 1 || strcmp(line, "cd") == 1
		|| strcmp(line, "pwd") == 1 || strcmp(line, "export") == 1
		|| strcmp(line, "unset") == 1 || strcmp(line, "env") == 1)
		return ;
	return ;
}
//check if it's one of the built-in cmd of shell besides exit
//TODO change strcmp to ft_strcmp | implement split here