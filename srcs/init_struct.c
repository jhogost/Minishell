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

t_redir	*init_redir_struct(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = NULL;
	redir->heredoc_content = NULL;
	redir->quoted = 0;
	redir->type = WORD;
	redir->next = NULL;
	return (redir);
}

t_cmd	*init_cmd_struct(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->pipe[0] = -1;
	cmd->pipe[1] = -1;
	cmd->redir = NULL;
	cmd->pid = -1;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*init_cmd(t_token *tok)
{
	t_cmd	*cmd;
	int		nb_args;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	nb_args = count_args(tok);
	cmd->argv = malloc(sizeof(char *) * (nb_args + 1));
	if (!cmd->argv)
		return (free(cmd), NULL);
	cmd->pid = -1;
	cmd->next = NULL;
	return (cmd);
}
//initialize a command structure with the number of arguments until pipe or end

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
