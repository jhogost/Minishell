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

int	is_built_in(char *word, int len)
{
	if (ft_strncmp(word, "echo", len) == 0 && len == 4)
		return (0);
	if (ft_strncmp(word, "cd", len) == 0 && len == 2)
		return (0);
	if (ft_strncmp(word, "pwd", len) == 0 && len == 3)
		return (builtin_pwd());
	if (ft_strncmp(word, "export", len) == 0 && len == 6)
		return (0);
	if (ft_strncmp(word, "unset", len) == 0 && len == 5)
		return (0);
	if (ft_strncmp(word, "env", len) == 0 && len == 3)
		return (0);
	return (-42);
}

void	builtin_cmd_or_else(char *word)
{
	if (!word)
		return ;
	if (is_built_in(word, ft_strlen(word)) != 0)
		return ;
}
//check if it's one of the built-in cmd of shell besides exit
