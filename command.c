/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:45:47 by jbayet            #+#    #+#             */
/*   Updated: 2026/03/31 14:40:49 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token *tok)
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

static t_cmd	*new_cmd(t_token **lexer)
{
	t_cmd	*cmd;
	int		i;
	int		args_count;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	args_count = count_args(*lexer);
	cmd->argv = malloc(sizeof(char *) * (args_count + 1));
	cmd->pipe_in = STDIN_FILENO;
	cmd->pipe_out = STDOUT_FILENO;
	cmd->next = NULL;
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

static t_cmd	*init_cmd(t_token *tok)
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

int	fill_cmds(t_shell *shell)
{
	t_token	*t;
	t_cmd	*new;
	int		i;

	t = shell->lexer;
	while (t)
	{
		new = init_cmd(t);
		if (!new)
			return (-1);
		i = 0;
		while (t && t->type != PIPE)
		{
			if (t->type == WORD)
				new->argv[i++] = ft_strdup(t->word);
			t = t->next;
		}
		new->argv[i] = NULL;
		add_cmd_back(&shell->cmds, new);
		if (t && t->type == PIPE)
			t = t->next;
	}
	return (0);
}
//fill the list of commands with the arguments from the lexer until pipe or end

/*
char	**tokens_to_argv(t_token **lexer)
{
	char	**argv;
	int		count;
	int		i;

	count = count_until_pipe(*lexer);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (*lexer && (*lexer)->type != PIPE)
	{
		if ((*lexer)->type == WORD)
		{
			argv[i] = ft_strdup((*lexer)->word);
			if (!argv[i])
				return (free_argv(argv, i), NULL);
			i++;
		}
		*lexer = (*lexer)->next;
	}
	argv[i] = NULL;
	if (*lexer && (*lexer)->type == PIPE)
		*lexer = (*lexer)->next;
	return (argv);
}
*/