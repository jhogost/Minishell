/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:45:47 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/15 18:11:53 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != PIPE)
	{
		if (tok->type == REDIR_IN || tok->type == REDIR_OUT
			|| tok->type == APPEND || tok->type == HEREDOC)
		{
			if (!tok->next)
				return (-1);
			tok = tok->next;
			if (tok->type != WORD && tok->type != BUILTIN)
				return (-1);
			tok = tok->next;
			continue ;
		}
		if (tok->type == WORD || tok->type == BUILTIN)
			count++;
		tok = tok->next;
	}
	return (count);
}

t_cmd	*fill_cmd(t_token **lexer, t_cmd *cmd)
{
	int		i;
	t_redir	*redir;

	i = 0;
	while (*lexer && (*lexer)->type != PIPE)
	{
		if (((*lexer)->type == WORD || (*lexer)->type == BUILTIN)
			&& !blank_line((*lexer)->word->str))
			cmd->argv[i++] = ft_strdup((*lexer)->word->str);
		else if ((*lexer)->type == REDIR_IN || (*lexer)->type == REDIR_OUT
			|| (*lexer)->type == APPEND || (*lexer)->type == HEREDOC)
		{
			redir = new_redir(lexer);
			if (!redir)
				return (NULL);
			add_redir_back(&cmd->redir, redir);
			*lexer = (*lexer)->next;
		}
		*lexer = (*lexer)->next;
	}
	cmd->argv[i] = NULL;
	if (*lexer && (*lexer)->type == PIPE)
		*lexer = (*lexer)->next;
	return (cmd);
}

t_cmd	*new_cmd(t_token **lexer)
{
	t_cmd	*cmd;
	int		args_count;

	cmd = init_cmd_struct();
	if (!cmd)
		return (NULL);
	args_count = count_args(*lexer);
	cmd->argv = malloc(sizeof(char *) * (args_count + 1));
	if (!cmd->argv)
		return (free(cmd), NULL);
	cmd = fill_cmd(lexer, cmd);
	return (cmd);
}

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
