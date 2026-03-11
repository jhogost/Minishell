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

int	is_built_in(char *line, int len)
{
	if (ft_strncmp(line, "echo", len) == 0 && len == 4)
		return (0);
	if (ft_strncmp(line, "cd", len) == 0 && len == 2)
		return (0);
	if (ft_strncmp(line, "pwd", len) == 0 && len == 3)
		return (builtin_pwd());
	if (ft_strncmp(line, "export", len) == 0 && len == 6)
		return (0);
	if (ft_strncmp(line, "unset", len) == 0 && len == 5)
		return (0);
	if (ft_strncmp(line, "env", len) == 0 && len == 3)
		return (0);
	return (-42);
}

void	builtin_cmd_or_else(char *line)
{
	if (is_built_in(line, ft_strlen(line)) != 0)
		return ;
}
//check if it's one of the built-in cmd of shell besides exit
