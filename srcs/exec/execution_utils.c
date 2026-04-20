/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:24:57 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/20 16:47:32 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(t_cmd *cmd, char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (0);
	if (S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (1);
	}
	return (0);
}

void	exit_child_signal(t_shell *shell)
{

	if (g_last_signal == 130)
	{
		free_everything(shell);
		exit(130);
	}
	free_everything(shell);
	exit(1);
}

void	exit_child(t_shell *shell, t_cmd *cmd, int code)
{
	free_everything(shell);
	exit(code);
}