/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 10:41:04 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/23 10:41:04 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd_struct(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->pid = -1;
	cmd->next = NULL;
	return (cmd);
}

int	init_struct(t_shell *shell, char **envp)
{
	char	*path;

	shell->input = NULL;
	shell->exit_code = 0;
	if (get_env(envp, shell) == -42)
		return (-42);
	path = getenv("PATH");
	if (!path)
		return (-42);
	shell->paths = ft_split(path, ":");
	if (!shell->paths)
		return (-42);
	return (0);
}
