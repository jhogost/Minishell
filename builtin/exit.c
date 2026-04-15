/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:11:54 by hhervieu          #+#    #+#             */
/*   Updated: 2026/04/13 12:35:00 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valide_exit_inpute(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (str[i] != '"' && str[i] != '-' && str[i] != '+')
				return (0);
		}
		i++;
	}
	return (1);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	int	exit_code;

	exit_code = shell->exit_code;
	if (argv[1])
	{
		if (argv[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		if (valide_exit_inpute(argv[1]))
			exit_code = ft_atoi(argv[1]);
		else
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required", 2);
			exit_code = 2;
		}
	}
	free_everything(shell);
	exit(exit_code);
	return (0);
}
