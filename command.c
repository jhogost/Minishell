/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:45:47 by jbayet            #+#    #+#             */
/*   Updated: 2026/03/26 18:01:34 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(int nb_token, int redir_in, t_token *start_token, t_shell *shell)
{
	t_cmd	*cmd;
	int		i;

	if (!nb_token)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->content_redir = NULL;
	cmd->redir_type = WORD;
	cmd->command = malloc(sizeof(char *) * ((nb_token + 1) - (redir_in * 2))); //nb de token (+ 1 pour NULL) mais si redir present (-2 pour redir + argument du redir)
	if (cmd->command)
		return (NULL);
	i = 0;
	while (i < nb_token - (redir_in * 2))
	{
		if (start_token->type == WORD)
		{
			cmd->command[i] = ft_strdup(start_token->word);
			i++;
		}
		else
		{
			cmd->redir_type = start_token->type;
			start_token = start_token->next;
			cmd->content_redir = ft_strdup(start_token->word);
		}
		start_token = start_token->next;
	}
	cmd->pipe_in = 0;
	cmd->pipe_out = 1;
	cmd->next = NULL;
	return (cmd);
}

void	add_cmd(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*cmds)
	{
		*cmds = new;
		return ;
	}
	tmp = *cmds;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_cmd	*build_cmds(t_shell *shell)
{
	t_token	*current_token;
	t_token	*start_token;
	t_cmd	*current_cmd;
	int		count_token_in_cmd;
	int		redir_in;

	current_token = shell->lexer;
	while (current_token)
	{
		start_token = current_token;
		count_token_in_cmd = 0;
		redir_in = 0;
		while (current_token->type != PIPE)
		{
			count_token_in_cmd++;
			if (current_token->type != WORD)
				redir_in = 1;
			current_token = current_token->next;
		}
		current_cmd = new_cmd(count_token_in_cmd, redir_in, start_token, shell);
		if (!current_cmd)
			return (NULL);
		add_cmd(&shell->cmds, current_cmd);
	}
	return (shell->cmds);
}
