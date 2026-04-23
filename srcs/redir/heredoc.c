/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:33:06 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/23 16:01:07 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_heredoc(char *line, t_shell *shell)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1]
			&& (ft_isalnum(line[i + 1]) || line[i + 1] == '?'))
			line = expand_token(shell, line, i);
		i++;
	}
	return (line);
}

int	built_heredoc_cmds(t_shell *shell)
{
	t_cmd	*curr_cmd;
	t_redir	*curr_redir;

	curr_cmd = shell->cmds;
	while (curr_cmd)
	{
		if (curr_cmd->redir)
			curr_redir = shell->cmds->redir;
		else
			curr_redir = NULL;
		while (curr_redir)
		{
			if (curr_redir && curr_redir->type == HEREDOC)
			{
				curr_redir->heredoc_content = read_heredoc(curr_redir, shell);
				if (!curr_redir->heredoc_content)
					return (shell->exit_code = 130, -42);
			}
			curr_redir = curr_redir->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (0);
}

void	print_heredoc_warning(t_redir *redir, int start_line)
{
	char	*strt_line;

	strt_line = ft_itoa(start_line);
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putstr_fd(strt_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(redir->file, 2);
	ft_putstr_fd("')\n", 2);
	free(strt_line);
}

char	*heredoc_loop(t_redir *redir, t_shell *shell, int st, char *content)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_last_signal == 130)
		{
			rl_event_hook = NULL;
			return (free(line), free(content), NULL);
		}
		if (!line)
		{
			print_heredoc_warning(redir, st);
			free (line);
			break ;
		}
		shell->count_line++;
		if (ft_strcmp(line, redir->file) == 0)
			return (free(line), content);
		if (need_expand(line, redir->expand))
			line = expand_heredoc(line, shell);
		content = strjoin_free(content, line);
		content = strjoin_free(content, ft_strdup("\n"));
	}
	return (content);
}

char	*read_heredoc(t_redir *redir, t_shell *shell)
{
	char	*content;

	content = NULL;
	content = ft_strdup("");
	g_last_signal = 0;
	rl_catch_signals = 0;
	rl_event_hook = interrupt_hook;
	heredoc_signals();
	content = heredoc_loop(redir, shell, shell->count_line, content);
	if (!content)
		return (NULL);
	rl_event_hook = NULL;
	general_signals();
	return (content);
}
