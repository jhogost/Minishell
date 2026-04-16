/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:38:26 by hhervieu          #+#    #+#             */
/*   Updated: 2026/04/02 14:38:26 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_error(t_shell *shell, char *cmd, char *path)
{
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd);
	}
	free(path);
	free_cmds(shell);
	free_everything(shell);
	exit(127);
}

void	execve_error(t_cmd *cmd, t_shell *shell, char *path)
{
	char	**new_argv;
	int		argc;
	int		i;

	if (errno == ENOEXEC)
	{
		argc = 0;
		while (cmd->argv[argc])
			argc++;
		new_argv = malloc(sizeof(char *) * (argc + 2));
		if (!new_argv)
			child_error(shell, cmd->argv[0], path);
		new_argv[0] = "/bin/bash";
		i = 0;
		while (cmd->argv[i])
		{
			new_argv[i + 1] = cmd->argv[i];
			i++;
		}
		new_argv[i + 1] = NULL;
		execve("/bin/bash", new_argv, shell->envp);
		free(new_argv);
	}
	child_error(shell, cmd->argv[0], path);
}
