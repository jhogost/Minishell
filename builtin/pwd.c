/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:36:04 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/11 13:36:04 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **argv)
{
	char	str[PATH_MAX];

	if (argv[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (1);
	}
	if (getcwd(str, sizeof(str)) == NULL)
	{
		ft_putstr_fd("pwd: error retrieving current directory: getcwd", 2);
		ft_putstr_fd(": cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		return (1);
	}
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
