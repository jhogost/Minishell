/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:45:47 by jbayet            #+#    #+#             */
/*   Updated: 2026/03/31 16:28:44 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_token *tok)
{
	int	i;

	i = 0;
	while (tok && tok->type != PIPE)
	{
		if (tok->type == WORD)
			i++;
		tok = tok->next;
	}
	return (i);
}
//count number of args until pipe or the end

t_cmd	*new_cmd(t_token **lexer)
{
	t_cmd	*cmd;
	int		i;
	int		args_count;

	cmd = init_cmd_struct();
	if (!cmd)
		return (NULL);
	args_count = count_args(*lexer);
	cmd->argv = malloc(sizeof(char *) * (args_count + 1));
	i = 0;
	while (*lexer && (*lexer)->type != PIPE)
	{
		if ((*lexer)->type == WORD)
			cmd->argv[i++] = ft_strdup((*lexer)->word);
		*lexer = (*lexer)->next;
	}
	cmd->argv[i] = NULL;
	if (*lexer && (*lexer)->type == PIPE)
		*lexer = (*lexer)->next;
	return (cmd);
}
//create a new command and initialize everything until pipe or the end

void	add_cmd_back(t_cmd **cmds, t_cmd *new)
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
//add a command to the end of the list of commands

int	create_cmds(t_shell *shell)
{
	t_token	*tmp_lexer;
	t_cmd	*cmd;

	tmp_lexer = shell->lexer;
	while (tmp_lexer)
	{
		cmd = new_cmd(&tmp_lexer);
		if (!cmd)
			return (-42);
		add_cmd_back(&shell->cmds, cmd);
	}
	return (0);
}
//create the list of commands from the lexer
