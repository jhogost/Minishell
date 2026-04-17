/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:33:06 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/18 00:23:48 by jbayet           ###   ########.fr       */
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

int	interrupt_hook(void)
{
	if (g_last_signal == 130)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}

char	*read_heredoc(t_redir *redir, t_shell *shell)
{
	char	*content;
	char	*line;
	int		start_line;

	content = NULL;
	content = ft_strdup("");
	start_line = shell->count_line;
	g_last_signal = 0;
	rl_catch_signals = 0;
	rl_event_hook = interrupt_hook;
	heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (g_last_signal == 130)
		{
			rl_event_hook = NULL;
			general_signals();
			return (free(line), free(content), NULL);
		}
		if (!line)
		{
			ft_putstr_fd("bash: warning: here-document at line ", 2);
			ft_putstr_fd(ft_itoa(start_line), 2);
			ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(redir->file, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		shell->count_line++;
		if (ft_strcmp(line, redir->file) == 0)
			return (general_signals(), free(line), content);
		if (need_expand(line, redir->expand))
			line = expand_heredoc(line, shell);
		content = strjoin_free(content, line);
		content = strjoin_free(content, ft_strdup("\n"));
	}
	rl_event_hook = NULL;
	return (general_signals(), content);
}
